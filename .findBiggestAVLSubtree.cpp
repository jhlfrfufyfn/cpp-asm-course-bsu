///16.1
#include <iostream>
#include <ostream>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <algorithm>
template<typename info_type>
class BNode {
public:
	info_type _info;
	BNode<info_type> *_left;
	BNode<info_type> *_right;
public:
	BNode<info_type>() : _info(0), _left(nullptr), _right(nullptr) {}
	BNode<info_type>(int info) : _info(info), _left(nullptr), _right(nullptr) {}
	BNode<info_type>(int info, BNode<info_type> *left, BNode<info_type> *right) : _info(info), _left(left), _right(right) {}
};

template<typename info_type>
class BTree {
public:
	BNode<info_type>* findBiggestAVLSubtree();
	BTree<info_type>();
	bool insert(info_type info);
	bool erase(info_type info);
	bool search(info_type info);
	void preOrder(std::ostream& out);
	void inOrder(std::ostream& out);
	void postOrder(std::ostream& out);
	size_t getSize();
	size_t height();
	bool empty();
private:
	BNode<info_type>* root;
	size_t size;
	bool insert(BNode<info_type> *& t, info_type info);
	bool erase(BNode<info_type> *& t, info_type info);
	bool search(BNode<info_type> * t, info_type info);
	void preOrder(BNode<info_type> * t, std::ostream& out);
	void inOrder(BNode<info_type> * t, std::ostream& out);
	void postOrder(BNode<info_type> * t, std::ostream& out);
	size_t height(BNode<info_type> * t);
	BNode<info_type>* createNode(info_type info);
	inline bool isReal(BNode<info_type> *p);
	int minimum(BNode<info_type> * t);
};

template<typename info_type>
BTree<info_type>::BTree() : root(nullptr) {}

template<typename info_type>
BNode<info_type>* indBiggestAVLSubtree(BNode<info_type> *root, int &maxChainSize, int &avlSize) {
	if (!root) {
		avlSize = 0;
		maxChainSize = 0;
		return nullptr;
	}

	///left call
	int leftAvlSize = 0;
	int leftMaxChainSize = 0;
	BNode<info_type> *leftNode = indBiggestAVLSubtree(root->_left, leftMaxChainSize, leftAvlSize);

	///right call
	int rightAvlSize = 0;
	int rightMaxChainSize = 0;
	BNode<info_type> *rightNode = indBiggestAVLSubtree(root->_right, rightMaxChainSize, rightAvlSize);

	///if we can union left and right
	if (abs(leftMaxChainSize - rightMaxChainSize) <= 1 && leftNode == root->_left && rightNode == root->_right) {
		maxChainSize = std::max(leftMaxChainSize, rightMaxChainSize) + 1;
		avlSize = leftAvlSize + rightAvlSize + 1;
		return root;
	}

	///if left avl subtree is bigger
	if (leftAvlSize > rightAvlSize) {
		avlSize = leftAvlSize;
		maxChainSize = leftMaxChainSize;
		return leftNode;
	}
	///then right avl subtree is bigger
	else {
		avlSize = rightAvlSize;
		maxChainSize = rightMaxChainSize;
		return rightNode;
	}
}


template<typename info_type>
BNode<info_type>* BTree<info_type>::findBiggestAVLSubtree()
{
	int f1 = 0, f2 = 0;
	return indBiggestAVLSubtree(root,f1,f2);
}

template<typename info_type>
bool BTree<info_type>::insert(info_type info) {
	bool ans = insert(root, info);
	if (ans)
		size++;
	return ans;
}

template<typename info_type>
bool BTree<info_type>::erase(info_type info) {
	bool ans = erase(root, info);
	if (ans)
		size--;
	return ans;
}

template<typename info_type>
bool BTree<info_type>::search(info_type info) {
	return search(root, info);
}

template<typename info_type>
void BTree<info_type>::preOrder(std::ostream& out) {
	preOrder(root, out);
}

template<typename info_type>
void BTree<info_type>::inOrder(std::ostream& out) {
	inOrder(root, out);
}

template<typename info_type>
void BTree<info_type>::postOrder(std::ostream& out) {
	postOrder(root, out);
}

template<typename info_type>
size_t BTree<info_type>::getSize() {
	return size;
}

template<typename info_type>
size_t BTree<info_type>::height() {
	return height(root);
}

template<typename info_type>
bool BTree<info_type>::empty() {
	return size == 0;
}

template<typename info_type>
bool BTree<info_type>::insert(BNode<info_type> *& t, info_type info) {
	if (t == nullptr) {
		t = createNode(info);
		return true;
	}
	else if (t->_info == info) {
		return false;
	}
	else if (t->_info < info) {
		return insert(t->_right, info);
	}
	else {
		return insert(t->_left, info);
	}
}

template<typename info_type>
bool BTree<info_type>::erase(BNode<info_type> *& t, info_type info) {
	if (t == nullptr)
		return false;
	if (t->_info < info)
		return erase(t->_right, info);
	else if (t->_info > info)
		return erase(t->_left, info);
	else {
		if (t->_left == nullptr && t->_right == nullptr)
			t = nullptr;
		else if (t->_left == nullptr&&t->_right != nullptr)
			t = t->_right;
		else if (t->_left != nullptr&&t->_right == nullptr)
			t = t->_left;
		else {
			t->_info = minimum(t->_right);
			erase(t->_right, t->_info);
		}
		return true;
	}
}

template<typename info_type>
bool BTree<info_type>::search(BNode<info_type> * t, info_type info) {
	if (t == nullptr)
		return false;
	else if (t->_info < info) {
		return search(t->_right, info);
	}
	else if (t->_info > info) {
		return search(t->_left, info);
	}
	else
		return true;
}

template<typename info_type>
void BTree<info_type>::preOrder(BNode<info_type> * t, std::ostream & out) {
	if (t) {
		out << t->_info << " ";
		preOrder(t->_left, out);
		preOrder(t->_right, out);
	}
}

template<typename info_type>
void BTree<info_type>::inOrder(BNode<info_type> * t, std::ostream & out) {
	if (t) {
		inOrder(t->_left, out);
		out << t->_info << " ";
		inOrder(t->_right, out);
	}
}

template<typename info_type>
void BTree<info_type>::postOrder(BNode<info_type> * t, std::ostream & out) {
	if (t) {
		postOrder(t->_left, out);
		postOrder(t->_right, out);
		out << t->_info << " ";
	}
}

template<typename info_type>
size_t BTree<info_type>::height(BNode<info_type> * t) {
	if (!t)
		return 0;
	else
		return size_t(std::max(height(t->_left), height(t->_right)) + 1);
}

template<typename info_type>
BNode<info_type> * BTree<info_type>::createNode(info_type info) {
	BNode<info_type> *newNode = new BNode<info_type>(info);
	return newNode;
}

template<typename info_type>
inline bool BTree<info_type>::isReal(BNode<info_type> * p) {
	return p != nullptr;
}

template<typename info_type>
int BTree<info_type>::minimum(BNode<info_type> * t) {
	if (t->_left == nullptr)
		return t->_info;
	else
		return minimum(t->_left);
}




int main() {
	BTree<int> tree;
	for (int i : {10,5,15,12,17,19,13}) {
		tree.insert(i);
	}
	BNode<int>* node = tree.findBiggestAVLSubtree();
	std::cerr << node->_info << std::endl;
	system("pause");
	return 0;
}
