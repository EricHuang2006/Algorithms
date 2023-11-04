/*
  * Created : 2023/11/4
  * 樹上帶修改 Dp
  * 使用樹鍊剖分 + 廣義矩陣相乘，用線段數維護
  * Verification : 洛谷 P4719 【模板】"动态 DP"&动态树分治
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
#define lowbit(x) x&-x
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
const int N = 1e9 + 7;
const int INF = 1e9;
const int maxn = 1e5 + 5;
vector<int> adj[maxn];
int val[maxn], dep[maxn], par[maxn], siz[maxn], head[maxn], tail[maxn], dfn[maxn], id[maxn];
int F[maxn][2], G[maxn][2];
int cnt = 0, n, m;

struct matrix{
	int a[2][2];
	matrix(){ for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) a[i][j] = (i == j ? 0 : -INF); }
	friend matrix operator * (matrix a, matrix b){
		matrix c;
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				c.a[i][j] = -INF;
				for(int k = 0; k < 2; k++){
					c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
				}
			}
		}
		return c;
	}
} g[maxn], st[maxn * 4];

void dfs(int pos, int prev){
	siz[pos] = 1, F[pos][1] = val[pos];
	if(prev != -1) adj[pos].erase(find(adj[pos].begin(), adj[pos].end(), prev));
	for(auto &x : adj[pos]){
		dep[x] = dep[pos] + 1;
		par[x] = pos;
		dfs(x, pos);
		siz[pos] += siz[x];
		F[pos][0] += max(F[x][0], F[x][1]);
		F[pos][1] += F[x][0];
		if(siz[x] > siz[adj[pos][0]]) swap(x, adj[pos][0]);
	}
}
void decompose(int pos, int h){
	head[pos] = h;
	id[cnt] = pos, dfn[pos] = cnt++;
	tail[h] = pos;
	G[pos][1] = val[pos];
	for(auto x : adj[pos]){
		if(x == adj[pos][0]) decompose(x, h);
		else {
			decompose(x, x);
			G[pos][0] += max(F[x][0], F[x][1]);
			G[pos][1] += F[x][0];
		}
	}
}
void build(int v, int l, int r){
	if(l == r){
		st[v] = g[id[l]];
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m), build(v * 2 + 1, m + 1, r);
	st[v] = st[v * 2] * st[v * 2 + 1];
}
void build(){
	dfs(0, -1);
	decompose(0, 0);
	for(int i = 0; i < n; i++){
		g[i].a[0][0] = g[i].a[0][1] = G[i][0];
		g[i].a[1][0] = G[i][1], g[i].a[1][1] = -INF;
	}
	build(1, 0, n - 1);
}
matrix qry(int l, int r, int v = 1, int L = 0, int R = n - 1){
	if(l > R || r < L) return matrix();
	if(l <= L && r >= R){
		return st[v];
	} 
	int m = (L + R) / 2;
	return qry(l, r, v * 2, L, m) * qry(l, r, v * 2 + 1, m + 1, R); 
}
void upd(int pos, int v = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[v] = g[id[l]];
		return;
	}
	int m = (l + r) / 2;
	if(pos <= m) upd(pos, v * 2, l, m);
	else upd(pos, v * 2 + 1, m + 1, r);
	st[v] = st[v * 2] * st[v * 2 + 1];
}
void change(int pos, int y){
	g[pos].a[1][0] += y - val[pos];
	val[pos] = y;
	while(true){
		matrix bef = qry(dfn[head[pos]], dfn[tail[head[pos]]]);
		upd(dfn[pos]);
		matrix aft = qry(dfn[head[pos]], dfn[tail[head[pos]]]);
		if(head[pos] == 0) break;
		pos = par[head[pos]];
		int chg = max(aft.a[0][0], aft.a[1][0]) - max(bef.a[0][0], bef.a[1][0]);
		g[pos].a[0][0] = g[pos].a[0][1] += chg;
		g[pos].a[1][0] += aft.a[0][0] - bef.a[0][0];
	}
}
int main(void){
	fastio;
	cin>>n>>m;
	for(int i = 0; i < n; i++) cin>>val[i];
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin>>a>>b;
		a--, b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	build();
	for(int i = 0; i < m; i++){
		int x, y;
		cin>>x>>y;
		x--;
		change(x, y);
		matrix ans = qry(dfn[0], dfn[tail[0]]);
		cout<<max(ans.a[0][0], ans.a[1][0])<<"\n";
	}
}
