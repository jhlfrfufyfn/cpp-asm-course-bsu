#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
using namespace std;
///============================================================================================================================
template<typename keyType,typename valueType>
class HashNode{
public:
	HashNode():_key(0),_value(0),_next(nullptr){}
	HashNode(const keyType &k, const valueType &v):_key(k),_value(v),_next(nullptr){}
	keyType& getKey()const;
	valueType& getValue()const;
	HashNode* getNext()const;
	void setKey(const keyType& key);
	void setValue(const valueType& value);
	void setNext(const nextType& next);
private:
	keyType _key;
	valueType _value;
	HashNode *_next;
	HashNode(const HashNode&);
	HashNode& operator=(const HashNode&);
	void copy();
	void swap();
	void deleteNext(HashNode* p);
};
void HashNode::copy(){
	
}
void HashNode::deleteNext(HashNode *&p){
	if(p->next)
		deleteNext(p->next);
	delete p;
}
HashNode::HashNode(const HashNode &other){
	deleteNext(next);
	n
}
keyType& HashNode::getKey()const{
	return _key;
}
valueType& HashNode::getValue()const{
	return _value;
}
HashNode* HashNode::getNext()const{
	return _next;
}
void HashNode::setKey(const keyType& key){
	_key=key;
}
void HashNode::setValue(const valueType& value){
	_value=value;
}
void HashNode::setNext(HashNode* next){
	_next=next;
}
///=============================================================================================================================
template<typename keyType,typename valueType>
class HashTable {
public:
	HashTable();
	~HashTable();
	HashTable& operator=(HashTable& other);
	valueType& operator [](const keyType& key);
	HashNode& operator =(const keyType& key);
	//istream& operator>>(istream& in, );
	//ostream& operator<<(ostream& out, );
	bool isEmpty();
	int getSize();
	int find();
	int erase();
	void swap(HashTable& other);
private:
	const int TABLE_SIZE=1000;
	vector<HashNode<keyType,valueType>> nodes;
};
///=============================================================================================================================

int main(){
	
}
