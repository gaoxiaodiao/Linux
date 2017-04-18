/**************************************
*文件说明:哈希表(线性探测法)
*作者:高小调
*创建时间:2017年04月18日 星期二 10时02分34秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<vector>
//哈希表的三种状态
enum STATUS{
	EMPTY,		//当前节点为空
	EXIST,		//当前节点已存在
	DELETE		//当前节点已被删除
};
//哈希方法:将Key值转换为整数
template<typename K>
struct HashFun{
	size_t operator()(const K& key){
		return key;
	}
};
//针对字符串类型进行特化
template<>
struct HashFun<std::string>{
	size_t operator()(const std::string &s){
		size_t ret = 0;
		const char *cur = s.c_str();
		while(*cur){
			ret += 137+*cur;
			++cur;
		}
	}
};


template<typename K,typename V,typename HashFun = HashFun<K> >
class HashTable{
	//哈希表数据节点
	struct Node{
		K _key;
		V _value;
		STATUS _status;
		Node(const K &key,const V &value)
			:_key(key)
			,_value(value)
			,_status(EMPTY){}
	};
public:
	//构造函数
	HashTable(size_t size)
		:_size(0){
		_tables.resize(size);	//在这里resize方便后面程序使用下标访问
	}
	//析构函数
	//...略
public:
	///////////////////公用接口///////////////////////
	std::pair<Node*,bool> Insert(const K &,const V &);	//插入
	void Remove(const K&);								//删除
	std::pair<Node*,bool> Find(const K&);				//查找
protected:
	void _CheckCapacity();		//检查是否需要扩容,进行扩容操作
	size_t _HashFun(const K &);	//使计算出来的下标处于合法位置
private:
	//禁止拷贝构造、赋值(懒人做法)
	HashTable(const HashTable &);
	HashTable &operator=(const HashTable &);
private:
	std::vector<Node> _tables;
	size_t _size;
};

/////////////////哈希表插入实现///////////////
template<typename K,typename V,typename HashFun>
std::pair<typename HashTable<K,V,HashFun>::Node*,bool> \
		HashTable<K,V,HashFun>::Insert(const K &key,const V &value){	
		_CheckCapacity();				//检查是否需要扩容
		size_t index = _HashFun(key);	//通过哈希方法根据key值计算下标
		//线性探测插入
		while(_tables[index].STATUS!=EMPTY){
			if(_tables[index]._key == key){
				//防冗余(key值唯一)
				return std::make_pair(_tables[index],false);
			}
			++index;	
			if(index == _tables.size()){
				//已经遍历到表尾,仍然没有空位,从头开始探测
				index = 0;
			}
		}
	}

//////////////////哈希表删除实现//////////////////
template<typename K,typename V,typename HashFun>
void HashTable<K,V,HashFun>::Remove(const K &key){
	std::pair<Node*,bool> del = Find(key);
	if(del._second != false){
		del->_STATUS = DELETE;
	}
}

//////////////////哈希表查找实现//////////////////
template<typename K,typename V,typename HashFun>
std::pair<typename HashTable<K,V,HashFun>::Node*,bool>
	HashTable<K,V,HashFun>::Find(const K &key){
		size_t index = _HashFun(key);
		while(_tables[index]._STATUS!=EMPTY){
			if(_tables[index]._key == key && 
					_tables[index]._status == EXIST){
				//遇到该元素,且该元素存在
				return std::make_pair(_tables[index],true);
			}
			++index;
			if(index >= _tables.size()){
				index = 0;
			}
		}
		//遇到空位置,该元素不存在
		return std::make_pair(_tables[index],false);
	}
