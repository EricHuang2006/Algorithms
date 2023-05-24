//經典題：CF 342E - Xenia and Tree https://codeforces.com/problemset/problem/342/E (also can use sqrt decomposition)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define pb push_back
#define eb emplace_back
const int maxn = 2e5 + 5;
int n, m;
vector<int> adj[maxn];
int sz[maxn], dep[maxn], cd_par[maxn], del[maxn], best[maxn], succ[maxn][19];

void dfssz(int pos, int prev){
	sz[pos] = 1;
	for(auto x : adj[pos]){
		if(x == prev || del[x]) continue;
		dfssz(x, pos);
		sz[pos] += sz[x];
	}
}
int get_centroid(int pos, int prev, int cnt){
	//cnt = the entire subtree size
	for(auto x : adj[pos]){
		if(x != prev && !del[x] && sz[x] > cnt / 2) return get_centroid(x, pos, cnt);
	}
	return pos;
}
void centroid_decomposition(int pos, int anc){
	dfssz(pos, anc);
	int centroid = get_centroid(pos, anc, sz[pos]);
	cd_par[centroid] = anc, del[centroid] = 1;
	for(auto x : adj[centroid]){
		if(!del[x]) centroid_decomposition(x, centroid);
	}
}
void dfsdep(int pos, int prev){
	succ[pos][0] = prev;
	for(int i = 1; i < 19; i++) succ[pos][i] = succ[succ[pos][i - 1]][i - 1];
	for(auto x : adj[pos]){
		if(x == prev) continue;
		dep[x] = dep[pos] + 1;
		dfsdep(x, pos);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin>>a>>b;
		a--, b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	centroid_decomposition(0, -1);
	dfsdep(0, 0); // also compute the ancestor relationship of the original graph
	for(int i = 0; i < n; i++) best[i] = 1e9;
	function<int(int, int)> find_lca = [&](int a, int b){
		for(int i = 18; i >= 0; i--){
			if(succ[a][i] != succ[b][i]){
				a = succ[a][i];
				b = succ[b][i];
			}
		}
		return succ[a][0];
	};
	function<int(int, int)> lift = [&](int b, int steps){
		for(int i = 0; i < 19; i++) if(steps & (1 << i)) b = succ[b][i];
		return b;
	};
	function<int(int, int)> lca = [&](int a, int b){
		if(dep[a] > dep[b]) swap(a, b);
		b = lift(b, dep[b] - dep[a]);
		if(a == b) return a;
		else return find_lca(a, b);
	};
	function<int(int, int)> dist = [&](int a, int b){
		int c = lca(a, b);
		return dep[a] + dep[b] - dep[c] * 2;
	};
	function<void(int)> upd = [&](int pos){
		int cur = pos;
		while(cur != -1){
			best[cur] = min(best[cur], dist(cur, pos));
			cur = cd_par[cur];
		}
	};
	upd(0);
	while(m--){
		int t, a;
		cin>>t>>a;
		a--;
		if(t == 1){
			upd(a);
		}
		else{
			int cur = a, ans = 1e9;
			while(cur != -1){
				ans = min(ans, best[cur] + dist(a, cur));
				cur = cd_par[cur];
			}
			cout<<ans<<"\n";
		}
	}
	

}		
