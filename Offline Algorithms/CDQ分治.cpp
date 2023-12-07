// find the number of indices j for every i such that x_j > x_i, y_j > y_i, z_j > z_i
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define lowbit(x) x&-x
#define int long long
const int INF = 1e9 + 7;
const int maxn = 1e5 + 5;
const int N = 1e9 + 7;

struct pt{
	int x, y, z, id;
	pt(){}
	pt(int _x, int _y, int _z) : x(_x), y(_y), z(_z){}
} a[maxn];

inline bool cmpx(pt a, pt b){
	return a.x < b.x || (a.x == b.x && a.y > b.y);
}
int BIT[maxn];
void upd(int pos, int val){
	while(pos < maxn){
		BIT[pos] += val;
		pos += lowbit(pos);
	}
}
int qry(int pos){
	int ret = 0;
	while(pos > 0){
		ret += BIT[pos];
		pos -= lowbit(pos);
	}
	return ret;
}
int ans[maxn];

void cdq(int l, int r){
	if(l >= r) return;
	int m = (l + r) / 2;
	cdq(l, m);
	cdq(m + 1, r);
	int id = l;
	vector<pt> cpy;
	for(int i = m + 1; i <= r; i++){
		while(id <= m && a[id].y < a[i].y) upd(a[id].z, 1), cpy.pb(a[id]), id++;
		ans[a[i].id] += qry(a[i].z - 1);
		cpy.pb(a[i]); 
	}
	for(int i = id; i <= m; i++) cpy.pb(a[i]);
	for(int i = l; i < id; i++) upd(a[i].z, -1);
	for(int i = l; i <= r; i++) a[i] = cpy[i - l];
}
signed main(void){
	fastio;
	int n;
	cin>>n;
	for(int i = 0; i < n; i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
		a[i].x = maxn - a[i].x, a[i].y = maxn - a[i].y, a[i].z = maxn - a[i].z;
		a[i].id = i;
	}
	sort(a, a + n, cmpx);
	cdq(0, n - 1);
	for(int i = 0; i < n; i++) cout<<ans[i]<<"\n";
}
