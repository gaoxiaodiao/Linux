/**************************************
*文件说明:哈希桶相关声明及实现
*作者:高小调
*创建时间:2017年04月19日 星期三 08时56分49秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __HASHBUCKET_HPP__
#define __HASHBUCKET_HPP__
#include<vector>
#include<cassert>
//哈希桶节点
template<typename K,typename V>
struct HashBucketNode{
	std::pair<K,V> _kv;
	HashBucketNode *_next;
	//构造函数
	HashBucketNode(const std::pair<K,V> & kv= std::pair<K,V>(K(),V()))
		:_kv(kv)
		,_next(NULL){}
};

//前置声明
template<typename K,typename V,typename HashFunc,typename Ptr,typename Ref>
struct HashBucketIterator;

//哈希算法
template<typename K>
struct HashFunc{
	size_t operator()(const K &key){
		return key;
	}
};

//哈希桶
template<typename K,typename V,typename HashFunc=HashFunc<K> >
class HashBucket{
	
public:
	typedef HashBucketNode<K,V> Node;
	typedef HashBucketIterator<K, V, HashFunc, std::pair<K,V>*, std::pair<K,V> & > Iterator;
	typedef HashBucketIterator<K,V,HashFunc,const std::pair<K,V> * ,const std::pair<K,V>& > ConstIterator;
	friend Iterator;
	friend ConstIterator;
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
#ifdef __HASHBUCKET_DEBUG__
				//为了更直观的明白析构乱序问题,在此把index也打印出来
				std::cout<<"\033[31m"<<del->_kv.first<<":"<<del->_kv.second<<"("<<i<<")"<<"\033[0m"<<std::endl;
#endif
				delete del;
			}
		}
	}
public:
	/////////////公用接口///////////////
	bool Insert(const K &key,const V &value);	//简化返回值
	Node* Find(const K &key);					//简化返回值
	void Remove(const K &key);
	Iterator Begin(){
		for(int i=0; i<_table.size(); ++i){
			if(_table[i]!=NULL){
				return Iterator(this,_table[i]);
			}
		}
	}
	Iterator End(){
		return Iterator(this,NULL);
	}
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
void HashBucket<K,V,HashFunc>::_Check(){
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
		//_table.swap(tmp._table);
		std::swap(_table,tmp._table);
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
	_Check();
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
	++_size;
#ifdef __HASHBUCKET_DEBUG__
	std::cout<<"["<<index<<"]"<<key<<":"<<value<<std::endl;
#endif
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
#ifdef __HASHBUCKET_DEBUG__
			std::cout<<"\033[34m"<<"key="<<cur->_kv.first<<"被释放!"<<"\033[0m"<<std::endl;
#endif
			delete cur;
			--_size;
			return ;
		}
		parent = cur;
		cur = cur->_next;
	}
}
//哈希算法
template<typename K,typename V,typename HashFunc>
size_t HashBucket<K,V,HashFunc>::_HashFunc(const K& key){
	return HashFunc()(key)%_table.size();
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
/*
template<typename K,typename V,typename HashFunc>
typename HashBucket<K,V,HashFunc>::Iterator HashBucket<K,V,HashFunc>::Begin(){
	Node *ret = NULL;
	for(int i=0; i<_table.size(); ++i){
		if(_table[i]!=NULL){
			ret = _table[i];
			break;
		}
	}
	return Iterator(this,ret);
}

template<typename K,typename V,typename HashFunc>
typename HashBucket<K,V,HashFunc>::Iterator HashBucket<K,V,HashFunc>::End(){
	return Iterator(this,NULL);
}
*/
//哈希桶简单版的迭代器
template<typename K,typename V,typename HashFunc,typename Ptr,typename Ref>
struct HashBucketIterator{
	typedef HashBucketNode<K,V> Node;
	typedef HashBucketIterator<K,V,HashFunc,Ptr,Ref> Self;
	//成员
	HashBucket<K,V,HashFunc> *_hb;	//哈希表
	Node * _node;					//当前节点
	//构造函数
	HashBucketIterator(HashBucket<K,V,HashFunc>* hb,Node* node)
		:_hb(hb)
		,_node(node){}
	//== !=
	bool operator!=(const Self & s)const{
		return _node!=s._node;
	}
	bool operator==(const Self &s)const{
		return (!(operator!=(s)));
	}
	//++
	Self& operator++(){
		_node = _Next();
		return *this;
	}
	Self operator++(int){
		Self ret(_hb,_node);
		_node = _Next();
		return ret;
	}
	//--
	Self &operator--(){
		_node = _Prev;
		return *this;
	}
	Self operator--(int){
		Self ret(_hb,_node);
		_node = _Prev();
		return ret;
	}
	//*
	Ref operator*(){
		return _node->_kv;
	}
	//->
	Ptr operator->(){
		return &(operator*());
	}
protected:
	//++
	Node* _Next(){
		if(_node==NULL){
			//当前哈希桶已经走完.
			assert(false);
			return NULL;
		}
		Node *next = _node->_next;
		if(next==NULL){
			//说明当前桶内_node已经是最后一个节点,
			//因此需要到其他桶中查询
			size_t index = _hb->_HashFunc(_node->_kv.first) + 1;
			for(; index<_hb->_table.size(); ++index){
				Node *cur = _hb->_table[index];
				if(cur!=NULL){
					//找到之后,修改next的值,然后跳出循环
					next = cur;
					break;
				}
			}
		}
		return next;
	}
	//--
	//先求出下标,判断当前节点是不是桶中首元素
	//如果不是首元素,遍历到当前节点,返回.
	//如果是首元素,到下标-1的桶中去找,然后循环此过程
	Node *_Prev(){
		if(_node==NULL){
			//当前哈希表已经走完
			assert(false);
			return NULL;
		}
		Node *prev = NULL;
		size_t index = _hb->_HashFunc(_node->_kv.first);
		if(_node!=_hb->_table[index]){
			//当前节点不是桶的首元素,遍历当前桶
			Node *cur = _hb->_table[index];
			assert(cur);		//桶中首元素为空,程序绝对有问题了!
			while(cur!=NULL&&cur!=_node){
				prev = cur;
				cur = cur->_next;
			}
			return prev;
		}
			//当前是桶中第一个元素,去前一个桶中找
		for(int i=index-1; i>=0; --i){
			Node *cur = _hb->_table[index];
			//如果前一个桶不为空,那么就是该桶最后一个元素
			while(cur!=NULL){
				prev = cur;
				cur = cur->_next;
			}
			if(prev!=NULL){
				//说明已经找到前一个节点
				break;
			}
		}
		return prev;
	}
};

#endif
