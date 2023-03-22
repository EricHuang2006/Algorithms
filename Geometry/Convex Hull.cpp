#include<bits/stdc++.h>
using namespace std;

int ConvexHull(Point *p, int n, Point *ch){
	sort(p, p + n);
	int m = 0;
	for(int i = 0; i < n; i++){
		while(m > 1 && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])<= 0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n - 2; i >= 0; i--){
		while(m > k && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) m--;
		ch[m++] = p[i];
	}
	if(n > 1) m--;
	return m;
}

int main(void){
	
}
