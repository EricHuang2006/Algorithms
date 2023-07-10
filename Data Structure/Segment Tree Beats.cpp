/*
  * Date: 2023/07/10
  * Segment Tree Beats
  * Process the following operations in O((n + q)log^2n)
      1. range chmin
      2. range chmax
      3. range additions
      4. range sum queries
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
#define eb emplace_back
const int maxn = 2e5 + 5;
const ll INF = 1e18;
struct node{
	ll sum;
	ll mx1, mx2, mxcnt;
	ll mn1, mn2, mncnt;
	ll lazy;
	node(){}
};
node st[maxn * 4];
int n, m;
vector<ll> a;
void merge(int v){

	//sum
	st[v].sum = st[v * 2].sum + st[v * 2 + 1].sum;

	//max
	if(st[v * 2].mx1 == st[v * 2 + 1].mx1){
		st[v].mx1 = st[v * 2].mx1;
		st[v].mxcnt = st[v * 2].mxcnt + st[v * 2 + 1].mxcnt;
		st[v].mx2 = max(st[v * 2].mx2, st[v * 2 + 1].mx2);
	}
	else{
		if(st[v * 2].mx1 < st[v * 2 + 1].mx1){
			st[v].mx1 = st[v * 2 + 1].mx1;
			st[v].mxcnt = st[v * 2 + 1].mxcnt;
			st[v].mx2 = max(st[v * 2].mx1, st[v * 2 + 1].mx2);
		}
		else{
			st[v].mx1 = st[v * 2].mx1;
			st[v].mxcnt = st[v * 2].mxcnt;
			st[v].mx2 = max(st[v * 2].mx2, st[v * 2 + 1].mx1);
		}
	}

	//min
	if(st[v * 2].mn1 == st[v * 2 + 1].mn1){
		st[v].mn1 = st[v * 2].mn1;
		st[v].mncnt = st[v * 2].mncnt + st[v * 2 + 1].mncnt;
		st[v].mn2 = min(st[v * 2].mn2, st[v * 2 + 1].mn2);
	}
	else{
		if(st[v * 2].mn1 > st[v * 2 + 1].mn1){
			st[v].mn1 = st[v * 2 + 1].mn1;
			st[v].mncnt = st[v * 2 + 1].mncnt;
			st[v].mn2 = min(st[v * 2].mn1, st[v * 2 + 1].mn2);
		}
		else{
			st[v].mn1 = st[v * 2].mn1;
			st[v].mncnt = st[v * 2].mncnt;
			st[v].mn2 = min(st[v * 2].mn2, st[v * 2 + 1].mn1);
		}
	}
}

void push_add(int v, int l, int r, ll val){
	if(val == 0) return; 
	st[v].sum += val * (r - l + 1);
	st[v].mx1 += val;
	st[v].mn1 += val;
	if(st[v].mx2 != -INF) st[v].mx2 += val;
	if(st[v].mn2 != INF) st[v].mn2 += val;
	st[v].lazy += val;
}

//corresponds to a chmin update
void push_max(int v, ll val, bool l){
	if(st[v].mx1 <= val) return;
	st[v].sum -= st[v].mxcnt * (st[v].mx1 - val);
	st[v].mx1 = val;
	if(l){
		st[v].mn1 = val;
	}
	else{
		if(val <= st[v].mn1) st[v].mn1 = val;
		else if(val < st[v].mn2) st[v].mn2 = val;
	}
}

//corresponds to a chmax update
void push_min(int v, ll val, bool l){
	if(st[v].mn1 >= val) return;
	st[v].sum += st[v].mncnt * (val - st[v].mn1);
	st[v].mn1 = val;
	if(l){
		st[v].mx1 = val;
	}
	else{
		if(val >= st[v].mx1) st[v].mx1 = val;
		else if(val > st[v].mx2) st[v].mx2 = val;
	}
}	
void push_down(int v, int l, int r){
	if(l == r) return;

	//sum
	int m = (l + r) / 2;
	push_add(v * 2, l, m, st[v].lazy);
	push_add(v * 2 + 1, m + 1, r, st[v].lazy);
	st[v].lazy = 0;

	// max
	push_max(v * 2, st[v].mx1, l == m);
	push_max(v * 2 + 1, st[v].mx1, m + 1 == r);

	// min
	push_min(v * 2, st[v].mn1, l == m);
	push_min(v * 2 + 1, st[v].mn1, m + 1 == r);
}		
void build(int v = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[v].sum = st[v].mx1 = st[v].mn1 = a[l];
		st[v].mxcnt = st[v].mncnt = 1;
		st[v].mx2 = -INF;
		st[v].mn2 = INF;
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m);
	build(v * 2 + 1, m + 1, r);
	merge(v);
}
void upd_add(int l, int r, ll val, int v = 1, int L = 0, int R = n - 1){
	if(l > R || r < L) return;
	if(l <= L && r >= R){
		push_add(v, L, R, val);
		return;
	}
	push_down(v, L, R);
	int m = (L + R) / 2;
	upd_add(l, r, val, v * 2, L, m);
	upd_add(l, r, val, v * 2 + 1, m + 1, R);
	merge(v);
}
void upd_min(int l, int r, ll val, int v = 1, int L = 0, int R = n - 1){
	if(l > R || r < L || st[v].mx1 <= val) return;
	if(l <= L && r >= R && st[v].mx2 < val){
		push_max(v, val, L == R);
		return;
	}
	push_down(v, L, R);
	int m = (L + R) / 2;
	upd_min(l, r, val, v * 2, L, m);
	upd_min(l, r, val, v * 2 + 1, m + 1, R);
	merge(v);
}
void upd_max(int l, int r, ll val, int v = 1, int L = 0, int R = n - 1){
	if(l > R || r < L || st[v].mn1 >= val) return;
	if(l <= L && r >= R && st[v].mn2 > val){
		push_min(v, val, L == R);
		return;
	}
	push_down(v, L, R);
	int m = (L + R) / 2;
	upd_max(l, r, val, v * 2, L, m);
	upd_max(l, r, val, v * 2 + 1, m + 1, R);
	merge(v);
}
ll qry(int l, int r, int v = 1, int L = 0, int R = n - 1){
	if(l > R || r < L) return 0;
	if(l <= L && r >= R){
		// cout<<"sum : "<<L<<" "<<R<<" "<<st[v].sum<<"\n";
		return st[v].sum;
	}
	push_down(v, L, R);
	int m = (L + R) / 2;
	return qry(l, r, v * 2, L, m) + qry(l, r, v * 2 + 1, m + 1, R);
}
int main(void){
	// fastio;
	cin>>n>>m;
	a.resize(n);
	for(int i = 0; i < n; i++){
		cin>>a[i];
	}
	build();
	while(m--){
		ll t, l, r;
		cin>>t>>l>>r;
		r --;
		if(t == 0){
			ll b;
			cin>>b;
			upd_min(l, r, b);
		}
		else if(t == 1){
			ll b;
			cin>>b;
			upd_max(l, r, b);
		}
		else if(t == 2){
			ll b;
			cin>>b;
			upd_add(l, r, b);
		}
		else{
			cout<<qry(l, r)<<"\n";
		}
	}
}
