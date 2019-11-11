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
	HashNode() :_key(0), _value(0), _next(nullptr) {}
	HashNode(const keyType &k, const valueType &v) :_key(k), _value(v), _next(nullptr) {}

	keyType getKey()const {
		return _key;
	}
	
	valueType getValue()const {
		return _value;
	}

	HashNode* getNext()const {
		return _next;
	}

	void setKey(const keyType& key) {
		_key=key;
	}

	void setValue(const valueType& value) {
		_value=value;
	}
	
	void setNext(HashNode *next) {
		_next=next;
	}

private:
	keyType _key;
	valueType _value;
	HashNode *_next;
};

///=============================================================================================================================

class HashTable {
public:
	///constructor
	HashTable():size(0) {
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
		if (this == &other) {
			return *this;
		}
		HashTable t(other);
		swap(t);
		return t;
	}
	/*
	valueType& operator[](const keyType& key) {
		int hash=getHashByKey(key);
		HashNode *p=_nodes[hash];
		while (p) {
			p=p->getNext();
		}
		p=new HashNode();
		p->setKey(key);
		re
	}

	valueType operator[](const keyType& key)const {
		int hash = getHashByKey(key);
		HashNode *p = _nodes[hash];
		while (p) {
			p = p->getNext();
		}
		p->setNext(new HashNode())
	}*/
	//istream& operator>>(istream& in, );
	//ostream& operator<<(ostream& out, );
	bool isEmpty();
	int getSize();
	int find();
	int erase();
	void swap(HashTable& other);
private:
	const int TABLE_SIZE = 1000;
	const int PRIME=237;
	vector<HashNode*> _nodes;
	unsigned int size;

	///auxiliary function for constructor
	void initNodes() {
		_nodes.resize(TABLE_SIZE,nullptr);
	}

	///function that makes *this a copy of given hashtable
	void copy(const HashTable& ht) {
		for (int i = 0;i < TABLE_SIZE;i++) {
			if (ht._nodes[i] != nullptr) {
				HashNode *pHT=ht._nodes[i];
				HashNode *pThis=this->_nodes[i];
				while (pHT) {
					pThis=new HashNode(pHT->getKey(),pHT->getValue());
					pHT=pHT->getNext();
					pThis=pThis->getNext();
				}
			}
		}
	}
	
	void clear() {
		for (int i = 0;i < TABLE_SIZE;i++) {
			HashNode *p=_nodes[i];
			while (p) {
				HashNode *t=p;
				p=p->getNext();
				delete t;
			}
		}
	}

	void swap(HashTable& other) {
		swap(size,other.size);
		for (int i = 0;i < TABLE_SIZE;i++) {
			swap(_nodes[i],other._nodes[i]);
		}
	}

	int getHashByKey(keyType const& key)const {
		int hash=0;
		int currPrime=1;
		for (auto it : key) {
			hash+=it*currPrime;
			currPrime*=currPrime;
			hash%=TABLE_SIZE;
			currPrime%=TABLE_SIZE;
		}
		return hash;
	}

};

///=============================================================================================================================

int main() {

}
