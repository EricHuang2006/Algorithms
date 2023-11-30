/*
	* Date : 2023.11.30
	* 點分樹
 	* 題目 : TIOJ 1171 . 我要成為海賊王
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#pragma GCC optimize("Ofast")
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define lowbit(x) x&-x
const int INF = 1e9;
const int maxn = 1e5 + 5, k = 20;
int n, q;
vector<pll> adj[maxn];
ll dist[k][maxn]; // dist[k][i] = distance of i to k-th-layer-par in the centroid tree(k is bounded by logn)
int sz[maxn], del[maxn], par[maxn], cdep[maxn];
ll sum[maxn], cnt[maxn], re[maxn]; // re : 存此子樹中的結點對父親的貢獻

void dfssz(int pos, int prev){
    sz[pos] = 1;
    for(auto [x, w] : adj[pos]){
        if(del[x] || x == prev) continue;
        dfssz(x, pos);
        sz[pos] += sz[x];
    }
}
int get_centroid(int pos, int prev, int siz){
    for(auto [x, w] : adj[pos]){
        if(!del[x] && x != prev && sz[x] > siz / 2) return get_centroid(x, pos, siz);
    }
    return pos;
}
void get_dist(int pos, int prev, int layer){
    for(auto [x, w] : adj[pos]){
        if(del[x] || x == prev) continue;
        dist[layer][x] = dist[layer][pos] + w;
        get_dist(x, pos, layer);
    }
}
void cd(int pos, int layer = 1, int p = 0){
    dfssz(pos, -1);
    int cen = get_centroid(pos, -1, sz[pos]);
    del[cen] = 1;
    dist[layer][cen] = 0;
    cdep[cen] = layer;
    par[cen] = p;
    get_dist(cen, -1, layer);
    for(auto [x, w] : adj[cen]){
        if(!del[x]){
            cd(x, layer + 1, cen);
        }
    }
}
void upd(int p){
    for(int x = p, d = cdep[x]; d; x = par[x], d--){
        sum[x] += dist[d][p];
        re[x] += dist[d - 1][p];
        cnt[x] ++;
    }
}
ll qry(int p){
    ll pre = 0, ans = 0;
    for(int x = p, d = cdep[x]; d; x = par[x], d--){
        ans += sum[x] - re[x] + (cnt[x] - pre) * dist[d][p];
        pre = cnt[x];
    }
    return ans;
}

bitset<maxn> color;
int main(void){
    fastio;
    cin>>n>>q;
    for(int i = 0; i < n - 1; i++){
        int a, b, l;
        cin>>a>>b>>l;
        adj[a].eb(b, l);
        adj[b].eb(a, l);
    }
    cd(0);
    for(int i = 0; i < q; i++){
        int t, x;
        cin>>t>>x;
        if(t == 1){
            if(!color[x]) color[x] = true, upd(x);
        }
        else cout<<qry(x)<<"\n";
    }
}
