/*
	* Created: 2023/08/30
	* Description: 用選轉卡尺O(n)求凸包直徑
	* Qualifications: 洛谷 P1452 [USACO03FALL] Beauty Contest G /【模板】旋转卡壳 https://www.luogu.com.cn/problem/P1452
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
#define pb push_back
#define pf push_front
#define eb emplace_back
#define f first
#define s second
#define ckmin(a, b) a = min(a, b)

struct pt{
	ll x, y;
	pt(){}
	pt(ll _x, ll _y) : x(_x), y(_y){}
	bool operator < (const pt& other) const{
		return x < other.x || (x == other.x && y < other.y);
	}
};

pt operator -(pt a, pt b){
	return pt(a.x - b.x, a.y - b.y);
}
ll len(pt a){
	return a.x * a.x + a.y * a.y;
}
istream &operator>>(istream &s, pt &p){
	s >> p.x >> p.y;
	return s;
}
ostream &operator<<(ostream &s, pt &p){
	s << "(" << p.x << ", " << p.y << ")";
	return s;
}
ll cross(pt a, pt b, pt c){
	pt ab = b - a, ac = c - a;
	return ab.x * ac.y - ab.y * ac.x;
}
vector<pt> convex_hull(vector<pt> p){
	int n = p.size();
	sort(p.begin(), p.end());
	vector<pt> hull;
	hull.pb(p[0]);
	int sz = 1;
	for(int i = 1; i < n; i++){
		while(sz > 1 && cross(hull[sz - 2], hull[sz - 1], p[i]) <= 0) hull.pop_back(), sz--; // 不要三點共線
		hull.pb(p[i]);
		sz++;
	}
	int tmp = sz;
	for(int i = n - 2; i >= 0; i--){
		while(sz > tmp && cross(hull[sz - 2], hull[sz - 1], p[i]) <= 0) hull.pop_back(), sz--;
		hull.pb(p[i]);
		sz++;
	}
	// hull.pop_back(); // 留這個點
	return hull;
}
const double eps = 1e-9;
int dcmp(double x){
	if(fabs(x) < eps) return 0;
	return x > eps ? 1 : -1;
}
int diameter(vector<pt> p){
	int n = p.size();
	if(n == 3) return len(p[1] - p[0]); // 退化一條線
	int x = 1; // segment[i, i + 1], 對點為x
	ll ans = 0;
	auto height = [&](int l, int r, int x) -> double{
		return double(abs(cross(p[l], p[r], p[x]))) / len(p[r] - p[l]);
	};
	for(int i = 0; i < n - 1; i++){
		while(dcmp(height(i, i + 1, x) - height(i, i + 1, (x + 1) % n) <= 0)) x = (x + 1) % n; // brute force the first point
		ans = max(max(ans, len(p[x] - p[i])), len(p[x] - p[i + 1]));
	}
	return ans;
}
int main(void){
	fastio;
	int n;
	cin>>n;
	vector<pt> p(n);
	for(int i = 0; i < n; i++){
		cin>>p[i];
	}
	auto h = convex_hull(p);
	cout<<diameter(h)<<"\n";
}
