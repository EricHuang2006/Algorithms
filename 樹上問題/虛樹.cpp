/*
  * 例題：洛谷 P2495 [SDOI2011] 消耗战 https://www.luogu.com.cn/problem/P2495
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
#define pb push_back
#define pf push_front
#define eb emplace_back
#define f first
#define s second
#define all(v) v.begin(), v.end()
#define lowbit(x) x&-x
#define ckmin(a, b) a = min(a, b)
const int maxn = 3e5 + 5;
const ll INF = 1e18;
int id[maxn], dep[maxn], qry[maxn], dfn = 0;
ll mind[maxn];
vector<pll> adj[maxn];
vector<int> nadj[maxn];
int succ[maxn][20], st[maxn], top = 0; // 模擬stack(較方便，可取第二大的元素)

void dfs(int pos, int prev){
	id[pos] = dfn++; // dfs序
	for(int i = 1; i < 20; i++) succ[pos][i] = succ[succ[pos][i - 1]][i - 1];
	for(auto [x, e] : adj[pos]){
		if(x == prev) continue;
		succ[x][0] = pos;
		mind[x] = min(mind[pos], e);
		dep[x] = dep[pos] + 1;
		dfs(x, pos);
	}
}
int main(void){
	fastio;
	int n;
	cin>>n;
	for(int i = 0; i < n; i++) mind[i] = INF;
	for(int i = 0; i < n - 1; i++){
		int a, b, w;
		cin>>a>>b>>w;
		a--, b--;
		adj[a].eb(b, w);
		adj[b].eb(a, w);
	}
	dfs(0, 0);
	int q;
	cin>>q;
	auto same_dep_lca = [&](int a, int b) -> int{
		for(int i = 19; i >= 0; i--){
			if(succ[a][i] != succ[b][i]){
				a = succ[a][i];
				b = succ[b][i];
			}
		}
		return succ[a][0];
	};
	auto lift = [&](int a, int steps) -> int{
		for(int i = 19; i >= 0; i--){
			if(steps & (1 << i)) a = succ[a][i];
		}
		return a;
	};
	auto lca = [&](int a, int b) -> int{
		if(dep[a] > dep[b]) swap(a, b);
		b = lift(b, dep[b] - dep[a]);
		if(a == b) return a;
		return same_dep_lca(a, b);
	};
	while(q--){
		int k;
		cin>>k;
		vector<int> a(k);
		for(int i = 0; i < k; i++) cin>>a[i], a[i] --, qry[a[i]] = true;
		sort(a.begin(), a.end(), [&](int a, int b){ return id[a] < id[b];});
		st[top = 0] = 0;
		nadj[0].clear();
		for(int i = 0; i < k; i++){
			//build virtual tree
			nadj[a[i]].clear();
			if(i == 0){
				st[++top] = a[i];
				continue;
			}
			int l = lca(st[top], a[i]);
			if(l != st[top]){ // 換鏈
				while(top >= 1 && id[l] < id[st[top - 1]]){
					nadj[st[top - 1]].pb(st[top]);
					top--;
				}
				if(l != st[top - 1]) nadj[l].clear(), nadj[l].pb(st[top]), st[top] = l; // 說明第一次入棧 -> 記得clear
				else nadj[l].pb(st[top]), top--;
			}
			st[++top] = a[i];
		}
		while(top){
			nadj[st[top - 1]].pb(st[top]);
			top--;
		}
		// do dfs on new tree
		auto dfs = [&](auto self, int pos) -> ll{
			ll sum = 0, ret = 0;
			for(auto x : nadj[pos]){
				sum += self(self, x);
			}
			if(qry[pos]) ret = mind[pos], qry[pos] = false;
			else ret = min(mind[pos], sum);
			return ret;
		};
		ll ans = dfs(dfs, 0);
		cout<<ans<<"\n";
	}
}
