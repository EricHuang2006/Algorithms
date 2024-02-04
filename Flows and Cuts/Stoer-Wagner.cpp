/*
    Created : 2023.2.4
    Description : Stoer-Wagner Algorithm 
                  finding the minimum cut of an undirected graph ( without source and sink )
    Time Complexity : O(V^3) / O(V^2logV) with fib heap
    Verification : P5632 【模板】Stoer-Wagner https://www.luogu.com.cn/problem/P5632
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
const int maxn = 605;
int edge[maxn][maxn], par[maxn], siz[maxn];
int dist[maxn], vis[maxn], done[maxn];
int n, m;
int root(int x){ return x == par[x] ? x : par[x] = root(par[x]);}

int contract(int &s, int &t){
	memset(dist, 0, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	int mincut = INF, id, maxc;
	for(int i = 0; i < n; i++){
		id = maxc = -1;
		for(int j = 0; j < n; j++){
			if(!done[j] && !vis[j] && dist[j] > maxc){
				id = j;
				maxc = dist[j];
			}
		}
		if(id == -1) return mincut;
		s = t, t = id;
		mincut = maxc;
		vis[id] = true;
		for(int j = 0; j < n; j++){
			if(!done[j] && !vis[j]) dist[j] += edge[id][j];
		}
	}
	return mincut;
}

int Stoer_Wagner(){
	int mincut = INF, s, t, tmp;
	for(int i = 1; i < n; i++){
		tmp = contract(s, t);
		done[t] = true;
		mincut = min(mincut, tmp);
		if(!mincut) return 0;
		for(int j = 0; j < n; j++){
			if(!done[j]) edge[s][j] = (edge[j][s] += edge[j][t]);
		}
	}
	return mincut;
}

signed main(void){
	fastio;
	cin>>n>>m;
	for(int i = 0; i < n; i++) par[i] = i, siz[i] = 1;
	for(int i = 0; i < m; i++){
		int a, b, w;
		cin>>a>>b>>w;
		a--, b--;
		int fa = root(a), fb = root(b);
		if(fa != fb){
			par[fa] = fb, siz[fb] += siz[fa];
		}
		edge[a][b] += w;
		edge[b][a] += w;
	}
	if(siz[root(0)] != n){
		cout<<0<<"\n";
		return 0;
	}
	cout<<Stoer_Wagner()<<"\n";
	
}
