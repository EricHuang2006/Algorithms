/*
  Created : 2024.9.12
  Description : Dominator tree
  Find the dominating relationship of vertices in a directed graph in O(nlogn)
  Verification : P5180 【模板】支配树 https://www.luogu.com.cn/problem/P5180
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
int in[maxn], id[maxn], par[maxn], dfn = 0;
int mn[maxn], idom[maxn], sdom[maxn], ans[maxn];
int fa[maxn]; // dsu
int n, m;

struct edge{
	int to, id;
	edge(){}
	edge(int _to, int _id) : to(_to), id(_id){}
};
vector<edge> adj[3][maxn];

void dfs(int pos){
	in[pos] = ++dfn;
	id[dfn] = pos;
	for(auto [x, id] : adj[0][pos]){
		if(in[x]) continue;
		dfs(x);
		par[x] = pos;
	}
}

int find(int x){
	if(fa[x] == x) return x;
	int tmp = fa[x];
	fa[x] = find(fa[x]);
	if(in[sdom[mn[tmp]]] < in[sdom[mn[x]]]){
		mn[x] = mn[tmp];
	}
	return fa[x];
}

void tar(int st){
	dfs(st);
	for(int i = 0; i < n; i++) mn[i] = sdom[i] = fa[i] = i;
	for(int i = dfn; i >= 2; i--){
		int pos = id[i], res = INF; // res : in(x) of sdom
		for(auto [x, id] : adj[1][pos]){
			if(!in[x]) continue;
			find(x);
			if(in[pos] > in[x]) res = min(res, in[x]);
			else res = min(res, in[sdom[mn[x]]]);
		}
		sdom[pos] = id[res];
		fa[pos] = par[pos];
		adj[2][sdom[pos]].eb(pos, 0);
		pos = par[pos]; // enumerate sdom links of par[pos]
		for(auto [x, id] : adj[2][pos]){
			find(x);
			if(sdom[mn[x]] == pos){
				idom[x] = pos;
			}
			else{
				idom[x] = mn[x];
			}
		}
		adj[2][pos].clear();
	}
	for(int i = 2; i <= dfn; i++){
		int x = id[i];
		if(idom[x] != sdom[x]) idom[x] = idom[idom[x]];
	}
}

signed main(void){
	fastio;
	cin>>n>>m;
	for(int i = 0; i < m; i++){
		int a, b;
		cin>>a>>b;
		a--, b--;
		adj[0][a].eb(b, i);
		adj[1][b].eb(a, i);
	}
	tar(0);
	for(int i = dfn; i >= 2; i--){
		ans[id[i]]++;
		ans[idom[id[i]]] += ans[id[i]];
	}
	ans[0]++;
	for(int i = 0; i < n; i++) cout<<ans[i]<<" ";
	cout<<"\n";
}
