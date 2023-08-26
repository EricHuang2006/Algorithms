/*
    * Created : 2023/08/25
    * Link Cut Tree
    * Description：處理動態樹問題
    * Verification : 洛谷 P1501 [国家集训队] Tree II https://www.luogu.com.cn/problem/P1501
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
#define ls ch[x][0]
#define rs ch[x][1]
const int maxn = 2e5 + 5;
const int mod = 51061;
//原樹的實鏈：在輔助樹中都是一棵splay中，且splay的inorder是鏈由淺至深的排序
//原樹的虛鏈：子認父親，父不認子
struct Splay{
	ll ch[maxn][2], par[maxn], sz[maxn], val[maxn], sum[maxn], rev[maxn], add[maxn], mul[maxn];

	void clear(int x){
		ch[x][0] = ch[x][1] = par[x] = sz[x] = val[x] = sum[x] = add[x] = rev[x] = 0;
		mul[x] = 1;
	}
	int get(int x){ return ch[par[x]][1] == x; }
	int isroot(int x){
		clear(0);
		return ch[par[x]][0] != x && ch[par[x]][1] != x;
	}

	void pull(int p){
		sz[p] = (sz[ch[p][0]] + sz[ch[p][1]] + 1) % mod;
		sum[p] = (sum[ch[p][0]] + sum[ch[p][1]] + val[p]) % mod;
	}
	void push(int x){
		if(mul[x] != 1){ // 先push mul 再 push add
			if(ch[x][0]){
				(mul[ls] *= mul[x]) %= mod;
				(val[ls] *= mul[x]) %= mod;
				(sum[ls] *= mul[x]) %= mod;
				(add[ls] *= mul[x]) %= mod;
			}
			if(ch[x][1]){
				(mul[rs] *= mul[x]) %= mod;
				(val[rs] *= mul[x]) %= mod;
				(sum[rs] *= mul[x]) %= mod;
				(add[rs] *= mul[x]) %= mod;
			}
			mul[x] = 1;
		}
		if(add[x]){
			if(ch[x][0]){
				(val[ls] += add[x]) %= mod;
				(sum[ls] += sz[ls] * add[x]) %= mod;
				(add[ls] += add[x]) %= mod;
			}
			if(ch[x][1]){
				(val[rs] += add[x]) %= mod;
				(sum[rs] += sz[rs] * add[x]) %= mod;
				(add[rs] += add[x]) %= mod;
			}
			add[x] = 0;
		}
		if(rev[x]){ // 標懶標時兒子已經翻轉了，兒子的兒子沒有
			if(ls) rev[ls] ^= 1, swap(ch[ls][0], ch[ls][1]);
			if(rs) rev[rs] ^= 1, swap(ch[rs][0], ch[rs][1]);
			rev[x] = 0;
		}
	}
	void rotate(int x){
		int y = par[x], z = par[y], k = get(x);
		if(!isroot(y)) ch[z][y == ch[z][1]] = x; // has to be put here (different from splay tree)
		ch[y][k] = ch[x][!k];
		par[ch[x][!k]] = y;
		ch[x][!k] = y;	
		par[y] = x;
		par[x] = z;
		pull(y), pull(x);
	}
	void splay(int x){
		update(x); // 把旋轉會經過的點都push_down
		for(int p; p = par[x], !isroot(x); rotate(x)){
			if(!isroot(p)) rotate(get(p) == get(x) ? p : x);
		}
	}
	int access(int x){ // make x the preferred path
		int p;
		for(p = 0; x != 0; p = x, x = par[x]){
			splay(x); // 把x提到根
			ch[x][1] = p; // 虛邊變實邊
			pull(x);
		}
		return p; // p 的含意：x到根所在的splay tree的根
	}
	void update(int x){
		if(!isroot(x)) update(par[x]); //由上往下更新
		push(x);
	}
	void make_root(int p){
		p = access(p);
		swap(ch[p][0], ch[p][1]);
		rev[p] ^= 1;
	}
	void link(int x, int y){
		make_root(x);
		splay(x);
		par[x] = y;
	}
	void split(int x, int y){ // 拿出一棵splay, 維護x到y的路徑
		make_root(x);
		access(y);
		splay(y); // if we need to make y the root
	}
	void cut(int x, int y){
		//如果不用驗證是否合法
		make_root(x);
		access(y);
		splay(y); // 此時 x 一定是 y 的兒子，雙向段開即可
		ch[y][0] = par[x] = 0;
	}
	int find(int p){ //查詢 x 所在原樹的根
		access(p);
		splay(p);
		push(p);
		while(ch[p][0]) p = ch[p][0], push(p);
		splay(p); // 必要，保證複雜度正確
		return p;
	}
	void inorder(int x){
		if(ch[x][0]) inorder(ch[x][0]);
		cout<<x<<" ";
		if(ch[x][1]) inorder(ch[x][1]);
	}
} st;
int main(void){
	fastio;
	int n, q;
	cin>>n>>q;
	for(int i = 1; i <= n; i++) st.clear(i), st.val[i] = 1, st.pull(i);
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin>>a>>b;
		st.link(a, b);
	}
	while(q--){
		char op;
		int a, b;
		cin>>op>>a>>b;
		if(op == '+'){
			int c;
			cin>>c;
			st.split(a, b); //b is the root
			(st.add[b] += c) %= mod;
			(st.val[b] += c) %= mod;
			(st.sum[b] += st.sz[b] * c) %= mod;
		}
		else if(op == '-'){
			int c, d;
			cin>>c>>d;
			st.cut(a, b);
			st.link(c, d);
		}
		else if(op == '*'){
			int c;
			cin>>c;
			st.split(a, b);
			(st.val[b] *= c) %= mod;
			(st.sum[b] *= c) %= mod;
			(st.mul[b] *= c) %= mod;
		}
		else{
			st.split(a, b);
			cout<<st.sum[b]<<"\n";
		}
	}
}
