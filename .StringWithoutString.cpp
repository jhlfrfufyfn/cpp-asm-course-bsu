#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;


signed main() {
	char *s1=new char[100000];
	cout << "Enter first string: ";
	cin>>s1;
	char *s2=new char[100000];
	cout << "Enter second string: ";
	cin >> s2;
	vector<char> used1(256);
	vector<char> used2(256);
	int sz=strlen(s1);
	for (int i = 0;i<sz;i++) {
		used1[(int)s1[i]] = 1;
	}
	 sz=strlen(s2);
	for (int j = 0;j<sz;j++) {
		used2[(int)s2[j]] = 1;
	}
	for (int i = 0;i<256;i++) {
		if (used1[i] == 1 && used2[i] == 1)
			cout << (char)i << " ";
	}
	system("pause");
	return 0;
}
