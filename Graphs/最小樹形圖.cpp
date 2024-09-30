/*
  Created : 2024.9.30
  Description : minimun spanning tree for a directed graph
  Complexity : O(nm), 要構解的話 O(n^2m) 
  Qualification : P4716 【模板】最小树形图 (https://www.luogu.com.cn/problem/P4716)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define Local
#define sz(x) ll(x.size())
const int maxn = 100 + 5;

struct DSU{
    vector<int> par, siz;
    int n;
    DSU(){}
    DSU(int _n) : n(_n){
        par.resize(n);
        siz.resize(n, 1);
        for(int i = 0; i < n; i++) par[i] = i;
    }
    int root(int x){ return x == par[x] ? x : par[x] = root(par[x]);}
    void unite(int x, int y){
        x = root(x), y = root(y);
        if(x == y) return;
        siz[x] += siz[y];
        par[y] = x;
    }
};

struct edge{
    int a, b, w;
    edge(){}
    edge(int _a, int _b, int _w) : a(_a), b(_b), w(_w){}
    bool operator < (const edge& other) const{
        return w < other.w;
    }
};

vector<edge> adj[maxn];

void ck(int &a, int r){
    if(a == r) a = 0;
    else if(a == 0) a = r;
}

signed main(void){
    fastio;
    int n, m, r;
    cin>>n>>m>>r;
    r--;
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin>>a>>b>>w;
        a--, b--;
        ck(a, r), ck(b, r);
        adj[b].pb(edge(a, b, w));
    }
    DSU dsu(n);
    int ans = 0;
    vector<int> par(n + 1);
    for(int rd = 0; rd < n; rd++){
        vector<int> a;
        for(int i = 0; i < n; i++) if(dsu.root(i) == i) a.pb(i);
        int cn = a.size();
        vector<int> cpar(n + 1), vis(n + 1);
        for(int i = 1; i < cn; i++){
            if(!adj[a[i]].size()) continue;
            sort(adj[a[i]].begin(), adj[a[i]].end());
            cpar[a[i]] = dsu.root(adj[a[i]][0].a);
        }
        int cnt = 1, lp = 0;
        for(int i = 1; i < cn; i++){
            if(vis[a[i]] == 2) continue;
            vector<int> q;
            q.pb(a[i]);
            vis[a[i]] = 1;
            int cur = cpar[a[i]];
            while(cur && !vis[cur]){
                vis[cur] = 1;
                q.pb(cur);
                cur = cpar[cur];
            }
            while(q.size() && q[0] != cur){
                vis[q[0]] = 2;
                q.erase(q.begin());
            }
            if(q.size()){
                lp = 1;
                //縮點
                vector<edge> nw;
                for(auto x : q) dsu.unite(q[0], x);
                for(auto x : q){
                    vis[x] = 2;
                    ans += adj[x][0].w;
                    par[adj[x][0].b] = adj[x][0].a;
                    for(int j = 1; j < adj[x].size(); j++){
                        auto [a, b, w] = adj[x][j];
                        if(dsu.root(a) != dsu.root(b)) nw.pb({a, b, w - adj[x][0].w});
                    }
                }
                adj[q[0]] = nw;
            }
        }
        if(!lp) break;
    }
    for(int i = 1; i < n; i++){
        if(dsu.root(i) == i){
            if(!adj[i].size()){
                cout<<-1<<"\n";
                return 0;
            }
            ans += adj[i][0].w;
            par[adj[i][0].b] = adj[i][0].a;
        }
    }
    cout<<ans<<"\n";
}
