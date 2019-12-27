#include <iomanip>
#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	if (n == 0) {
		cout << 0 << endl;
		system("pause");
		exit(0);
	}
	if (n == 1) {
		cout << 1 << endl;
		system("pause");
		exit(0);
	}
	long double element = (n - 1)*n;
	long double sum = element;
	int m = n / 2;
	for (int i = 2;i <= m;i++) {
		element *= (long double)(n - 2 * i + 1)*(long double)(n - 2 * i + 2);
		element /= long double(i*i*i);
		sum += element;
	}
	if (n % 2 == 1) {
		element /= double(m + 1);
	}
	for (int i = m + 1;i <= n;i++) {
		element *= (long double)(n - i + 1);
		element /= long double(i*i);
		sum += element;
	}
	cout << fixed << setprecision(10) << sum << endl;

	system("pause");
	return 0;
}
