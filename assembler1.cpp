#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
using namespace std;
int ans = 0;
typedef long long ll;
int func(int n, int m) {
	__asm {
		push n;///push initial sum
		push n;///push initial lastMember
		mov ecx, n;///initializing counter
		dec ecx;///initializing counter
	loop_start:
		pop eax;///get lastMember {stack=(sum)}
		mul ecx;///eax=index*lastMember(newLastMember)
		mov edx, n;
		sub edx, ecx;
		inc edx;
		mov ebx, edx;
		mov edx, 0;
		div ebx;///eax=eax/ebx;
		pop edx;///edx=sum {stack=()}
		add edx, eax;///sum+=newLastMember 
		push edx;///{stack=(newSum)
		push eax;///push newLastMember {stack=(newLastMember,newSum)}
		cmp edx, m;
		jg exit_cycle;
		cmp ecx,0;
		je exit_cycle;
		loop loop_start;
	exit_cycle:
		pop edx;
		pop edx;
		mov eax, n;
		sub eax, ecx;
		mov ans, eax;
		dec ans;
		mov ans, eax;
	}
}

int main() {
	int n = 0, m = 0;
	cin >> n >> m;
	cout << func(n, m);
	system("pause");
	return 0;
}
