/**************************************
*文件说明:哈希桶相关声明及实现
*作者:高小调
*创建时间:2017年04月19日 星期三 08时56分49秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
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

//哈希桶
template<typename K,typename V,typename HashFunc>
class HashBucket{
public:
	typedef HashBucketNode<K,V> Node;
public:
	HashBucket(const size_t size)
		:_size(0){
		_table.resize(size);
	}
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
	std::pair<Node*,bool> Insert(const K &key,const V &value);
	std::pair<Node*,bool> Find(const K &key);
	void Remove(const K &key);
protected:
	void _Check();
	void _HashFunc(const K&);
private:
	//禁止拷贝、赋值(懒人做法)
	HashBucket(const HashBucket&);
	HashBucket &operator=(const HashBucket&);
private:
	std::vector<Node*> _table;
	size_t _size;
};
