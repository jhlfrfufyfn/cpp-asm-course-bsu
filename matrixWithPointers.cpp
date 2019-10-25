#include <iostream>
using namespace std;
int sum1(int *mat, int n, int m) {
	int res = 0;
	for (int i = 0;i<n;i++) {
		for (int j = 0;j<m;j++) {
			res += mat[i*m + j];
			cerr << "mat[" << i*m + j << "]=" << mat[i*m + j] << "\n";
		}
	}
	return res;
}
int sum2(int *mat[], int n, int m) {
	int res = 0;
	for (int i = 0;i<n;i++) {
		for (int j = 0;j<m;j++) {
			res += mat[i][j];
			cerr << "mat[" << i << "][" << j << "]=" << mat[i][j] << "\n";
		}
	}
	return res;
}

int sum3a(int *pa, int n, int m, int l) {
	int res = 0;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			for (int c = 0;c < l;c++) {
				res+=pa[i*n*m+j*m+c];
			}
		}
	}
	return res;
}
const int cn=2,cm=2,cl=2;
int sum3b(int *pa) {
	int res = 0;
	for (int i = 0;i < cn;i++) {
		for (int j = 0;j < cm;j++) {
			for (int c = 0;c < cl;c++) {
				res += pa[i*cn*cm + j*cm + c];
			}
		}
	}
	return res;
}

void input(int &n, int &m) {
	cin >> n >> m;
}
int solve1(int n, int m) {
	int *mat = new int(n*m);
	for (int i = 0;i<n;i++) {
		for (int j = 0;j<m;j++) {
			cin >> mat[i*m + j];
			cerr << "mat[" << i*m + j << "]=" << mat[i*m + j] << "\n";
		}
	}
	return sum1(mat, n, m);
}
int solve2(int n, int m) {
	int **mat = new int*[n];
	for (int i = 0;i<n;i++)
		mat[i] = new int[m];
	for (int i = 0;i<n;i++) {
		for (int j = 0;j<m;j++) {
			cin >> mat[i][j];
			cerr << "mat[" << i << "][" << j << "]=" << mat[i][j] << "\n";
		}
	}
	return sum2(mat, n, m);
}

void MultMatrix(int *pa, int *pb, int *pc, int cn, int cm, int cl) {
	for (int i = 0;i < cn;i++) {
		for (int j = 0;j < cl;j++) {
			pc[i*cn+j] = 0;
		}
	}
	for (int i = 0;i < cn;i++) {
		for (int j = 0;j < cm;j++) {
			for (int c = 0;c < cl;c++) {
				pc[i*cn+c]+=pa[i*cn+j]*pb[j*cm+c];
			}
		}
	}
}
void MultMatrix3(int *pa, int *pb, int *pc, int cn, int cm, int cl, int ck) {
	for (int i = 0;i < cn;i++) {
		for (int j = 0;j < cm;j++) {
			for (int c = 0;c < cl;c++) {
				for (int k = 0;k < ck;k++) {
					pc[i*cn*cm+j*cm+k]=pa[i*cn*cm+j*cm+c]*pb[i*cn*cl+c*cl+k];
				}
			}
		}
	}
}


int main()
{
	//int n, m;
	//input(n, m);
	//cout<<solve1(n, m);
	//cout << "\n";
	//cout<<solve2(n, m);
	//int a[2][3][4];
	//for (int i = 0;i < 2;i++) {
	//	for (int j = 0;j < 3;j++) {
	//		for (int c = 0;c < 4;c++) {
	//			a[i][j][c]=c;
	//		}
	//	}
	//}
	//cout<<sum3a(**a,2,3,4)<<"\n";
	//int b[cn][cm][cl];
	//for (int i = 0;i < cn;i++) {
	//	for (int j = 0;j < cm;j++) {
	//		for (int c = 0;c < cl;c++) {
	//			a[i][j][c]=c;
	//		}
	//	}
	//}
	//cout<<sum3b(**a)<<"\n";
	//int firstMat[2][2];
	//firstMat[0][0] = 2;
	//firstMat[0][1] = 2;
	//firstMat[1][0] = 3;
	//firstMat[1][1] = 3;
	//int secondMat[2][2];
	//secondMat[0][0] = 5;
	//secondMat[0][1] = 1;
	//secondMat[1][0] = 0;
	//secondMat[1][1] = 2;
	//int thirdMat[2][2];
	//MultMatrix(*firstMat,*secondMat,*thirdMat,2,2,2);
	//for (int i = 0;i < 2;i++) {
	//	for (int j = 0;j < 2;j++) {
	//		cout<<thirdMat[i][j]<<" ";
	//	}
	//	cout<<"\n";
	//}
	system("pause");
	///check MultMatrix3
	return 0;
}
