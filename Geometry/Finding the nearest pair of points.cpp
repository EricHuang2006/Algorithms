/*
	* Date: 2023/08/12
	* Finding d^2, where d is the distance of the nearest pair of points
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#pragma GCC optimize("Ofast")
#define pb push_back
#define eb emplace_back
const ll INF = 8e18;
const int N = 998244353;
const int maxn = 2e5 + 5;

struct pt{
	ll x, y;
	pt(){}
	pt(ll _x, ll _y) : x(_x), y(_y) {}
};
pt a[maxn], tmp[maxn];
struct cmp_x{
	bool operator()(const pt& a, const pt& b) const{
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	}
};
struct cmp_y{
	bool operator()(const pt& a, const pt& b) const{
		return a.y < b.y;
	}
};
pt operator - (pt a, pt b){
	return pt(a.x - b.x, a.y - b.y);
}
ll len(pt a){
	return sqrt(a.x * a.x + a.y * a.y);
}
ll len2(pt a){
	return a.x * a.x + a.y * a.y;
}
ostream &operator << (ostream &s, pt &p){
	s << p.x << " " << p.y;
	return s;
}
ll mn_dist = INF;
void upd_ans(pt a, pt b){
	ll dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	mn_dist = min(mn_dist, dist);
}

void solve(int l, int r){
	if(r - l <= 3){
		for(int i = l; i < r; i++){
			for(int j = i + 1; j < r; j++){
				upd_ans(a[i], a[j]);
			}
		}
		sort(a + l, a + r, cmp_y());
		return;
	}
	int m = (l + r) / 2;
	int midx = a[m].x;
	solve(l, m);
	solve(m, r);

	merge(a + l, a + m, a + m, a + r, tmp, cmp_y());
	copy(tmp, tmp + r - l, a + l);
 
	int sz = 0;
	for(int i = l; i < r; i++){
		if((a[i].x - midx) * (a[i].x - midx) < mn_dist){
			int cur = 0;
			for(int j = sz - 1; j >= 0 && (a[i].y - tmp[j].y) * (a[i].y - tmp[j].y) < mn_dist; j--){
				upd_ans(a[i], tmp[j]);
			}
			tmp[sz++] = a[i];
		}
	}
}
void solve(){
	int n;
	cin >> n;
	mn_dist = INF;
	for(int i = 0; i < n; i++) {
		ll x, y;
		cin>>x>>y;
		a[i] = pt(x, y);
	}
	sort(a, a + n, cmp_x());
	solve(0, n);
	cout<<mn_dist<<"\n";
	// cout<<fixed<<setprecision(6)<<sqrt(mn_dist)<<"\n";
}

int main(void){
	fastio;	
	int t = 1;
	while(t--){
		solve();
	}
}
