#include <iostream> 
#include <algorithm>
#include <vector>
using namespace std;
struct Point
{
	int x, y;
	bool operator==(Point s) {
		return s.x==x&&s.y==y;
	}
};
inline int isLeft(Point P0, Point P1, Point P2)
{
	return ((P1.x - P0.x) * (P2.y - P0.y)
		- (P2.x - P0.x) * (P1.y - P0.y));
}

int cn_PnPoly(Point P, Point* V, int n)
{
	int cn = 0;  
	for (int i = 0; i<n; i++) { 
		if (((V[i].y <= P.y) && (V[i + 1].y > P.y)) || ((V[i].y > P.y) && (V[i + 1].y <= P.y))) {
			float vt = (float)(P.y - V[i].y) / (V[i + 1].y - V[i].y);
			if (P.x <  V[i].x + vt * (V[i + 1].x - V[i].x)) 
				++cn;
		}
	}
	return (cn & 1);

}

bool isInside(Point P, Point* V, int n)
{
	int  wn = 0;
	for (int i = 0; i<n; i++) {
		if(V[i]==P)
			return 1;
		if (V[i].y <= P.y) {
			if (V[i + 1].y  > P.y)
				if (isLeft(V[i], V[i + 1], P) > 0)
					++wn;
		}
		else {
			if (V[i + 1].y <= P.y)
				if (isLeft(V[i], V[i + 1], P) < 0)
					--wn;
		}
	}
	return !(wn == 0);
}
int main() {
	int n;
	cin >> n;	
	Point pol[1000];
	for (int i = 0;i < n;i++) {
		cin >> pol[i].x >> pol[i].y;
	}
	pol[n]=pol[0];
	Point p;
	cin >> p.x >> p.y;
	if (cn_PnPoly(p, pol, n)||isInside(p,pol,n))
		cout << "YES";
	else
		cout << "NO";
	system("pause");
	return 0;
}

/*
13
2 1
2 2
2 3
2 4
3 3
4 3
5 4
5 3
5 2
4 2
4 1
4 0
3 0
*/
