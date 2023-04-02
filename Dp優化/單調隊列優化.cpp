//Problem source: Codeforces E. The Fair Nut and Rectangles
//Learned from: https://codeforces.com/blog/entry/63823
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct line{
	ll m, k;
	line(){}
	line(ll _m, ll _k) : m(_m), k(_k){}
	ll val(ll x) {
		return m * x + k;
	}
	ll intersectX(line l){
		return (long double) (k - l.k) / (l.m - m);
	}
};

struct info{
	ll x, y, a;
	info(){}
	info(ll _x, ll _y, ll _a): x(_x), y(_y), a(_a){}
	bool operator < (const info& other){
		return x < other.x;
	}
};

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	vector<info> v(n);
	for(int i = 0; i < n; i++){
		ll x, y, a;
		cin>>x>>y>>a;
		v[i] = info(x, y, a);
	}
	sort(v.begin(), v.end());
	ll ans = 0;
	deque<line> dq;
	dq.push_front(line(0, 0));
	for(int i = 0; i < n; i++){
		// query -> insert
		while(dq.size() >= 2 && dq.back().val(v[i].y) < dq[dq.size() - 2].val(v[i].y)) dq.pop_back();
		ll val = dq.back().val(v[i].y) + v[i].x * v[i].y - v[i].a;
		ans = max(ans, val);
		line cur = line(-v[i].x, val);
		while(dq.size() >= 2 && cur.intersectX(dq[0]) >= dq[0].intersectX(dq[1])) dq.pop_front();
		dq.push_front(cur);
	}
	cout<<ans;

}
