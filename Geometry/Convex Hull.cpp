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
int n;
struct pt{
	ll x, y;
	pt(){}
	pt(ll _x, ll _y) : x(_x), y(_y){}
	bool operator < (const pt& other) const{
		return x < other.x || (x == other.x && y < other.y);
	}
};
pt operator - (pt a, pt b){
	return pt(a.x - b.x, a.y - b.y);
}
ll cross(pt a, pt b){
	return a.x * b.y - a.y * b.x;
}
istream &operator >> (istream &s, pt &p){
	s >> p.x >> p.y;
	return s;
}
ostream &operator << (ostream &s, pt &p){
	s << p.x << " " << p.y;
	return s;
}
vector<pt> convex_hull(vector<pt> p, int n){
	vector<pt> ch;
	int m = 0;
	for(int i = 0; i < n; i++){
		while(m > 1 && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) < 0) ch.erase(prev(ch.end())), m--;
		ch.pb(p[i]), m++;
	}
	int k = m;
	for(int i = n - 2; i >= 0; i--){
		while(m > k && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) < 0) ch.erase(prev(ch.end())), m--;
		ch.pb(p[i]), m++;
	}
	ch.erase(prev(ch.end()));
	return ch;
}
int main(void){
	fastio;
	int n;
	cin >> n;
	vector<pt> p(n);
	for(int i = 0; i < n; i++) cin >> p[i];
	sort(p.begin(), p.end());
	auto ch = convex_hull(p, n);
	cout<<ch.size()<<"\n";
	for(auto x : ch) cout<<x<<"\n";
}
