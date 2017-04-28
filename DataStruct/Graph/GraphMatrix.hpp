/**************************************
*文件说明:图相关声明及实现(邻接矩阵)
*作者:高小调
*创建时间:2017年04月28日 星期五 11时59分55秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<vector>
using namespace std::vector;
template<typename V,typename W>
class GraphMatrix{
	public:
		GraphMatrix(const V*,size_t,const W&,bool);	//构造函数
	public:
		void AddEdge(const V&,const V&,const W&);	//添加一条边
	protected:
		size_e GetVertexIndex(const V&);			//获取顶点下标
	private:
		vector<V> _vertex;					//顶点集合
		vector<vector<W>> _matrix			//顶点与边的关系
		bool _IsDigraph;					//是否为有向图
};
