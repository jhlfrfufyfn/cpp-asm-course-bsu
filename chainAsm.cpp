#include <iomanip>
#include <iostream>
using namespace std;
///32
int FWords(char* s) {
	__asm {
		mov edi, s;
		mov ax, 0;
		mov es, ax;
		mov ax, 32;
		mov ecx, 100;
		cld;	
		repne scas s;
		je found;
	found:
		mov eax, edi;
		sub eax, s;
		jmp exit;
		mov eax, -1;
	exit:
	}
}

int main() {
	char *s = "Length 8";
	cout<< FWords(s) <<"\n";
	system("pause");
	return 0;
}
