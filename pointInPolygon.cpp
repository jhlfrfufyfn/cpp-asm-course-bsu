#include <iostream> 
#include <algorithm>
#include <vector>
using namespace std;
const int INF = 1000000;
struct Point
{
	int x,y;
};
bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return 1;
	return 0;
}
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r)
{
	int val = (q.y-p.y)*(r.x-q.x)-(q.x-p.x)*(r.y-q.y);
	if (val == 0) 
		return 0;
	if(val > 0)
		return 1;
	if(val < 0)
		return 2;
}
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);
	if (o1 != o2 && o3 != o4)
		return 0;
	if (o1 == 0 && onSegment(p1, p2, q1)) 
		return 1;
	if (o2 == 0 && onSegment(p1, q2, q1)) 
		return 1;
	if (o3 == 0 && onSegment(p2, p1, q2)) 
		return 1;
	if (o4 == 0 && onSegment(p2, q1, q2)) 
		return 1;
	return 0;
}

bool isInside(Point polygon[], int n, Point p)
{
	Point extreme = { INF, p.y };
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return onSegment(polygon[i], p, polygon[next]);
			count++;
		}
		i = next;
	} while (i != 0);
	return count&1;  
}

int main()
{
	int n;
	cin>>n;
	Point pol[1000];
	for (int i = 0;i < n;i++) {
		cin>>pol[i].x>>pol[i].y;
	}
	Point p;
	cin>>p.x>>p.y;
	if(isInside(pol,n,p))
		cout<<"YES";
	else
		cout<<"NO";
	system("pause");
	return 0;
}
