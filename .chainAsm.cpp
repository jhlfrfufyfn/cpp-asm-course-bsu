#include <iomanip>
#include <iostream>
#include "gtest/gtest.h"
using namespace std;
int FWords(char* s)
{
	_asm
	{
		push ds;
		pop es;
		mov ecx, 0;
		mov ebx, 0;
		cld;
		lea edi, s;
		mov edi, [edi];
		mov al, 0;
	for1:
		scasb;
		je exit1;
		inc ecx;
		jmp for1;
	exit1:
		inc ecx;
			lea edi, s;
			mov edi, [edi];
			mov al, ' ';
			for2 :
			cmp ecx, 1;
			je exitt;
		repe scasb
			dec edi;
		cmp es:[edi],0;
		je exitt;
		inc ecx;
		inc ebx;
		repne scasb;
		dec edi;
		inc ecx;
		jmp for2;
	exitt:
		cld;
	mov eax, ebx;
	}
}

int main() {
	char *ch = " a a ";
	std::cout << FWords(ch);
	system("pause");
	return 0;
}
