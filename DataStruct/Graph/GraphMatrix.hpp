/**************************************
*文件说明:图相关声明及实现(邻接矩阵)
*作者:高小调
*创建时间:2017年04月28日 星期五 11时59分55秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __GRAPHMATRIX_H__
#define __GRAPHMATIRX_H__
#include<vector>
using std::vector;
template<typename V,typename W>
class GraphMatrix{
#ifdef __GRAPHMATRIX_DEBUG__
	friend void TestGraphMatrix();
#endif
	public:
		GraphMatrix(const V*,int,const W& a=W(),bool b=false);//构造函数
	public:
		void AddEdge(const V&,const V&,const W&);	//添加一条边
	protected:
		int GetVertexIndex(const V&);			//获取顶点下标
	private:
		vector<V> _vertex;					//顶点集合
		vector<vector<W>> _matrix;			//顶点与边的关系
		bool _IsDigraph;					//是否为有向图
};

//构造函数
template<typename V,typename W>
GraphMatrix<V,W>::GraphMatrix(const V* vertex,int size,const W& invalid,bool IsDigraph)
	:_vertex(vertex,vertex+size)
	,_IsDigraph(IsDigraph){
		for(int i=0; i<size; ++i){
			_matrix.push_back(vector<W>());
			_matrix.back().resize(size,invalid);
		}
}

//获取顶点下标
template<typename V,typename W>
int GraphMatrix<V,W>::GetVertexIndex(const V& vertex){
	int index = 0;
	for(int i=0; i<_vertex.size(); ++i){
		if(_vertex[i] == vertex){
			return i;
		}
	}
	return -1;
}

//添加一条边
template<typename V,typename W>
void GraphMatrix<V,W>::AddEdge(const V& v1,const V& v2,const W& weight){
	int index1 = GetVertexIndex(v1);
	int index2 = GetVertexIndex(v2);
	if(index1 == -1 || index2 == -1){
		return ;
	}
	_matrix[index1][index2] = weight;
	if(!_IsDigraph){
		_matrix[index2][index1] = weight;
	}
}

/*
template<typename V,typename W>
GraphMatrix<V,W>::
template<typename V,typename W>
GraphMatrix<V,W>::
template<typename V,typename W>
GraphMatrix<V,W>::
template<typename V,typename W>
GraphMatrix<V,W>::
template<typename V,typename W>
GraphMatrix<V,W>::

*/

#endif
