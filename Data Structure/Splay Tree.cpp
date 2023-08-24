/*
 	* Created : 2023/08/24
 	* Splay Tree
 	* Qualifications : 洛谷 P3369 【模板】普通平衡树 https://www.luogu.com.cn/problem/P3369
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
#define pb push_back
#define pf push_front
#define eb emplace_back
#define f first
#define s second
#define all(v) v.begin(), v.end()
#define lowbit(x) x&-x
const int maxn = 2e5 + 5;
const int INF = 1e9;
const int N = 998244353;
int rt, tot = 0, par[maxn], ch[maxn][2], val[maxn], cnt[maxn], sz[maxn];
// splay tree

struct Splay{
	void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
	bool get(int x) {return x == ch[par[x]][1];} // 判斷是否為右子樹
	void clear(int x){
		ch[x][0] = ch[x][1] = par[x] = val[x] = sz[x] = cnt[x] = 0;
	}

	void rotate(int x){ // 把x rotate 到原 parent 的位置
		int y = par[x], z = par[y], chk = get(x);
		ch[y][chk] = ch[x][chk ^ 1];
		if(ch[x][chk ^ 1]) par[ch[x][chk ^ 1]] = y; // '夾'在x跟y之間的子樹的parent 從x變成y
		ch[x][chk ^ 1] = y;
		par[y] = x;
		par[x] = z;
		if(z) ch[z][y == ch[z][1]] = x;
		maintain(y);
		maintain(x);
	}

	void splay(int x){
		for(int p = par[x]; p = par[x], p != 0; rotate(x)){
			if(par[p]) rotate(get(x) == get(p) ? p : x);
		}
		rt = x;
	}

	void insert(int k){
		if(!rt){
			val[++tot] = k;
			cnt[tot]++;
			rt = tot;
			maintain(rt);
			return;
		}
		int cur = rt, p = 0;
		while(true){
			if(val[cur] == k){ //找到值為k的節點，更新節點資訊
				cnt[cur]++;
				maintain(cur);
				maintain(p);
				splay(cur);
				break;
			}
			p = cur;
			cur = ch[cur][val[cur] < k]; // 否則向下找
			if(!cur){ // 遇到空節點->插入
				val[++tot] = k;
				cnt[tot]++;
				par[tot] = p;
				ch[p][val[p] < k] = tot;
				maintain(tot);
				maintain(p);
				splay(tot);
				break;
			}
		}
	}

	int rk(int k){ // 查詢k的排名
		int res = 0, cur = rt;
		while(true){
			if(k < val[cur]) cur = ch[cur][0];
			else{
				res += sz[ch[cur][0]];
				if(k == val[cur]){
					splay(cur);
					return res + 1;
				}
				res += cnt[cur];
				cur = ch[cur][1];
			}
		}
	}
	int kth(int k){ // 查詢排名k的數
		int cur = rt;
		while(true){
			if(ch[cur][0] && k <= sz[ch[cur][0]]) cur = ch[cur][0];
			else{
				k -= cnt[cur] + sz[ch[cur][0]];
				if(k <= 0){
					splay(cur);
					return val[cur];
				}
				cur = ch[cur][1];
			}
		}
	}

	int pre(){ // 查詢前驅(小於x最大的數) : 插入x(此時x位於根) -> 前驅為左子樹最右節點(此部分在做的事) -> 刪去x 
		int cur = ch[rt][0];
		if(!cur) return cur;
		while(ch[cur][1]) cur = ch[cur][1];
		splay(cur);
		return cur;
	}

	int nxt(){ // 查詢後驅
		int cur = ch[rt][1];
		if(!cur) return cur;
		while(ch[cur][0]) cur = ch[cur][0];
		splay(cur);
		return cur;
	}
	void del(int k){
		rk(k);
		if(cnt[rt] > 1){
			cnt[rt] --;
			maintain(rt);
			return;
		}
		if(!ch[rt][0] && !ch[rt][1]){
			clear(rt);
			rt = 0;
			return;
		}
		if(!ch[rt][0]){
			int cur = rt;
			rt = ch[rt][1];
			par[rt] = 0;
			clear(cur);
			return;
		}
		if(!ch[rt][1]){
			int cur = rt;
			rt = ch[rt][0];
			par[rt] = 0;
			clear(cur);
			return;
		}
		int cur = rt;
		int x = pre(); // 把左樹最右點轉上來，此時cur左樹為空，父子關係為 x -> cur -> ch[cur][1]，把x的右子樹設為ch[cur][1]即可
		par[ch[cur][1]] = x;
		ch[x][1] = ch[cur][1];
		clear(cur);
		maintain(rt);
	}
} tree;

int main(void){
	fastio;
	int n;
	cin>>n;
	for(int i = 0; i < n; i++){
		int op, x;
		cin>>op>>x;
		if(op == 1) tree.insert(x);
		else if(op == 2) tree.del(x);
		else if(op == 3) cout<<tree.rk(x)<<"\n";
		else if(op == 4) cout<<tree.kth(x)<<"\n";
		else if(op == 5) tree.insert(x), cout<<val[tree.pre()]<<"\n", tree.del(x);
		else tree.insert(x), cout<<val[tree.nxt()]<<"\n", tree.del(x);
	}
}
