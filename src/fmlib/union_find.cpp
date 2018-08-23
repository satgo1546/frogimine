//=============================================================================
// ■ FM::UnionFind
//-----------------------------------------------------------------------------
//   并查集。也称为disjoint-set或merge-find set。
//=============================================================================

template <size_t size> class UnionFind {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	size_t parent[size];
	size_t ancestor(size_t i) {
		return parent[i] == i ? i : (parent[i] = ancestor(parent[i]));
	}
public:
	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	UnionFind() {
		for (size_t i = 0; i < size; i++) parent[i] = i;
	}
	//-------------------------------------------------------------------------
	// ● 合并
	//   “union”是关键字。
	//-------------------------------------------------------------------------
	void merge(size_t a, size_t b) {
		parent[ancestor(b)] = ancestor(a);
	}
	//-------------------------------------------------------------------------
	// ● 是否在同一集合内？
	//-------------------------------------------------------------------------
	bool is_relative(size_t a, size_t b) {
		return ancestor(a) == ancestor(b);
	}
};
