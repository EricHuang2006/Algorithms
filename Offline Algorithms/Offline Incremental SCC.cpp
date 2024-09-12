/*
  Created : 2024.9.12
  Description : handle edge addition and SCC related qureies offline in O(nlogn)
  Verification : CF 1989F - Simultaneous Coloring (https://codeforces.com/contest/1989/problem/F)
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define int long long
#define lowbit(x) x&-x
#define ld long double
const int maxn = 4e5 + 5;
const int INF = 1e9;
const int N = 1e9 + 7;
vector<int> adj[maxn];
int ans[maxn];
int in[maxn], low[maxn], scc[maxn], cnt = 0, dfn = 0;
int par[maxn], siz[maxn];
int cur = 0;
stack<int> st;
int cal(int x){
	return x > 1 ? x * x : 0;
}
vector<int> tra;

struct edge{
	int u, v, id;
	edge(){}
	edge(int _u, int _v, int _id) : u(_u), v(_v), id(_id){}
};


void dfs(int pos){
	in[pos] = low[pos] = ++dfn;
	st.push(pos);
	for(auto x : adj[pos]){
		if(in[x]){
			if(!scc[x]) low[pos] = min(low[pos], in[x]);
		}
		else{
			dfs(x);
			low[pos] = min(low[pos], low[x]);
		}
	}
	if(low[pos] == in[pos]){
		int c = ++cnt;
		while(st.top() != pos){
			scc[st.top()] = c;
			tra.pb(st.top());
			st.pop();
		}
		scc[pos] = c;
		tra.pb(pos);
		st.pop();
	}
}

int root(int x){ return x == par[x] ? x : par[x] = root(par[x]);}
void unite(int x, int y){
	x = root(x), y = root(y);
	if(x == y) return;
	if(siz[x] > siz[y]) swap(x, y);
	cur -= cal(siz[x]) + cal(siz[y]);
	siz[y] += siz[x], par[x] = y;
	cur += cal(siz[y]);
}

void sol(int l, int r, vector<edge> e){
	int m = (l + r) / 2;
	vector<int> v;
	for(auto &[a, b, id] : e){
		a = root(a), b = root(b), v.pb(a), v.pb(b);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for(auto x : v) in[x] = scc[x] = 0, adj[x].clear();
	for(auto [a, b, id] : e) if(id <= m){
		adj[a].pb(b);
	}
	tra.clear();
	dfn = cnt = 0;
	for(auto x : v) if(!in[x]) dfs(x);
	if(l == r){
		for(int i = 0; i < ll(tra.size()) - 1; i++){
			if(scc[tra[i]] == scc[tra[i + 1]]){
				unite(tra[i], tra[i + 1]);
			}
		}
		ans[l] = cur;
		return;
	}
	vector<edge> L, R;
	for(auto [a, b, id] : e){
		if(scc[a] == scc[b] && id <= m) L.pb(edge(a, b, id));
		else R.pb(edge(a, b, id));
	}
	sol(l, m, L), sol(m + 1, r, R);

}

signed main(void){
	fastio;
	int n, m, q;
	cin>>n>>m>>q;
	for(int i = 0; i < n + m; i++) par[i] = i, siz[i] = 1;
	vector<edge> e;
	for(int i = 0; i < q; i++){
		int a, b;
		char c;
		cin>>a>>b>>c;
		a--, b--;
		if(c == 'R'){
			e.pb(edge(n + b, a, i));
		}
		else e.pb(edge(a, n + b, i));
	}
	sol(0, q - 1, e);
	for(int i = 0; i < q; i++) cout<<ans[i]<<"\n";
}
