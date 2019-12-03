#include <iostream> 
#include <algorithm>
#include <vector>
using namespace std;
int funcP1(int n, int x, int currFi1=1, int currFi2=1) {
	__asm {
		///initialize x^n +
		///initialize f0,f1 +
		///initialize sum before 1 including +
		///write a cycle +
		///registers used: ecx, eax, edx
		///unused: ebx, edi,esi
		push esi;
		push edi;
		cmp n, 1;
		jne NOT11;
		cmp x, 1;
		jne NOT11;
		jmp MARK8;
	NOT11:
		cmp n,1;
		jne NOT10;
		cmp x,0;
		jne NOT10;
		jmp MARK6;
	NOT10:
		cmp n,0;
		jne NOT0X;
		jmp MARK6;
	NOT0X:
		mov ebx, 0;
		mov edi, 1;
		mov currFi1, 1;
		mov currFi2, 1;
		mov ecx, n;
		mov eax, 1;
	c1:
		mul x;
		loop c1;
		mov edi, eax;
		add ebx, eax;
		mov eax, edi;
		mov ecx, x;
		mov edx, 0;
		cmp ecx, 0;
		je MARK1;
		div ecx;
	MARK1:
		mov edi, eax;
		add ebx, eax;
		mov ecx, currFi1;
		mov esi, ecx;
		mov ecx, currFi2;
		add esi, ecx;
		mov ecx, n;
		dec ecx;
	c2:
		///recalc edi +
		///process ebx +
		///recalc esi(1)(2) +
		push ecx;
		mov ecx, x;
		mov eax, edi;
		mov edx, 0;
		cmp ecx, 0;
		je MARK2;
		div ecx;
	MARK2:
		pop ecx;
		mov edi, eax;
		mul esi;
		add ebx, eax;
		push esi;
		push ecx;
		mov ecx, currFi1;
		mov currFi2, ecx;
		add esi, ecx;
		pop ecx;
		pop currFi1;
		cmp ecx, 0;
		je MARK4;
		loop c2;
	MARK4:
		cmp x, 0;
		je MARK6;
		mov eax, ebx;
		jmp MARK7;
	MARK6:
		mov eax, currFi1;
		jmp MARK7;
	MARK8:
		mov eax,currFi1;
		add eax,currFi2;
		jmp MARK7;
	MARK7:
		pop edi;
		pop esi;
	}
}
int funcP2(int n, int x, int currFi1=1, int currFi2=1) {
	__asm {
		///initialize x^0 +
		///initialize f0,f1 +
		///initialize sum before 1 including +
		///write a cycle +	
		push esi;
		push edi;
		cmp n, 1;
		je MARK6;
		cmp n,0;
		je MARK8;
		mov ebx, 0;
		mov edi, 1;
		mov currFi1, 1;
		mov currFi2, 1;
		mov eax, 1;
		mov edi, eax;
		add ebx, eax;
		mov eax, edi;
		mov ecx, x;
		mul ecx;
		mov edi, eax;
		add ebx, eax;
		mov ecx, currFi1;
		mov esi, ecx;
		mov ecx, currFi2;
		add esi, ecx;
		mov ecx, n;
		dec ecx;
	c2:
		///recalc edi +
		///process ebx +
		///recalc esi(1)(2)+
		push ecx;
		mov ecx, x;
		mov eax, edi;
		mul ecx;
		pop ecx;
		mov edi, eax;
		mul esi;
		add ebx, eax;
		push esi;
		push ecx;
		mov ecx, currFi1;
		mov currFi2, ecx;
		add esi, ecx;
		pop ecx;
		pop currFi1;
		cmp ecx, 0;
		je MARK5;
		loop c2;
	MARK5:
		mov eax, ebx;
		jmp MARK7;
	MARK6:
		mov eax, 1;
		add eax, x;
		jmp MARK7;
	MARK8:
		mov eax,currFi1;
		jmp MARK7;
	MARK7:
		pop edi;
		pop esi;
	}
}
int checkCpp1(int n, int x) {
	int p1 = 0;
	int currX = 1;
	vector<int> f(n + 1);
	f[0] = 1;
	if (n != 0)
		f[1] = 1;
	for (int i = 2;i <= n;i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	for (int i = 0;i <= n;i++) {
		p1 += f[n - i] * currX;
		currX *= x;
	}
	return p1;
}
int checkCpp2(int n, int x) {
	int p1 = 0;
	int currX = 1;
	vector<int> f(n + 1);
	f[0] = 1;
	if (n != 0)
		f[1] = 1;
	for (int i = 2;i <= n;i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	for (int i = 0;i <= n;i++) {
		p1 += f[i] * currX;
		currX *= x;
	}
	return p1;
}
int main()
{
	int n, x;
	cout << "Enter n,x:\n ";
	cin >> n >> x;
	if (checkCpp1(n, x) == funcP1(n, x) && checkCpp2(n, x) == funcP2(n, x))
		cout << "Ok\n";
	cout << "p1Correct = " << checkCpp1(n, x) << "\np2Correct = " << checkCpp2(n, x) << "\n";
	cout << "p1 = " << funcP1(n, x) << "\np2 = " << funcP2(n, x) << "\n";
	system("pause");
	return 0;
}
