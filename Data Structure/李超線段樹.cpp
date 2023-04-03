//Problem: Codeforces F. Escape Through Leaf
//Link: https://codeforces.com/contest/932/problem/F
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define F first
#define S second
const ll INF = 1e18 + 5;
const int maxn = 1e5 + 5;
const int maxc = 1e5;
vector<ll> a, b;
vector<vector<int>> adj;
vector<ll> ans;

struct line{
	ll m, k;
	line(){}
	line(ll _m, ll _k) : m(_m), k(_k){}
	ll val(ll x){ return m * x + k; }
}; 

struct node{
	line ans;
	node *l, *r;
	int siz;
	node(){}
	node(line l) : ans(l), l(nullptr), r(nullptr){ }
};
node sgt[maxn];

int root[maxn], cnt = 0;
struct segtree{
	node *rt;
	int n, siz;
	segtree() : n(maxc * 2), siz(0), rt(nullptr){}
	void insert(node* &k, int l, int r, line cur){
		if(!k){
			k = new node(cur);
			siz++;
			return;
		}
		if(l == r){
			if(k->ans.val(l) > cur.val(l)) k->ans = cur;
			return;
		}
		int m = (l + r) / 2;
		if(k->ans.val(m) > cur.val(m)) swap(k->ans, cur);
		if(cur.m > k->ans.m) insert(k->l, l, m, cur);
		else insert(k->r, m + 1, r, cur);
	}
	void insert(ll m, ll k) { insert(rt, 0, n, line(m, k)); }
	void insert(line l) { insert(rt, 0, n, l);}
	ll qry(node *k, int l, int r, int pos){
		if(!k) return INF;
		if(l == r) return k->ans.val(pos);
		int m = (l + r) / 2;
		return min(k->ans.val(pos), pos <= m ? qry(k->l, l, m, pos) : qry(k->r, m + 1, r, pos));
	}
	ll qry(int pos) { return qry(rt, 0, n, pos); }
	void dfs(vector<line>& tmp, node *nd){
		//get all the useful lines of the segtree (when merging)
		if(!nd) return;
		tmp.pb(nd->ans);
		dfs(tmp, nd->l);
		dfs(tmp, nd->r);
	}
	void dfs(vector<line>& tmp) { dfs(tmp, rt); }
};

void merge(segtree &a, segtree &b){
	if(a.siz < b.siz) swap(a, b);
	vector<line> tmp;
	b.dfs(tmp);
	for(auto x : tmp) a.insert(x);
}

segtree dfs(int pos, int prev){
	segtree cur;
	if(adj[pos].size() == 1 && adj[pos][0] == prev){
		cur.insert(b[pos], -b[pos] * maxc);
		return cur;
	}
	for(auto x : adj[pos]){
		if(x == prev) continue;
		segtree tmp = dfs(x, pos);
		merge(cur, tmp);
	}
	ans[pos] = cur.qry(a[pos] + maxc);
	cur.insert(b[pos], ans[pos] - b[pos] * maxc);
	return cur;
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	a.resize(n), b.resize(n), adj.resize(n), ans.resize(n);
	for(auto &x : a) cin>>x;
	for(auto &x : b) cin>>x;
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin>>u>>v;
		u--, v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(0, -1);
	for(int i = 0; i < n; i++) cout<<ans[i]<<" ";
}
