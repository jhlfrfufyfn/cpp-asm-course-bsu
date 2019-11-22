#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
using namespace std;
///============================================================================================================================
typedef string keyType;
typedef int valueType;
class HashNode {
public:
	HashNode() :_key(""), _value(0), _next(nullptr) {}
	HashNode(const keyType &k, const valueType &v) :_key(k), _value(v), _next(nullptr) {}
	keyType _key;
	valueType _value;
	HashNode *_next;
};
///реализовать find
///написать свое расширение памяти поддерживая коэффицент заполнения

///=============================================================================================================================

class HashTable {
public:

	///constructor
	HashTable() :_size(0) {
		initNodes();
	}
	///constructor with another hash table
	HashTable(const HashTable& other) {
		HashTable();
		copy(other);
	}

	///destructor
	~HashTable() { clear(); }

	///overloaded operator= 
	HashTable& operator=(const HashTable& other) {
		if (this != &other) {
			HashTable t(other);
			swap(t);
		}
		return *this;
	}

	///modifies value by key
	valueType& operator[](const keyType& key) {
		int hash = getHashByKey(key);
		HashNode **p = &_nodes[hash];
		bool was = 0;
		while (*p) {
			if ((*p)->_key == key) {
				was = 1;
				break;
			}
			p = &((*p)->_next);
		}
		if (!was) {
			*p = new HashNode();
			(*p)->_key = key;
		}
		return (*p)->_value;
	}

	///checks if hashTable is empty
	bool isEmpty()const {
		return (_size == 0);
	}

	///gets size
	int getSize()const {
		return _size;
	}

	void erase(const keyType& key) {
		int hash = getHashByKey(key);
		HashNode **p = &_nodes[hash];
		HashNode **last = nullptr;
		HashNode **nodeErased = nullptr;
		while (*p) {
			if ((*p)->_key == key) {
				nodeErased = p;
				if (last != nullptr)
					(*last)->_next = (*p)->_next;
				break;
			}
			last = p;
			p = &((*p)->_next);
		}
		*p = nullptr;
	}


	void swap(HashTable& other) {
		std::swap(_size, other._size);
		for (int i = 0;i < TABLE_SIZE;i++) {
			std::swap(_nodes[i], other._nodes[i]);
		}
	}

private:
	const int TABLE_SIZE = 1000;
	const int PRIME = 237;
	vector<HashNode*> _nodes;
	int _size;

	///auxiliary function for constructor
	void initNodes() {
		_nodes.resize(TABLE_SIZE, nullptr);
	}

	///function that makes *this a copy of given hashtable
	void copy(const HashTable& ht) {
		for (int i = 0;i < TABLE_SIZE;i++) {
			if (ht._nodes[i] != nullptr) {
				HashNode *pHT = ht._nodes[i];
				HashNode *pThis = this->_nodes[i];
				while (pHT) {
					pThis = new HashNode(pHT->_key, pHT->_value);
					pHT = pHT->_next;
					pThis = pThis->_next;
				}
			}
		}
	}

	///clears the hash table
	void clear() {
		for (int i = 0;i < TABLE_SIZE;i++) {
			HashNode *p = _nodes[i];
			while (p) {
				HashNode *t = p;
				p = p->_next;
				delete t;
			}
		}
	}

	///returns the hash by key
	int getHashByKey(keyType const& key)const {
		int hash = 0;
		int currPrime = 1;
		for (auto it : key) {
			hash += it*currPrime;
			currPrime *= currPrime;
			hash %= TABLE_SIZE;
			currPrime %= TABLE_SIZE;
		}
		return hash;
	}

};

///=============================================================================================================================

int main() {
	HashTable table;
	table["a"] = 1;
	cout << table["a"] << "\n";
	table["a"] = 3;
	table["a"] = 1;
	table["b"] = 2;
	table["b"] = 31;
	cout << table["a"] << " " << table["b"] << "\n";
	table.erase("a");
	cout << table["a"] << " " << table["b"] << "\n";
	cout << table["a"] << "\n";
	return 0;
}
