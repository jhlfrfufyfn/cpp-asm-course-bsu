
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
///_delspec naked
void __declspec(naked) swapTask(int **a, int n, int m) {
	__asm {
		/*
		mov ebx,a;
		mov ebx,[ebx];
		mov edx,0;
		mov eax,[ebx][edx];
		add edx,4;
		mov eax,[ebx][edx];
		add edx, 4;
		mov eax, [ebx][edx];
		mov ebx,a;
		mov ebx,[ebx+4];
		mov eax,[ebx][edx];
		*/
		///цикл по строкам
		///цикл по столбцам
		///поменять в строке i элементы a[i][i] и a[i][n-i-1]
		push ebp;
		mov ebp,esp;
		sub esp,20;
		mov eax, 0;///using for swap
		mov ebx, 0;///adress
		mov ecx, [ebp + 0x0C];///counter of a row
		mov edx, 0;///shift of a column
		mov esi, 4;///shift of a row;
		mov ebx, [ebp + 0x08];
		mov edi, 0;
		mov ebx, [ebp + 0x08];
		mov ebx, [ebx];
	loop1:
		push ecx;
		mov edx, 0;
		mov eax, 0;
		///calculate current second index;
		mov ecx, [ebp + 0x10];
		sub ecx, 1;
		sub ecx, edi;
		///
		mov edx, [ebx][edi * 4];///t=a;
		mov eax, [ebx][ecx * 4];///a=b;
		mov[ebx][edi * 4], eax;///a=b;
		mov[ebx][ecx * 4], edx;///b=t;
		cmp ecx, 0;
		pop ecx;
		jle exitCycle;
		inc edi;
		mov ebx, [ebp + 0x08];
		add ebx, esi;
		mov ebx, [ebx];
		add esi, 4;
		loop loop1;
	exitCycle:
		add esp,20;
		pop ebp;
		ret;
	}
}

void callSwapTask(int **a, int n, int m) {
	__asm {
		push m;
		push n;
		push a;
		call swapTask;
		add esp,0Ch;
	}
}

signed main() {
	cout << "Enter n: ";
	int n;
	cin >> n;
	cout << "Enter m: ";
	int m;
	cin >> m;
	srand(329);
	int **a = new int*[n];
	for (int i = 0;i < n;i++) {
		a[i] = new int[m];
	}
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			a[i][j] = rand() % 10;
		}
	}
	cout << endl;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j<m;j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	callSwapTask(a, n, m);
	cout << endl;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j<m;j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	system("pause");
	return 0;
}
