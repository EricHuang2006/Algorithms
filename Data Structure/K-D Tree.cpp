/*
  Created : 2024.2.5
  Description : K-D Tree
  處理高維 範圍查詢操作 / 鄰域查詢操作
  Verification : Lougu - P4148 简单题 https://www.luogu.com.cn/problem/P4148
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
const int maxn = 2e5 + 5, LG = 18;
//二進位分組

struct pt{
	int x[2];
	int val, sum;
	int l, r;
	int L[2], R[2];
} st[maxn], l, h; // l, h -> query

int rt[LG];
int b[maxn], cnt = 0;

void upd(int v){
	st[v].sum = st[st[v].l].sum + st[st[v].r].sum + st[v].val;
	for(auto k : {0, 1}){
		st[v].L[k] = st[v].R[k] = st[v].x[k];
		if(st[v].l){
			st[v].L[k] = min(st[v].L[k], st[st[v].l].L[k]);
			st[v].R[k] = max(st[v].R[k], st[st[v].l].R[k]);
		}
		if(st[v].r){
			st[v].L[k] = min(st[v].L[k], st[st[v].r].L[k]);
			st[v].R[k] = max(st[v].R[k], st[st[v].r].R[k]);
		}
	}
}

int build(int l, int r, int dep = 0){
	int m = (l + r) / 2;
	std::nth_element(b + l, b + m, b + r + 1, 
		[&](int x, int y){return st[x].x[dep] < st[y].x[dep];});
	int x = b[m];
	if(l < m) st[x].l = build(l, m - 1, dep ^ 1);
	if(m < r) st[x].r = build(m + 1, r, dep ^ 1);
	upd(x);
	return x;
}

void append(int &v){ // demolish a tree
	if(!v) return;
	b[++cnt] = v;
	append(st[v].l);
	append(st[v].r);
	v = 0;
}
//(!(l.x[k] <= t[p].L[k] && t[p].R[k] <= h.x[k]));
int qry(int v){
	if(!v) return 0;
	bool flag = false;
	for(auto k : {0, 1}) flag |= !(l.x[k] <= st[v].L[k] && st[v].R[k] <= h.x[k]);
	if(!flag) return st[v].sum; // completely inside qry 
	for(auto k : {0, 1})
		if(st[v].R[k] < l.x[k] || st[v].L[k] > h.x[k]) return 0;
	int ans = 0;
	flag = false;
	for(auto k : {0, 1}) flag |= !(l.x[k] <= st[v].x[k] && st[v].x[k] <= h.x[k]);
	if(!flag) ans += st[v].val;
	return ans += qry(st[v].l) + qry(st[v].r);
}

signed main(void){
	fastio;
	int n;
	cin>>n;
	int lst = 0;
	n = 0;
	while(true){
		int op;
		cin>>op;
		if(op == 1){
			int x, y, a;
			cin>>x>>y>>a;
			x ^= lst, y ^= lst, a ^= lst;
			st[++n] = {{x, y}, a};
			b[cnt = 1] = n;
			for(int sz = 0;;sz++){
				if(!rt[sz]){
					rt[sz] = build(1, cnt);
					break;
				}
				else append(rt[sz]);
			}
		}
		else if(op == 2){
			cin>>l.x[0]>>l.x[1]>>h.x[0]>>h.x[1];
			l.x[0] ^= lst, l.x[1] ^= lst, h.x[0] ^= lst, h.x[1] ^= lst;
			lst = 0;
			for(int i = 0; i < LG; i++) lst += qry(rt[i]);
			cout<<lst<<"\n";
		}
		else break;
	}
}
