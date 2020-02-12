#pragma once

#include <fstream>
#include <algorithm>

template<typename info_type>
class BNode {
public:
	info_type _info;
	BNode<info_type>* _left;
	BNode<info_type>* _right;
public:
	BNode<info_type>() : _info(0), _left(nullptr), _right(nullptr) {}
	BNode<info_type>(const info_type& info) : _info(info), _left(nullptr), _right(nullptr) {}
	BNode<info_type>(const info_type& info, BNode<info_type>* left, BNode<info_type>* right) : _info(info), _left(left), _right(right) {}
	BNode<info_type>(BNode<info_type>* node) {
		clear(this);
		*this = BNode();
		copy(node);
	}

private:

	void copy(BNode<info_type>* node) {
		if (node == nullptr) {
			return;
		}
		copy(node->_left);
		copy(node->_right);
		this->_info = node->_info;
	}

	void clear(BNode<info_type>* node) {
		if (node == nullptr)
			return;
		BNode<info_type>* curr = node;
		clear(node->_left);
		clear(node->_right);
		delete curr;
	}

};

template<typename info_type>
class BTree {
public:
	BTree<info_type>();
	BTree<info_type>(const BTree<info_type>& tree);

	bool insert(const info_type&);
	bool erase(const info_type&);
	void clear();

	bool search(const info_type& info);
	void preOrder(std::ostream& out);
	void inOrder(std::ostream& out);
	void postOrder(std::ostream& out);

	size_t getSize();
	size_t height();
	bool empty();


private:
	bool insert(BNode<info_type>*& t, const info_type& info);
	bool erase(BNode<info_type>*& t, const info_type& info);
	bool search(BNode<info_type>* t, const info_type& info);
	void preOrder(BNode<info_type>* t, std::ostream& out);
	void inOrder(BNode<info_type>* t, std::ostream& out);
	void postOrder(BNode<info_type>* t, std::ostream& out);
	size_t height(BNode<info_type>* t);
	BNode<info_type>* createNode(const info_type& info);
	inline bool isReal(BNode<info_type>* p);
	int minimum(BNode<info_type>* t);

	BNode<info_type>* root;
	size_t size;
};


template<typename info_type>
BTree<info_type>::BTree() : root(nullptr), size(0) {}

template<typename info_type>
BTree<info_type>::BTree(const BTree<info_type>& tree) : root(nullptr), size(0) {
	root = new BNode<info_type>(tree.root);
}

template<typename info_type>
bool BTree<info_type>::insert(const info_type& info) {
	if (insert(root, info) == true) {
		size++;
		return true;
	}
	return false;
}

template<typename info_type>
bool BTree<info_type>::erase(const info_type& info) {
	if (erase(root, info) == true) {
		size--;
		return true;
	}
	return false;
}

template<typename info_type>
bool BTree<info_type>::search(const info_type& info) {
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
inline void BTree<info_type>::clear() {
	size = 0;
	root.clear();
}

template<typename info_type>
bool BTree<info_type>::insert(BNode<info_type>*& t, const info_type& info) {
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
bool BTree<info_type>::erase(BNode<info_type>*& t, const info_type& info) {
	if (t == nullptr)
		return false;
	if (t->_info < info)
		return erase(t->_right, info);
	else if (t->_info > info)
		return erase(t->_left, info);
	else {
		if (t->_left == nullptr && t->_right == nullptr)
			t = nullptr;
		else if (t->_left == nullptr && t->_right != nullptr)
			t = t->_right;
		else if (t->_left != nullptr && t->_right == nullptr)
			t = t->_left;
		else {
			t->_info = minimum(t->_right);
			erase(t->_right, t->_info);
		}
		return true;
	}
}

template<typename info_type>
bool BTree<info_type>::search(BNode<info_type>* t, const info_type& info) {
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
void BTree<info_type>::preOrder(BNode<info_type>* t, std::ostream& out) {
	if (t) {
		out << t->_info << " ";
		preOrder(t->_left, out);
		preOrder(t->_right, out);
	}
}

template<typename info_type>
void BTree<info_type>::inOrder(BNode<info_type>* t, std::ostream& out) {
	if (t) {
		inOrder(t->_left, out);
		out << t->_info << " ";
		inOrder(t->_right, out);
	}
}

template<typename info_type>
void BTree<info_type>::postOrder(BNode<info_type>* t, std::ostream& out) {
	if (t) {
		postOrder(t->_left, out);
		postOrder(t->_right, out);
		out << t->_info << " ";
	}
}

template<typename info_type>
size_t BTree<info_type>::height(BNode<info_type>* t) {
	if (!t)
		return 0;
	else
		return size_t(std::max(height(t->_left), height(t->_right)) + 1);
}

template<typename info_type>
BNode<info_type>* BTree<info_type>::createNode(const info_type& info) {
	BNode<info_type>* newNode = new BNode<info_type>(info);
	return newNode;
}

template<typename info_type>
inline bool BTree<info_type>::isReal(BNode<info_type>* p) {
	return p != nullptr;
}

template<typename info_type>
int BTree<info_type>::minimum(BNode<info_type>* t) {
	if (t->_left == nullptr)
		return t->_info;
	else
		return minimum(t->_left);
}

