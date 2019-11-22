#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
using namespace std;
typedef long long ll;

int findI(vector<vector<int> > const& mat) {
	int currP = 0;
	int n=mat.size();
	while (currP < n) {
		int shift=1;
		while (currP + shift < n && mat[currP][currP + shift] == 0) {
			shift++;
		}
		if (currP + shift == n) {
			return currP;
		}
		else
			currP=currP+shift;
	}
	return -1;
}
int main() {
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	int n;
	cin>>n;
	vector<vector<int> > mat(n, vector<int>(n));
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			cin>>mat[i][j];
		}
	}
	cout<<findI(mat);
	return 0;
}
