#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
int tenSt,maxC,currC;
void changeA(int x) {
	__asm {
		mov eax,x;
		mov ecx, 100;
		mov esi, 10;
		loopStart1:
			mov edx,0;
			div esi;
			cmp eax, 0;
			je exitCycle;
		loop loopStart1;
		exitCycle:
		mov edx, 100;
		sub edx, ecx;
		inc edx;
		push edx;///top of stack is number of digits;
		///===================================================================================================
		mov eax,x;
		mov ecx,100;
		mov esi,10;
		mov edi, 0;
		loopStart2:
			mov edx,0;
			div esi;
			cmp edi,edx;
			jge noReplace;
			mov edi,edx;
			noReplace:
			cmp eax,0;
			je exitCycle2;
		loop loopStart2;
		exitCycle2:
		mov maxC, edi;///maxC is maxCifr
		///==================================================================================
		mov eax,x;///number to divide
		mov ecx,100;///cycle counter
		mov edx,0;
		mov esi,10;///ten
		mov edi,0;///final number
		mov tenSt,1;
		loopStart3:
			///get a current cifr;
			mov edx,0;
			div esi;
			mov currC, edx;
			///current cifr is in top of stack;
			///calculate (ten degree)*(current cifr)
			push eax;
			push edx;
			mov eax,edx;
			mul tenSt;
			pop edx;
			push eax;
			add edi,eax;
			mov eax, esi;
			mul tenSt;
			mov tenSt, eax;
			pop eax;
			mov ebx, currC;
			cmp maxC, ebx;
			///if it's a top cifr then newEcx=2 else newEcx=1
			///add it to final number
			jne notDoubleIt;
			mov eax,tenSt;
			mul  currC;
			add edi, eax;
			mov eax, esi;
			mul tenSt;
			mov tenSt, eax;
		notDoubleIt:
			pop eax;
			///update tenSt
		loop loopStart3;
		pop eax;
		mov eax,edi;
	}
}

int main() {
	int a;
	cin >> a;
	int ans;
	changeA(a);
	__asm mov ans,eax;
	cout<<ans;
	system("pause");
	return 0;
}
