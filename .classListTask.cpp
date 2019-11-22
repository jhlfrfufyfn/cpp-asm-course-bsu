#include <iostream>
#include <fstream>
#include <vector>
#include <random>
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
public:
	KList() :fpFirst(nullptr), fppLast(&fpFirst), fSize(0) {}
	void PushFront(int x) {
		fSize++;
		fpFirst = new KNode(x, fpFirst);
		if (fpFirst->next == nullptr) {
			fppLast = &(fpFirst->next);
		}
	}
	void PushBack(int x) {
		fSize++;
		(*fppLast) = new KNode(x);
		fppLast = &((*fppLast)->next);
	}

	int Size() {
		return fSize;
	}

	int Summa() {
		KNode *p = fpFirst;
		int sum = 0;
		while (p) {
			sum += p->info;
			p = p->next;
		}
		return sum;
	}
	friend const pair<KNode*,bool> compareLists(KNode* p1,KNode* p2,int n) {
		if (p2 == nullptr) {
			return{ p1,true };
		}
		vector<int> vec1,vec2;
		KNode* it=p1;
		while (it) {
			vec1.push_back(it->info);
			it=it->next;
		}
		it=p2;
		while (it) {
			vec2.push_back(it->info);
			it=it->next;
		}
		vector<int>::iterator iter=search(vec1.begin(),vec1.end(),vec2.begin(),vec2.end());
		if (iter != vec1.end()) {
			it = p1;
			int sz=iter-vec1.begin();
			while(it->info!=vec2.back()&&it->next!=nullptr)
				it=it->next;
			it=it->next;
			return {it,true};
		}
		else
			return{ nullptr,false };
	}
	friend const bool checkTask(const KList& L, const KList& L1, const KList& L2, const KList& L3, const KList& L4) {
		bool ans=1;
		KNode* pL=L.fpFirst;
		pair<KNode*,bool> res1=compareLists(pL,L1.fpFirst,L1.fSize);
		if(res1.second==false)
			ans=0;
		pL=res1.first;
		pair<KNode*, bool> res2 = compareLists(pL, L2.fpFirst, L2.fSize);
		if (res2.second == false)
			ans = 0;
		pL = res2.first;
		pair<KNode*, bool> res3 = compareLists(pL, L3.fpFirst, L3.fSize);
		if (res3.second == false)
			ans = 0;
		pL = res3.first;
		pair<KNode*, bool> res4 = compareLists(pL, L4.fpFirst, L4.fSize);
		if (res4.second == false)
			ans = 0;
		pL = res4.first;
		return ans;
	}
private:
	KNode *fpFirst;
	KNode **fppLast;
	unsigned int fSize;
};
KList input(const string sFile) {
	ifstream in(sFile);
	KList l;
	if (in) {
		int x;
		while (in >> x) {
			l.PushBack(x);
		}
	}
	return l;
}
int main() {
	KList L=input("inputL.txt");
	KList Ls1=input("inputL1.txt");
	KList Ls2=input("inputL2.txt");
	KList Ls3=input("inputL3.txt");
	KList Ls4=input("inputL4.txt");
	cout<<checkTask(L,Ls1,Ls2,Ls3,Ls4)<<"\n";
	system("pause");
	return 0;
}
