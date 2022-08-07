#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iterator>
#include <unordered_map>
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

///=============================================================================================================================

class HashTable {
public:

	///constructor
	HashTable();

	///constructor with another hash table
	HashTable(const HashTable& other);

	///destructor
	~HashTable() { clear(); }

	///overloaded operator= 
	HashTable& operator=(const HashTable& other);

	///modifies value by key
	valueType& operator[](const keyType& key);

	///checks if hashTable is empty
	bool isEmpty()const;

	///gets size
	int getSize()const;

	friend ostream& operator<<(std::ostream &out, const HashTable& tt);

	///returns flag if there is the key in the table
	bool find(const keyType& key) const;

	///erases element with key if exists
	void erase(const keyType& key);

	///swaps two tables
	void swap(HashTable& other);

private:
	size_t TABLE_SIZE = 100;			///initial size of the table

	const int PRIME = 237;			///prime number used for hashing

									///coefficient, used for recalculating of the TABLE_SIZE : if the real size is bigger 
									/// than TABLE_SIZE * EXPANDCOEF , than we make out table two times bigger
	const size_t EXPANDCOEF = 15;

	vector<HashNode*> _nodes;		///lists of the hashTable

	size_t _size;					///number of elements in hashtable

									///auxiliary function for constructor
	void initNodes();

	///function that makes *this a copy of given hashtable
	void copy(const HashTable& ht);

	///clears the hash table
	void clear();

	///calculates hash by key
	int getHashByKey(keyType const& key)const;

	///checks if rebuild is needed
	void checkRebuild();

	///expanses or squeezes the table
	void rebuildTable(bool);
};
///=============================================================================================================================
HashTable::HashTable() :_size(0)
{
	initNodes();
}

HashTable::HashTable(const HashTable & other) : _size(0)
{
	initNodes();
	copy(other);
}

HashTable & HashTable::operator=(const HashTable & other)
{
	if (this != &other) {
		HashTable t(other);
		swap(t);
	}
	return *this;
}

valueType & HashTable::operator[](const keyType & key)
{
	checkRebuild();
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
		_size++;
		*p = new HashNode();
		(*p)->_key = key;
	}
	return (*p)->_value;
}

bool HashTable::isEmpty() const
{
	return (_size == 0);
}

int HashTable::getSize() const
{
	return _size;
}

bool HashTable::find(const keyType & key) const
{
	int hash = getHashByKey(key);
	HashNode *p = _nodes[hash];
	while (p) {
		if (p->_key == key) {
			return true;
		}
		p = p->_next;
	}
	return false;
}

void HashTable::erase(const keyType & key)
{
	checkRebuild();
	int hash = getHashByKey(key);
	HashNode **p = &_nodes[hash];
	HashNode **last = nullptr;
	HashNode *nodeErased = nullptr;
	while (*p) {
		if ((*p)->_key == key) {
			nodeErased = *p;
			*p = (*p)->_next;
			_size--;
			break;
		}
		last = p;
		p = &((*p)->_next);
	}
	delete nodeErased;
}

void HashTable::swap(HashTable & other)
{
	std::swap(_size, other._size);
	for (int i = 0;i < TABLE_SIZE;i++) {
		std::swap(_nodes[i], other._nodes[i]);
	}
}

void HashTable::initNodes()
{
	_nodes.resize(TABLE_SIZE, nullptr);
}

void HashTable::copy(const HashTable & ht)
{
	_size = ht._size;
	for (int i = 0;i < TABLE_SIZE;i++) {
		if (ht._nodes[i] != nullptr) {
			HashNode *pHT = ht._nodes[i];
			HashNode **pThis = &(this->_nodes[i]);
			while (pHT) {
				*pThis = new HashNode(pHT->_key, pHT->_value);
				pHT = pHT->_next;
				pThis = &(*pThis)->_next;
			}
		}
	}
}

void HashTable::clear()
{
	_size = 0;
	for (int i = 0;i < TABLE_SIZE;i++) {
		HashNode *p = _nodes[i];
		while (p) {
			HashNode *t = p;
			p = p->_next;
			delete t;
		}
		_nodes[i] = nullptr;
	}
}

int HashTable::getHashByKey(keyType const & key) const
{
	int hash = 0;
	int currPrime = 1;
	for (auto it : key) {
		hash += it*currPrime;
		currPrime *= PRIME;
		hash %= TABLE_SIZE;
		currPrime %= TABLE_SIZE;
	}
	return hash;
}

void HashTable::checkRebuild()
{
	if (_size > TABLE_SIZE*EXPANDCOEF) {
		rebuildTable(1);
	}
	if (_size < TABLE_SIZE && TABLE_SIZE >= 200) {
		rebuildTable(0);
	}
}


void HashTable::rebuildTable(bool b)			///if b == 0 then squeeze, else expand
{
	vector<pair<keyType, valueType> > vec;
	for (int i = 0;i < TABLE_SIZE;i++) {
		HashNode *p = _nodes[i];
		while (p) {
			vec.push_back({ p->_key,p->_value });
			p = p->_next;
		}
	}
	clear();
	if (b)
		TABLE_SIZE *= 2;
	else {
		TABLE_SIZE /= 2;
	}
	_nodes.resize(TABLE_SIZE);
	for (const auto &it : vec) {
		int hash = getHashByKey(it.first);
		HashNode **p = &_nodes[hash];
		bool was = 0;
		while (*p) {
			if ((*p)->_key == it.first) {
				was = 1;
				break;
			}
			p = &((*p)->_next);
		}
		if (!was) {
			_size++;
			*p = new HashNode();
			(*p)->_key = it.first;
			(*p)->_value = it.second;
		}
	}
}
///=============================================================================================================================



HashTable func(HashTable f) {
	f["aa"] = 4;
	return f;
}


int main() {
	std::unordered_map<string, int> mp;
	HashTable table;
	for (char c1 = 'a';c1 <= 'z';c1++) {
		for (char c2 = 'a';c2 <= 'z';c2++) {
				string s = string(1, c1) + string(1, c2);
				mp[s] = (int)c1 + c2;
				table[s] = (int)c1 + c2;
		}
	}
	HashTable table2 = func(table);
	cout << table << std::endl << std::endl << table2;
	for (char c1 = 'z';c1 >= 'a';c1--) {
		for (char c2 = 'r';c2 >= 'a';c2--) {
				string s = string(1, c1) + string(1, c2);
				mp.erase(s);
				table.erase(s);
		}
	}

	ofstream errorOut("errorLog.txt");

	for (char c1 = 'a';c1 <= 'z';c1++) {
		for (char c2 = 'a';c2 <= 'z';c2++) {
			string s = string(1, c1) + string(1, c2);
			bool bMap = mp.find(s) != mp.end();
			bool bTable = table.find(s);
			if (bMap != bTable) {
				errorOut << s << endl;
			}
		}
	}
	system("pause");
	return 0;
}

ostream & operator<<(std::ostream & out, const HashTable & tt)
{
	for (int i = 0;i < tt.TABLE_SIZE;i++) {
		HashNode *p = tt._nodes[i];
		while (p) {
			out << p->_key << " " << p->_value << std::endl;
			p = p->_next;
		}
	}
	return out;
}
