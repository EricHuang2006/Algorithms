#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

struct Dinic{
	struct edge{
		ll to, cap;
		edge(){}
		edge(int _to, ll _cap) : to(_to), cap(_cap){}
	};
	vector<edge> e;
	vector<vector<int>> adj;
	vector<int> iter, level;
	int n, s, t;
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		adj = vector<vector<int>>(n);
		iter = vector<int>(n);
		level = vector<int>(n);
		e.clear();
	}
	void add_edge(int from, int to, ll cap){
		adj[from].pb(e.size()), adj[to].pb(e.size() + 1);
		e.pb(edge(to, cap)), e.pb(edge(from, 0));
	}
	void bfs(){
		fill(level.begin(), level.end(), -1);
		level[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int cur = q.front(); q.pop();
			for(auto id : adj[cur]){
				auto [to, cap] = e[id];
				if(level[to] == -1 && cap){
					level[to] = level[cur] + 1;
					q.push(to);
				}
			}
		}
	}
	ll dfs(int pos, ll flow){
		if(pos == t) return flow;
		for(int &i = iter[pos]; i < adj[pos].size(); i++){
			auto [to, cap] = e[adj[pos][i]];
			if(level[to] == level[pos] + 1 && cap){
				ll tmp = dfs(to, min(flow, cap));
				if(tmp){
					e[adj[pos][i]].cap -= tmp;
					e[adj[pos][i] ^ 1].cap += tmp;
					return tmp; 
				}
			}
		}
		return 0;
	}
	ll flow(){
		ll ret = 0;
		while(true){
			bfs();
			if(level[t] == -1) break;
			fill(iter.begin(), iter.end(), 0);
			ll tmp;
			while((tmp = dfs(s, INF)) > 0){
				ret += tmp;
			}
		}
		return ret;
	}
	vector<pll> cut(){
		vector<pll> ret;
		fill(level.begin(), level.end(), -1);
		level[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int cur = q.front(); q.pop();
			for(auto id : adj[cur]){
				auto [to, cap] = e[id];
				if(cap == 0 && level[to] == -1) ret.pb({e[id ^ 1].to, to});
				else if(level[to] == -1){
					level[to] = level[cur] + 1;
					q.push(to);
				}
			}
		}
		return ret;
	}
} flow;


int main(){
    int n, m;
    cin>>n>>m;
    flow.init(n, 0, n - 1);
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin>>a>>b>>w;
        a--, b--;
        flow.add_edge(a, b, w);
    }
    cout<<flow.flow();
}
