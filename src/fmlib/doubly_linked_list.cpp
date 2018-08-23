//=============================================================================
// ■ FM::DoublyLinkedList
//-----------------------------------------------------------------------------
//   双向链表的类。
//   此处的实现没有使用new和delete，而是在预先分配好的内存池中创建元素的。
//=============================================================================

template <class T, size_t size> class DoublyLinkedList {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
private:
	Node data[size];
	bool data_used[size];
public:
	Node* head;
	Node* tail;
	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	DoublyLinkedList() {
		memset(data_used, 0, sizeof(data_used));
		head = tail = NULL;
	}
	//-------------------------------------------------------------------------
	// ● 分配一个空结点
	//   不能分配时返回NULL。
	//-------------------------------------------------------------------------
	Node* new_node() {
		for (size_t i = 0; i < size; i++) {
			if (!data_used[i]) {
				data_used[i] = true;
				return &data[i];
			}
		}
		return NULL;
	}
	//-------------------------------------------------------------------------
	// ● 插入于之前
	//-------------------------------------------------------------------------
	void insert(Node* node, T x) {
		Node* y = new_node();
		y->data = x;
		assert((bool) head == (bool) tail);
		if (head) {
			y->prev = node->prev;
			y->next = node;
			if (node->prev) node->prev->next = y;
			node->prev = y;
		} else {
			y->prev = NULL;
			y->next = NULL;
			head = tail = y;
		}
	}
	//-------------------------------------------------------------------------
	// ● 插入于之后
	//-------------------------------------------------------------------------
	void append(Node* node, T x) {
		Node* y = new_node();
		y->data = x;
		assert((bool) head == (bool) tail);
		if (head) {
			y->prev = node;
			y->next = node->next;
			if (node->next) node->next->prev = y;
			node->next = y;
		} else {
			y->prev = NULL;
			y->next = NULL;
			head = tail = y;
		}
	}
	//-------------------------------------------------------------------------
	// ● 删除结点
	//-------------------------------------------------------------------------
	void remove(Node* node) {
		data_used[node - data] = false;
		if (node->prev) {
			node->prev->next = node->next;
		} else {
			head = node->next;
		}
		if (node->next) {
			node->next->prev = node->prev;
		} else {
			tail = node->prev;
		}
	}
};
