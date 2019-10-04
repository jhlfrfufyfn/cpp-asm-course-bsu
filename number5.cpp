#include <iostream> 
#include <algorithm>
#include <vector>
using namespace std;
int currFi,currFi1,currFi2,currSum,Xi;
int funcP1(int n, int x) {
	__asm {
		///initialize x^n +
		///initialize f0,f1 +
		///initialize sum before 1 including +
		///write a cycle +
		mov currSum, 0;
		mov Xi, 1;
		mov currFi1,1;
		mov currFi2,1;
		mov ecx,n;
		mov eax,1;
	c1:
		mul x;
	loop c1;
		mov Xi,eax;
		add currSum,eax;
		mov eax,Xi;
		mov ecx,x;
		mov edx,0;
		div ecx;
		mov Xi,eax;
		add currSum,eax;
		mov ecx,currFi1;
		mov currFi,ecx;
		mov ecx,currFi2;
		add currFi,ecx;
		mov ecx, n;
		dec ecx;
	c2:
		///recalc Xi +
		///process currSum +
		///recalc currFi(1)(2) +
		push ecx;
		mov ecx,x;
		mov eax,Xi;
		mov edx,0;
		div ecx;
		pop ecx;
		mov Xi,eax;
		mul currFi;
		add currSum, eax;
		push currFi;
		push ecx;
		mov ecx,currFi1;
		mov currFi2,ecx;
		add currFi,ecx;
		pop ecx;
		pop currFi1;
	loop c2;
		mov eax,currSum;
	}
}
int funcP2(int n, int x) {
	__asm {
		///initialize x^0 +
		///initialize f0,f1 +
		///initialize sum before 1 including +
		///write a cycle +		
		mov currSum,0;
		mov Xi, 1;
		mov currFi1, 1;
		mov currFi2, 1;
		mov eax, 1;
		mov Xi, eax;
		add currSum, eax;
		mov eax, Xi;
		mov ecx, x;
		mul ecx;
		mov Xi, eax;
		add currSum, eax;
		mov ecx,currFi1;
		mov currFi, ecx;
		mov ecx,currFi2;
		add currFi, ecx;
		mov ecx, n;
		dec ecx;
	c2:
		///recalc Xi +
		///process currSum +
		///recalc currFi(1)(2)+
		push ecx;
		mov ecx, x;
		mov eax, Xi;
		mul ecx;
		pop ecx;
		mov Xi, eax;
		mul currFi;
		add currSum, eax;
		push currFi;
		push ecx;
		mov ecx, currFi1;
		mov currFi2, ecx;
		add currFi, ecx;
		pop ecx;
		pop currFi1;
	loop c2;
		mov eax, currSum;
	}
}
int main()
{
	int n,x;
	cout<<"Enter n,x:\n ";
	cin>>n>>x;
	cout<<"p1 = "<<funcP1(n,x)<<"\np2 = "<<funcP2(n,x)<<"\n";
	system("pause");
	return 0;
}
