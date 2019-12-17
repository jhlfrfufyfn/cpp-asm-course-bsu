#include <iomanip>
#include <iostream>
using namespace std;
///32
int FWords(const char* s) {
	__asm {
		mov edi, s;
		mov ax, 0;
		mov es, ax;
		mov ax, 32;
		mov ecx, 100000;
		mov edx, 0; /// counter of the words
		cmp [edi], 32;
		je SKIPIF;
		inc edx;
		scasb;
	SKIPIF:
		for1:
			cld; 
			repne scasb;
			cmp [edi-1], 32;
			dec edi;
			cmp [edi - 1], 32;
			je init1;
		init1: 
			mov bl, 1;///flag for left letter
			jmp further;
		init0:
			mov bl, 0;
			jmp further;
		further:
			cmp [edi + 1], 32;	
			je init21;
		init21:
			mov bh, 1;///flag for right letter
			jmp further1;
		init20:
			mov bh, 0;
			jmp further1;
		further1:
			cmp bh, 32;
			je SKIPIF2;
			cmp[edi + 1], 'a';
			jl SKIPIF2;
			cmp[edi + 1], 'z';
			jg SKIPIF2;
			inc edx;
		SKIPIF2:
		endofloop:
			inc edi;
		loop for1;
	exit1:
		mov eax, edx;
	}
}
const string test1 = "a a a";
const string test2 = "a a a";
const string test3 = "a a a";
const string test4 = "a a a";
int main() {
	const char *s = test1.c_str();
	cout << FWords(s) << "\n";
	system("pause");
	return 0;
}
