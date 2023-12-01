/*
    * Created : 2023/08/25
    * Link Cut Tree
    * Description：處理動態樹問題
    * Verification : P3690 【模板】动态树（LCT） https://www.luogu.com.cn/problem/P3690
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define REP1(i, n) FOR(i, 0, n + 1)
#define SZ(x) (int)(x).size()
#define pb push_back
#define pf push_front
#define eb emplace_back
#define f first
#define s second
#define lowbit(x) x&-x
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define int long long 
#define ls ch[x][0]
#define rs ch[x][1]
const int INF = 1e9 + 7;
const int maxn = 1e5 + 5;
//原樹的實鏈：在輔助樹中都是一棵splay中，且splay的inorder是鏈由淺至深的排序
//原樹的虛鏈：子認父親，父不認子
struct LCT{
	int ch[maxn][2], par[maxn], rev[maxn], xr[maxn], val[maxn];
	int get(int x){ return ch[par[x]][1] == x;}
	int isroot(int x){ return ch[par[x]][0] != x && ch[par[x]][1] != x;}
	void push(int x){
		if(rev[x]){
			if(rs) swap(ch[rs][0], ch[rs][1]), rev[rs] ^= 1;
			if(ls) swap(ch[ls][0], ch[ls][1]), rev[ls] ^= 1;
			rev[x] = 0;
		}
	}
	void pull(int x){
		xr[x] = xr[ls] ^ xr[rs] ^ val[x];
	}
	void rotate(int x){
		int y = par[x], z = par[y], k = get(x);
		if(!isroot(y)) ch[z][ch[z][1] == y] = x;
		ch[y][k] = ch[x][!k], par[ch[x][!k]] = y;
		ch[x][!k] = y, par[y] = x;
		par[x] = z;
		pull(y), pull(x);
	}
	void update(int x){
		if(!isroot(x)) update(par[x]);
		push(x);
	}
	void splay(int x){
		update(x); // 把旋轉會經過的點都push_down
		for(int p = par[x]; !isroot(x); rotate(x), p = par[x]){
			if(!isroot(p)) rotate(get(p) == get(x) ? p : x);
		}
	}
	void access(int x){
		for(int p = 0; x != 0; p = x, x = par[x]){
			splay(x); // 把x提到根
			ch[x][1] = p; // 虛邊變實邊
			pull(x);
		}
	}
	void make_root(int x){
		access(x);
		splay(x);
		swap(ls, rs);
		rev[x] ^= 1;
	}
	void link(int x, int y){
		make_root(x);
		splay(x);
		if(find_root(y) == x) return;
		par[x] = y;
	}
	void cut(int x, int y){
		make_root(x);
		access(y);
		splay(x);
		if(par[y] != x || ch[y][0]) return;
		ch[x][1] = par[y] = 0;
	}
	int find_root(int x){
		access(x);
		splay(x);
		push(x);
		while(ls) x = ls, push(x);
		splay(x); // 必要，保證複雜度正確
		return x;
	}
	void split(int x, int y){
		make_root(x);
		access(y);
		splay(y);
	}
	void upd(int x, int y){
		access(x);
		splay(x);
		val[x] = y;
		pull(x);
	}
} st;

signed main(void){
	fastio;
	int n, m;
	cin>>n>>m;
	for(int i = 0; i < n; i++){
		int x;
		cin>>x;
		st.upd(i + 1, x);
	}
	for(int i = 0; i < m; i++){
		int op, x, y;
		cin>>op>>x>>y;
		if(op == 0){
			st.split(x, y);
			cout<<st.xr[y]<<"\n";			
		}
		else if(op == 1){
			st.link(x, y);
		}
		else if(op == 2){
			st.cut(x, y);
		}
		else{
			st.upd(x, y);
		}
	}

}
