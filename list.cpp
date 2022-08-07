#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
typedef long long ll;
class KNode {
public:
	KNode() :info(0), next(nullptr) {}
	explicit KNode(int aInfo) :info(aInfo) {}
	KNode(int aInfo, KNode *aNext) :info(aInfo), next(aNext) {}
	int info;
	KNode *next;
};


class KList {
private:
	KNode *fpFirst;///pointer to the first node of the list
	KNode **fppLast;///pointer to the pointer to the first void(nullptr) node of the list(so we could do pushBack easily)
	unsigned int fSize;///number of nodes in the list

	///function that makes (*this) a copy of given list, that starts from node p
	void Copy(KNode *p) {
		while (p) {
			this->pushBack(p->info);
			p = p->next;
		}
	}

	///function that swaps pointers of list (t) and list (*this)
	void Swap(KList &t) {
		swap(this->fpFirst, t.fpFirst);
		swap(this->fppLast, t.fppLast);
	}

	void Clear() {
		while (fSize)
			erase(fSize - 1);
	}
public:
	///constructor, creates an empty list
	KList() :fpFirst(nullptr), fppLast(&fpFirst), fSize(0) {}

	///constructor, creates a copy of given list (lst)
	KList(KList const& lst) :fpFirst(nullptr), fppLast(&fpFirst), fSize(0) {
		Copy(lst.fpFirst);
	}


	///overloaded operator= , creates a copy of the given list and swaps this copy with our list; unused copy is erased automatically
	KList& operator=(KList const& l2) {
		if (this == &l2) {
			return *this;
		}
		KList t(l2);
		this->Swap(t);
		return *this;
	}

	///function, creates a node with value x and pushes it to the beginning
	void pushFront(int x) {
		fSize++;
		fpFirst = new KNode(x, fpFirst);
		if (fpFirst->next == nullptr) {
			fppLast = &(fpFirst->next);
		}
	}

	///function, creates a node with value x and pushes it to the end
	void pushBack(int x) {
		fSize++;
		(*fppLast) = new KNode(x);
		fppLast = &((*fppLast)->next);
	}

	///returs size of the list
	int getSize()const {
		return fSize;
	}

	///returns flag of emptyness
	bool isEmpty()const {
		return !getSize();
	}

	///erases the last element of the list
	void popBack() {
		if (isEmpty()) {
			throw out_of_range("Cannot delete from the empty list");
		}
		erase(fSize - 1);
	}

	///erases the first element of the list
	void popFront() {
		if (isEmpty()) {
			throw out_of_range("Cannot delete from the empty list");
		}
		erase(0);
	}

	///calculates summation of infos of all nodes in the list
	int countSum()const {
		KNode *p = fpFirst;
		int sum = 0;
		while (p) {
			sum += p->info;
			p = p->next;
		}
		return sum;
	}


	///outputs all the infos from the list, separated with space ' '
	friend ostream& operator<<(ostream &out, const KList &l) {
		const char DIVISER = ' ';
		KNode *p = l.fpFirst;
		while (p) {
			out << p->info << DIVISER;
			p = p->next;
		}
		return out;
	}

	///reverses the list
	void reverse() {
		KNode *p = fpFirst;
		KNode *origPrev = nullptr;
		KNode *prev = origPrev;
		KNode *nextP = nullptr;
		while (p) {
			nextP = p->next;
			p->next = prev;
			if (nextP == nullptr)
				break;
			prev = p;
			p = nextP;
		}
		fpFirst = p;
		fppLast = &origPrev;
	}

	///accesses the index's element
	int& operator[](int index) {
		if (index >= (int)fSize || index < 0) {
			throw out_of_range("list index is out of range");
		}
		KNode *currentNode = fpFirst;
		for (int i = 0;i < index;i++) {
			currentNode = currentNode->next;
		}
		return currentNode->info;
	}


	void erase(int index) {
		if (index >= (int)fSize || index < 0) {
			throw out_of_range("list index is out of range");
		}
		KNode *currentNode = fpFirst;
		KNode *lastNode = nullptr;
		for (int i = 0;i < index;i++) {
			lastNode = currentNode;
			currentNode = currentNode->next;
		}
		if (currentNode->next == nullptr) {
			fppLast = &currentNode->next;
		}
		if (lastNode == nullptr) {
			fpFirst = fpFirst->next;
			currentNode->next = nullptr;
		}
		else {
			lastNode->next = currentNode->next;
			currentNode->next = nullptr;
		}
		delete currentNode;
		fSize--;
	}

	///inserts to be [index] element
	void insert(int index, int info) {
		if (index<0 || index>fSize) {
			throw out_of_range("list index is out of range");
		}
		KNode *curr = fpFirst;
		KNode *last = nullptr;
		for (int i = 0;i < index;i++) {
			last = curr;
			curr = curr->next;
		}
		KNode *p = new KNode(info, curr);
		if (last) {
			last->next = p;
		}
		else {
			fpFirst = p;
		}
		fSize++;
	}

	///return the index of the first node with info equals value
	int findFirst(int value) {
		KNode *p = fpFirst;
		int i = 0;
		while (p) {
			if (p->info == value) {
				return i;
			}
			i++;
			p = p->next;
		}
		return -1;
	}

	///checks if first n elements of p1 are equal to first n elements of p2, use carefully, exceptions aren't prewritten
	friend const pair<KNode*, bool> compareLists(KNode* p1, KNode* p2, int n) {
		if (p2 == nullptr) {
			return{ p1,true };
		}
		vector<int> vec1, vec2;
		KNode* it = p1;
		while (it) {
			vec1.push_back(it->info);
			it = it->next;
		}
		it = p2;
		while (it) {
			vec2.push_back(it->info);
			it = it->next;
		}
		vector<int>::iterator iter = search(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
		if (iter != vec1.end()) {
			it = p1;
			int sz = iter - vec1.begin();
			while (it->info != vec2.back() && it->next != nullptr)
				it = it->next;
			it = it->next;
			return{ it,true };
		}
		else
			return{ nullptr,false };
	}

	///destructor
	~KList() {
		Clear();
	}
};
void input(KList &l, const string& sFile, char diviser) {
	ifstream in(sFile);
	string str;
	getline(in, str, diviser);
	stringstream ss;
	ss << str;
	if (in) {
		int x;
		while (ss >> x) {
			l.pushBack(x);
		}
	}
}

int main() {
	KList list1;
	input(list1, "input.txt", '%');
	list1.popFront();
	cout<<list1;
	system("pause");
	return 0;
}
