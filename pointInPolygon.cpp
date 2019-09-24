#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Point {
	double x, y;
	Point(double a=0., double b=0.) :x(a), y(b){}
	bool operator==(Point& a) {
		return (a.x == x)&&(a.y == y);
	}
};
struct Edge {
	Point a, b;
	Edge(Point c, Point d) { a = c;b = d; }
};

double leftTurn(Point a, Point b, Point q) {
	return (q.x - a.x)*(b.y - a.y) - (q.y - a.y)*(b.x-a.x);
}

signed main() {
	cout << "Enter x and y of point ";
	Point p;
	cin >> p.x >> p.y;
	cout << "\nEnter first point of polygon ";
	vector<Point> vec;
	double currx, curry;
	cin >> currx >> curry;
	vec.push_back(Point(currx, curry));
	cout << "\nEnter the number of shifts ";
	int n;
	cin >> n;
	cout << "\nEnter the shifts ";
	for (int i = 0;i < n;i++) {
		int shift;
		cin >> shift;
		if (shift == 0) {
			currx++;
			vec.push_back(Point(currx, curry));
		}
		else if (shift == 1) {
			currx++;
			curry++;
			vec.push_back(Point(currx, curry));
		}
		else if (shift == 2) {
			curry++;
			vec.push_back(Point(currx, curry));
		}
		else if (shift == 3) {
			currx--;
			curry++;
			vec.push_back(Point(currx, curry));
		}
		else if (shift == 4) {
			currx--;
			vec.push_back(Point(currx, curry));
		}
		else if (shift == 5) {
			currx--;
			curry--;
			vec.push_back(Point(currx, curry));
		}
		else if (shift == 6) {
			curry--;
			vec.push_back(Point(currx, curry));
		}
		else if (shift == 7) {
			currx++;
			curry--;
			vec.push_back(Point(currx, curry));
		}
	}
	vector<Edge> e;
	for (int i = 1;i < vec.size();i++) {
		e.push_back(Edge(vec[i - 1], vec[i]));
	}
	e.push_back(Edge(vec[n - 1], vec[0]));
	bool INSIDE = 0;
	for (int i = 0;i < e.size();i++) {
		Edge currEdge = e[i];
		if (currEdge.a == p || currEdge.b == p) {
			INSIDE = 1;
			break;
		}
		else if (currEdge.a.y == currEdge.b.y)
			continue;
		else if (p.y == max(currEdge.a.y, currEdge.b.y) && p.x < min(currEdge.a.x, currEdge.b.x))
			INSIDE ^= 1;
		else if (p.y == min(currEdge.a.y, currEdge.b.y))
			continue;
		else if (currEdge.a.y <= p.y <= currEdge.b.y&&leftTurn(currEdge.a, currEdge.b, p))
			INSIDE ^= 1;
	}
	cout << "\n";
	if (INSIDE == 1)
		cout << "INSIDE";
	else
		cout << "OUTSIDE";
	system("pause");
	return 0;
}
















