/**************************************
*文件说明:申请内存、释放内存均为O(1)的内存池
*作者:高小调
*创建时间:2017年04月17日 星期一 19时07分32秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
template<typename T>
class ObjectPool{
	struct ObjectPoolNode{
		void *base;				//大块内存
		size_t totalObj;		//对象个数
		ObjectPoolNode* next;	//下一块节点
	
		ObjectPoolNode(size_t nObjs){
			base = ::operator new(GetSize()*nObjs);
			if(base==NULL){
				throw std::bad_alloc();
			}
			totalObj = nObjs;
			next = NULL;
		}
	
		~ObjectPoolNode(){
			if(base!=NULL){
				::operator delete(base);
				base = NULL;
				totalObj = 0;
				next = NULL;
			}
		}
	};
typedef ObjectPoolNode Node;
public:
	ObjectPool(const size_t n = 20,const size_t max = 1024)
		:_head(NULL)
		,_tail(NULL)
		,_initNum(n)
		,_maxNum(max)
		,_Count(0)
		,_lastDeleted(NULL){
			_head = _tail = new Node(_initNum);
		}
	~ObjectPool(){
		Node *cur = _head;
		while(cur!=NULL){
			Node *del = cur;
			cur = cur->next;
			delete del;
		}
	}
public:
	void* Allocate();			//申请内存
	void Deallocate(T *);		//回收内存
	T* New();					//调用构造函数初始化对象
	void Delete(T*);			//调用析构函数清理资源
public:
	static size_t GetSize();
private:
	Node *_head;			//头节点
	Node *_tail;			//尾节点
	size_t _initNum;			//每次开多少个对象的内存
	size_t _maxNum;			//最大限度
	size_t _Count;			//已分配对象个数
	T *_lastDeleted;		//隐形释放链表
};
template<typename T>
T* ObjectPool<T>::New(){
	T *ret = (T*)Allocate();
	new(ret)T();
	return ret;	
}

template<typename T>
void ObjectPool<T>::Delete(T * ptr){
	ptr->~T();
	Deallocate(ptr);
}

template<typename T>
size_t ObjectPool<T>::GetSize(){
	return sizeof(T)>sizeof(T*)?sizeof(T):sizeof(T*);
}

template<typename T>
void* ObjectPool<T>::Allocate(){
	void *ret = NULL;
	//隐形链表中,没有节点,需要从尾节点获取
	if(_lastDeleted==NULL){
		//当前节点的所存对象已满,需要重新申请节点
		if(_Count >= _tail->totalObj){	//这个=号非常关键，调试了将近一个小时
			//节点的容量扩大一倍,但不超过所给的限度
			_initNum = _initNum*2<_maxNum?_initNum*2:_maxNum;
			_tail->next =new Node(_initNum);
			_tail = _tail->next;
			_Count = 0;

		}
		ret = (char*)_tail->base + _Count*GetSize();
	}else{
		//直接从隐形链表中获取对象(采取头删的形式)
		ret = _lastDeleted;
		_lastDeleted = *(T**)_lastDeleted;
	}
	++_Count;
	return ret;
}

template<typename T>
void ObjectPool<T>::Deallocate(T *ptr){
	//将当前节点头插入隐形链表
	*(T**)ptr = _lastDeleted;
	_lastDeleted = ptr;
	--_Count;
}
