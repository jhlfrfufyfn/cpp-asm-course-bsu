#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	if (n == 0) {
		cout << 1 << endl;
		system("pause");
		exit(0);
	}
	if (n == 1) {
		cout << 1 << endl;
		system("pause");
		exit(0);
	}
	double element = (n - 1) * n;
	double s = element;
	for (int i = 1;i < n;i++) {
		if (i < n - i) {
			element *= (double)(n - 2 * i)*(double)(n - 2 * i - 1);
			element /= (double)(i + 1)*(double)(i + 1)*(double)(i + 1);
		}
		else {
			element *= (double)(n - i);
			element /= (double)(i + 1)*(double)(i + 1);
		}
		s += element;
	}
	cout << s << endl;
	system("pause");
	return 0;
}
