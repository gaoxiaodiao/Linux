/**************************************
*文件说明:并查集相关声明及实现
*作者:高小调
*创建时间:2017年05月04日 星期四 14时40分42秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<vector>
#include<iostream>
#include<cassert>
using std::cout;
using std::endl;
using std::vector;
class UnionSet{
	public:
		UnionSet(int size);
	public:
		void Union(const int root,const int e);
		int GetUnionNum();
		void Print(){
			for(int i=0; i<_array.size(); ++i){
				cout<<_array[i]<<" ";
			}
			cout<<endl;
		}
	protected:
		int GetRootIndex(const int e);
	private:
		vector<int> _array;
};

//构造函数
UnionSet::UnionSet(int size){
	_array.resize(size,-1);
}

//合并
void UnionSet::Union(const int e1,const int e2){
	assert(e1<_array.size());
	assert(e2<_array.size());
	int index = GetRootIndex(e1);
	_array[index] += _array[e2];
	_array[e2] = index;
}

//寻找根节点的index
int UnionSet::GetRootIndex(const int e){
	assert(e<_array.size());
	int index = e;
	while(_array[index] > -1){
		index = _array[index];
	}
	return index;
}

//获取集合数目
int UnionSet::GetUnionNum(){
	int count = 0;
	for(int i=0; i<_array.size(); ++i){
		if(_array[i] <= -1){
			count++;
		}
	}
	return count;
}
