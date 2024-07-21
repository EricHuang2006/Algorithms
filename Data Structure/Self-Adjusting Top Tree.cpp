/*
  *Created : 2024.7.21
  Description : Self-Adjusting Top Tree
                Support add / delete edge, path queries, subtree queries in O(logn)
  Verification : P3690 【模板】动态树（LCT） https://www.luogu.com.cn/problem/P3690
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2")
#define pb push_back
#define eb emplace_back 
#define f first
#define s second
#define int long long
#define lowbit(x) x&-x
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define ms(x) ch[x][2]
// type == 0 => compress node
// type == 1 => rake node
const int maxn = 1e6 + 5;

int read(){
	int s = 0;
	char a = getchar();
	while(!isdigit(a)) a = getchar();
	while(isdigit(a)){
		s = (s << 1) + (s << 3);
		s += a ^ 48;
		a = getchar();
	}
	return s;
}

int ch[maxn][3], s[maxn][2], tot, val[maxn], n, m, rev[maxn], top, st[maxn], par[maxn];

int new_node(){
	if(top){
		top--;
		return st[top + 1];
	}
	else return ++tot;
}

bool isroot(int x){ return rs(par[x]) != x && ls(par[x]) != x;}
bool dir(int x){ return rs(par[x]) == x;}

void pull(int x, int type){
	if(type){
		s[x][1] = s[ls(x)][1] ^ s[rs(x)][1] ^ s[ms(x)][1];
		return;
	}
	s[x][0] = s[ls(x)][0] ^ val[x] ^ s[rs(x)][0];
	s[x][1] = s[ls(x)][1] ^ s[ms(x)][1] ^ s[rs(x)][1] ^ val[x];
}

void psrev(int x){
	if(!x) return;
	rev[x] ^= 1;
	swap(ls(x), rs(x));
}

void push(int x, int type){
	if(type) return;
	if(rev[x]){
		psrev(ls(x));
		psrev(rs(x));
		rev[x] = 0;
		return;
	}
}

void update(int x, int type){
	if(!isroot(x)) update(par[x], type);
	push(x, type);
}

void setpar(int x, int p, int type){
	if(x) par[x] = p;
	ch[p][type] = x;
}

void rotate(int x, int type){
	int y = par[x], z = par[y], d = dir(x), w = ch[x][d ^ 1];
	if(z) ch[z][ms(z) == y ? 2 : dir(y)] = x;
	ch[x][d ^ 1] = y;
	ch[y][d] = w;
	if(w) par[w] = y;
	par[y] = x;
	par[x] = z;
	pull(y, type);
	pull(x, type);
}

void splay(int x, int type, int gl = 0){
	update(x, type);
	for(int y; y = par[x], !isroot(x) && y != gl; rotate(x, type)){
		if(par[y] != gl && !isroot(y)) rotate(dir(x) == dir(y) ? y : x, type);
	}
}

void clear(int x){
	ls(x) = rs(x) = ms(x) = s[x][0] = s[x][1] = rev[x] = val[x] = 0;
	st[++top] = x;
}

void del(int x){
	setpar(ms(x), par[x], 1);
	if(ls(x)){
		int p = ls(x);
		push(p, 1);
		while(rs(p)) p = rs(p), push(p, 1);
		splay(p, 1, x);
		setpar(rs(x), p, 1);
		setpar(p, par[x], 2);
		pull(p, 1);
		pull(par[x], 0);
	}
	else setpar(rs(x), par[x], 2);
	clear(x);
}

void splice(int x){ // x is a rake node
	// local splay
	splay(x, 1);
	int y = par[x];
	splay(y, 0);
	//splice
	if(rs(y)){
		swap(par[ms(x)], par[rs(y)]);
		swap(ms(x), rs(y));
		pull(x, 1);
	}
	else del(x);
	pull(rs(y), 0);
	pull(y, 0);
}	

void access(int x){ // x is a compress node
	splay(x, 0);	
	int ys = x;
	if(rs(x)){
		int y = new_node();
		setpar(ms(x), y, 0);
		setpar(rs(x), y, 2);
		rs(x) = 0;
		setpar(y, x, 2);
		pull(y, 1);
		pull(x, 0);
	}
	while(par[x]){
		splice(par[x]);
		x = par[x];
	}
	splay(ys, 0);
}

int find_root(int x){
	access(x);
	push(x, 0);
	while(ls(x)) x = ls(x), push(x, 0);
	splay(x, 0);
	return x;
}

void make_root(int x){
	access(x);
	psrev(x);
}
void expose(int x, int y){
	make_root(x);
	access(y);
}

void link(int x, int y){
	if(find_root(x) == find_root(y)) return;
	access(x);
	make_root(y);
	setpar(y, x, 1);
	pull(x, 0);
	pull(y, 0);
}
void cut(int x, int y){
	expose(x, y);
	if(ls(y) != x || rs(x)) return;
	par[x] = ls(y) = 0;
	pull(y, 0);
}

signed main(void){
	fastio;
	n = read(), m = read();
	tot = n;
	for(int i = 1; i <= n; i++) val[i] = read(), pull(i, 0);
	for(int i = 1; i <= m; i++){
		int op = read(), x = read(), y = read();
		if(!op){
			expose(x, y);
			cout<<s[y][0]<<"\n";
		}
		else if(op == 1) link(x, y);
		else if(op == 2) cut(x, y);
		else{
			access(x);
			val[x] = y;
			pull(x, 0);
		}
	}
}
