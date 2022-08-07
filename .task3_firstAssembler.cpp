#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <Windows.h>
#include <algorithm>
#include <iterator>
using namespace std;
///=============================================================================================================

int findK(int n, int m) {
	__asm {
		mov eax, 0;///for calculating
		mov ebx, 0;
		mov ecx, 0;///for cycles and I
		mov edx, 0;///currentC
		mov edi, 0;///current sum
		mov esi, 0;

		mov edx, n;///0th value
		mov edi, edx;
		cmp edx, m;
		jg NOTFOUNDK;
	for1:
		mov ebx, n;
		add ebx, 2;
		cmp ecx, ebx;
		je NOTFOUNDK;

		mov eax, n;
		sub eax, ecx;
		dec eax;

		mul edx;
		mov edx, eax;

		mov eax, ecx;
		add eax, 2;

		xchg eax, edx;
		mov ebx, edx;
		mov edx, 0;
		div ebx;
		mov edx, eax;

		add edi, edx;

		cmp edi, m;
		jg FOUNDK;

		inc ecx;
		inc ecx;
		loop for1;

	FOUNDK:
		mov eax, ecx - 1;
		jmp ENDFUNC;

	NOTFOUNDK:
		mov eax, -1;
		jmp ENDFUNC;

	ENDFUNC:
		nop;
	}
}


int C(int n, int k) {
	if (k < 0)
		return 0;
	double res = 1;
	for (int i = 1; i <= k; ++i)
		res = res * (n - k + i) / i;
	return (int)(res + 0.01);
}

int findKCpp(int n, int m) {
	int currC = C(n, n - 1);
	int sum = currC;
	for (int i = 1;i <= n + 1;i++) {
		if (sum > m)
			return i - 2;
		currC = C(n, n - i - 1);
		sum += currC;
	}
	if (sum > m)
		return n;
	return -1;
}

int main() {
	cout << "Enter n, m " << endl;
	int n, m;
	for (n = 5;n <= 5;n++) {
		for (m = 10;m <= 100;m++) {
			cerr << n << " " << m << endl << "c++ : " << findKCpp(n, m) << endl << "asm : " << findK(n, m) << endl << endl;
		}
	}
	system("pause");
	return 0;
}










