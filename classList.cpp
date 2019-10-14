#include <iostream>
#include <fstream>
#include <vector>
#include <random>
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
public:
	KList() :fpFirst(nullptr), fppLast(&fpFirst), fSize(0) {}
	void PushFront(int x) {
		fSize++;
		fpFirst=new KNode(x,fpFirst);
		if (fpFirst->next == nullptr) {
			fppLast=&(fpFirst->next);
		}
	}
	void PushBack(int x) {
		fSize++;
		(*fppLast)=new KNode(x);
		fppLast=&((*fppLast)->next);
	}

	int Size() {
		return fSize;
	}

	int Summa() {
		KNode *p=fpFirst;
		int sum=0;
		while (p) {
			sum+=p->info;
			p=p->next;
		}
		return sum;
	}

