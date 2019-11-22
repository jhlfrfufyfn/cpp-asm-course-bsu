#include <iostream> 
#include <algorithm>
#include <vector>
using namespace std;
int currFi, currFi1, currFi2, currSum, Xi;
///don't work if x==0, erase global vars
int funcP1(int n, int x) {
	__asm {
		///initialize x^n +
		///initialize f0,f1 +
		///initialize sum before 1 including +
		///write a cycle +
		mov currSum, 0;
		mov Xi, 1;
		mov currFi1, 1;
		mov currFi2, 1;
		mov ecx, n;
		mov eax, 1;
	c1:
		mul x;
		loop c1;
		mov Xi, eax;
		add currSum, eax;
		mov eax, Xi;
		mov ecx, x;
		mov edx, 0;
		div ecx;
		mov Xi, eax;
		add currSum, eax;
		mov ecx, currFi1;
		mov currFi, ecx;
		mov ecx, currFi2;
		add currFi, ecx;
		mov ecx, n;
		dec ecx;
	c2:
		///recalc Xi +
		///process currSum +
		///recalc currFi(1)(2) +
		push ecx;
		mov ecx, x;
		mov eax, Xi;
		mov edx, 0;
		div ecx;
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
int funcP2(int n, int x) {
	__asm {
		///initialize x^0 +
		///initialize f0,f1 +
		///initialize sum before 1 including +
		///write a cycle +		
		mov currSum, 0;
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
		mov ecx, currFi1;
		mov currFi, ecx;
		mov ecx, currFi2;
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
int checkCpp1(int n, int x) {
	int p1 = 0;
	int currX = 1;
	vector<int> f(n + 1);
	f[0] = 1;
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
	cout << "p1 = " << funcP1(n, x) << "\np2 = " << funcP2(n, x) << "\n";
	system("pause");
	return 0;
}
