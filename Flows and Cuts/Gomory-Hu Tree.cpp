/*
  Created : 2024.2.4
  Description : Gomory-Hu Tree : 最小割樹
  Time Complexity : O(n^3m)
  Vericication : P4897 【模板】最小割树（Gomory-Hu Tree）https://www.luogu.com.cn/problem/P4897
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define FOR(i, n) for(int i = 0; i < n; i++)
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define lowbit(x) x&-x
#define int long long
const ll INF = 1e18;
const int maxn = 505;
int n, m;
vector<pll> adj[maxn];
struct edge{
	int a, b, w;
	edge(){}
	edge(int _a, int _b, int _w) : a(_a), b(_b), w(_w){}
};
vector<edge> e;

struct Dinic{
	struct edge{
		int to, cap;
		edge(int _to, int _cap) : to(_to), cap(_cap){}
	};
	vector<edge> e;
	vector<vector<int>> adj;
	int n, s, t;
	void add_edge(int from, int to, int cap){
		adj[from].pb(e.size());
		adj[to].pb(e.size() + 1);
		e.pb(edge(to, cap)), e.pb(edge(from, cap));
	}
	vector<int> iter, level;
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		e.clear();
		adj = vector<vector<int>>(n);
		iter.resize(n);
		level.resize(n);
	}
	void bfs(){
		fill(level.begin(), level.end(), -1);
		level[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int pos = q.front(); q.pop();
			for(auto id : adj[pos]){
				auto [to, cap] = e[id];
				if(!cap || level[to] != -1) continue;
				level[to] = level[pos] + 1;
				q.push(to);
			}
		}
	}
	int dfs(int pos, int flow){
		if(pos == t) return flow;
		for(int &i = iter[pos]; i < adj[pos].size(); i++){
			auto [to, cap] = e[adj[pos][i]];
			if(!cap || level[to] != level[pos] + 1) continue;
			int tmp = dfs(to, min(flow, cap));
			if(tmp){
				e[adj[pos][i]].cap -= tmp;
				e[adj[pos][i] ^ 1].cap += tmp;
				return tmp;
			}
		}
		return 0;
	}
	int flow(){
		int ret = 0;
		while(true){
			bfs();
			if(level[t] == -1) break;
			fill(iter.begin(), iter.end(), 0);
			int tmp;
			while((tmp = dfs(s, INF)) > 0){
				ret += tmp;
			}
		}
		return ret;
	}
	vector<int> reached(){
		vector<int> vis(n);
		bfs();
		for(int i = 0; i < n; i++) if(level[i] != -1) vis[i] = 1;
		return vis;
	}
} flow;

void Gomory_Hu_Tree(vector<int> st){
	if(st.size() <= 1) return;
	int s = st[0], t = st[1];
	flow.init(n, s, t);
	for(auto [a, b, w] : e) flow.add_edge(a, b, w);
	int cost = flow.flow();
	vector<int> vis = flow.reached();
	adj[s].eb(t, cost), adj[t].eb(s, cost);
	vector<int> a, b;
	for(auto x : st){
		if(vis[x]) a.pb(x);
		else b.pb(x);
	}
	Gomory_Hu_Tree(a);
	Gomory_Hu_Tree(b);
}
int succ[maxn][9], mn[maxn][9], dep[maxn];

void dfs(int pos, int prev){
	succ[pos][0] = prev;
	for(int i = 1; i < 9; i++){
		succ[pos][i] = succ[succ[pos][i - 1]][i - 1];
		mn[pos][i] = min(mn[pos][i - 1], mn[succ[pos][i - 1]][i - 1]);
	}
	for(auto [x, w] : adj[pos]){
		if(x == prev) continue;
		dep[x] = dep[pos] + 1;
		mn[x][0] = w;
		dfs(x, pos);
	}
}

int lift(int &b, int steps){
	int ret = INF;
	for(int i = 8; i >= 0; i--){
		if(steps & (1 << i)){
			ret = min(ret, mn[b][i]);
			b = succ[b][i];
		}
	}
	return ret;
}
int same_depth_lca(int a, int b){
	int ret = INF;
	for(int i = 8; i >= 0; i--){
		if(succ[a][i] != succ[b][i]){
			ret = min(ret, mn[a][i]);
			ret = min(ret, mn[b][i]);
			a = succ[a][i], b = succ[b][i];
		}
	}
	return min(ret, min(mn[a][0], mn[b][0]));
}

int lca(int a, int b){
	if(a == b) return 0;
	int ret = INF;
	if(dep[a] > dep[b]) swap(a, b);
	ret = lift(b, dep[b] - dep[a]);
	if(a == b) return ret;
	return min(ret, same_depth_lca(a, b));
}
signed main(void){
	fastio;
	cin>>n>>m;
	n++;
	for(int i = 0; i < m; i++){
		int a, b, w;
		cin>>a>>b>>w;
		// a--, b--;
		e.pb(edge(a, b, w));
	}
	vector<int> st(n);
	for(int i = 0; i < n; i++) st[i] = i;
	Gomory_Hu_Tree(st);
	for(int i = 0; i < n; i++) for(int j = 0; j < 9; j++) mn[i][j] = INF;
	dfs(0, 0);
	int q;
	cin>>q;
	for(int i = 0; i < q; i++){
		int a, b;
		cin>>a>>b;
		// a--, b--;
		cout<<lca(a, b)<<"\n";
	}
}
