//CSES - Path Queries II (still haven't AC) https://cses.fi/problemset/result/6105513/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#pragma GCC optimize("O3,unroll-loops")
#define f first
#define s second
#define pb push_back
const int maxn = 2e5 + 5;
int n, q, t = 0;
int val[maxn], sz[maxn], head[maxn], dep[maxn], st[maxn * 4], par[maxn], loc[maxn];
vector<int> adj[maxn];
int op(int a, int b){
	return max(a, b);
}
void upd(int pos, int val, int v = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[v] = val;
		return;
	}
	int m = (l + r) / 2;
	if(pos <= m) upd(pos, val, v * 2, l, m);
	else upd(pos, val, v * 2 + 1, m + 1, r);
	st[v] = op(st[v * 2], st[v * 2 + 1]);
}
ll qry(int l, int r, int v = 1, int L = 0, int R = n - 1){
	if(L > r || R < l) return 0;
	if(l <= L && r >= R) return st[v];
	int m = (L + R) / 2;
	return op(qry(l, r, v * 2, L, m), qry(l, r, v * 2 + 1, m + 1, R));
}
 
void dfs(int pos, int prev){
	sz[pos] = 1;
	if(prev != -1) adj[pos].erase(find(adj[pos].begin(), adj[pos].end(), prev));
	for(auto &x : adj[pos]){
		par[x] = pos, dep[x] = dep[pos] + 1;
		dfs(x, pos);
		sz[pos] += sz[x];
		if(sz[x] > sz[adj[pos][0]]) swap(x, adj[pos][0]);
	}
}
void decompose(int pos, int h){
	head[pos] = h, loc[pos] = t++;
	upd(loc[pos], val[pos]);
	for(auto x : adj[pos]){
		if(x == adj[pos][0]) decompose(x, h);
		else decompose(x, x);
	}
}
void build(){
	dfs(0, -1);
	decompose(0, 0);
}
int solve(int a, int b){
	int ret = 0;
	while(head[a] != head[b]){
		if(dep[head[a]] > dep[head[b]]) swap(a, b);
		ret = op(ret, qry(loc[head[b]], loc[b]));
		b = par[head[b]];
	}
	if(dep[a] > dep[b]) swap(a, b);
	return op(ret, qry(loc[a], loc[b])); 
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>q;
	for(int i = 0; i < n; i++) cin>>val[i];
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin>>a>>b;
		a--, b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	build();
	while(q--){
		int t, a, b;
		cin>>t>>a>>b;
		a--;
		if(t == 1){
			upd(loc[a], b);
		}
		else{
			b--;
			cout<<solve(a, b)<<" ";
		}
	}
}
