/**************************************
*文件说明:哈希桶相关声明及实现
*作者:高小调
*创建时间:2017年04月19日 星期三 08时56分49秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<vector>
//哈希桶节点
template<typename K,typename V>
struct HashBucketNode{
	std::pair<K,V> _kv;
	HashBucketNode *_next;
	//构造函数
	HashBucketNode(const std::pair<K,V> & kv= std::pair(K(),K()))
		:_kv(kv)
		,_next(NULL){}
};

//哈希算法
template<typename K>
struct HashFunc{
	size_t operator()(const K &key){
		return key;
	}
};

//哈希桶
template<typename K,typename V,typename HashFunc=HashFunc<K>>
class HashBucket{
public:
	typedef HashBucketNode<K,V> Node;
public:
	//构造函数
	HashBucket(const size_t size = 0)
		:_size(0){
		_table.resize(size);
	}
	//析构函数
	~HashBucket(){
		for(int i=0; i<_table.size(); ++i){
			Node *cur = _table[i];
			while(cur!=NULL){
				Node* del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}
public:
	bool Insert(const K &key,const V &value);	//简化返回值
	Node* Find(const K &key);					//简化返回值
	void Remove(const K &key);
protected:
	void _Check();
	size_t _HashFunc(const K&);
	size_t _GetPrimeSize(size_t);
private:
	//禁止拷贝、赋值(懒人做法)
	HashBucket(const HashBucket&);
	HashBucket &operator=(const HashBucket&);
private:
	std::vector<Node*> _table;
	size_t _size;
};

//判断是否需要扩容
template<typename K,typename V,typename HashFunc>
HashBucket<K,V,HashFunc>::_Check(){
	if(_table.empty()){
		//第一次初始化默认容量给7
		_table.resize(7);
	}else if( _size/_table.size() >= 1){
		//哈希桶已满,需要立即扩容
		size_t newSize = _GetPrimeSize(_size);	//计算新容量
		HashBucket<K,V> tmp(newSize);			//创建新对象
		for(int i=0; i<_table.size(); ++i){
			//将原表中的数据重新插入新表
			Node *cur = _table[i];
			while(cur!=NULL){
				tmp.Insert(cur->_kv.first,cur->_kv.second);
				cur = cur->_next;
			}
		}
		//交换
		_table.swap(tmp._table);
		std::swap(_size,tmp._size);
	}
}

//查找
template<typename K,typename V,typename HashFunc>
typename HashBucket<K,V,HashFunc>::Node* 
HashBucket<K,V,HashFunc>::Find(const K &key){
	size_t index = _HashFunc(key);	//计算所在下标
	Node *cur = _table[index];		//拿到第一个节点
	while(cur!=NULL){
		if(cur->_kv.first == key){
			//找到返回当前节点
			return cur;
		}
		cur = cur->_next;
	}
	//没找到返回空
	return NULL;
}
//插入
template<typename K,typename V,typename HashFunc>
bool HashBucket<K,V,HashFunc>::Insert(const K &key,const V &value){
	Node* ret = Find(key);
	if(ret!=NULL){
		//该key值已存在,返回false
		return false;
	}
	size_t index = _HashFunc(key);	//计算下标
	Node *newNode = new Node(std::make_pair(key,value));	//创建新节点
	//头插
	newNode->_next = _table[index];
	_table[index] = newNode;
	return true;
}
//删除
template<typename K,typename V,typename HashFunc>
void HashBucket<K,V,HashFunc>::Remove(const K &key){
	size_t index = _HashFunc(key);
	Node *parent = NULL;
	Node *cur = _table[index];
	while(cur!=NULL){
		if(cur->_kv.first == key){
			//找到该节点
			if(parent!=NULL){
				//该节点非头节点
				parent->_next = cur->_next;
			}else{
				//该节点是头节点
				_table[index] = cur->_next;
			}
			//释放当前节点
			delete cur;
			return ;
		}
		parent = cur;
		cur = cur->_next;
	}
}
//哈希算法
template<typename K,typename V,typename HashFunc>
size_t HashBucket<K,V,HashFunc>::_HashFunc(const K& key){
	return HashFunc()(key)&_table.size();
}
//素数表
template<typename K,typename V,typename HashFunc>
size_t HashBucket<K,V,HashFunc>::_GetPrimeSize(size_t size){
	const int Primesize = 28;
	static const unsigned long Primenum[Primesize] ={
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul,
		786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul,
		25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul,
		805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};
	for (int i = 0; i < Primesize; ++i){
		if (Primenum[i] > size){
			return Primenum[i];
		}
	}
	return size;
}
template<typename K,typename V,typename HashFunc>
HashBucket<K,V,HashFunc>::
template<typename K,typename V,typename HashFunc>
HashBucket<K,V,HashFunc>::
template<typename K,typename V,typename HashFunc>
HashBucket<K,V,HashFunc>::
template<typename K,typename V,typename HashFunc>
HashBucket<K,V,HashFunc>::
