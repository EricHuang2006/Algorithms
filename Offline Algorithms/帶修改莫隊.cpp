/*
  * Created : 2023/09/02
  * 帶修改莫隊：l, r 分塊, t 單調遞增
  * 分塊大小：n^(2/3)
  * 時間複雜度：O(n^(5/3))
  * 範例：洛谷 P1903 [国家集训队] 数颜色 / 维护队列 https://www.luogu.com.cn/problem/P1903
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
const int maxw = 1e6 + 5;
const int INF= 1e9 + 5;
const int block = 2500; // n^(2/3)
//帶修改莫隊 - l, r 分塊, t 單調遞增
struct query{
	int l, r, t, id;
	bool operator < (const query &other) const{
		if(l / block != other.l / block) return l / block < other.l / block;
		else if(r / block != other.r / block) return r / block < other.r / block;
		else return t < other.t;
	}
	query(int _l, int _r, int _t, int _id) : l(_l), r(_r), t(_t), id(_id){}
};
struct modify{
	int pos, val, t;
	modify(int _pos, int _val, int _t) : pos(_pos), val(_val), t(_t){}
};
int cnt[maxw], a[maxn];
int distinct = 0;
vector<query> qry;
vector<modify> chg;
void del(int pos){
	cnt[a[pos]] --;
	if(!cnt[a[pos]]) distinct --;
}
void add(int pos){
	cnt[a[pos]]++;
	if(cnt[a[pos]] == 1) distinct++;
}
int main(void){
	fastio;
	int n, m;
	cin>>n>>m;
	for(int i = 0; i < n; i++) cin>>a[i];
	int qrsz = 0;
	for(int i = 0; i < m; i++){
		char q; int l, r;
		cin>>q>>l>>r;
		l--;
		if(q == 'Q'){
			r--;
			qry.pb(query(l, r, i, qrsz++));
		}
		else{
			chg.pb(modify(l, r, i));
		}
	}
	sort(qry.begin(), qry.end());
	int t = 0, tid = 0, l = 0, r = -1;
	vector<int> ans(qrsz);
	for(int i = 0; i < qry.size(); i++){
		while(l < qry[i].l) del(l++);
		while(l > qry[i].l) add(--l);
		while(r > qry[i].r) del(r--);
		while(r < qry[i].r) add(++r);
		while(tid < chg.size() && qry[i].t > chg[tid].t){
			int pos = chg[tid].pos;
			if(pos >= l && pos <= r) del(pos);
			swap(a[pos], chg[tid].val);
			if(pos >= l && pos <= r) add(pos);
			tid++;
		}
		while(tid > 0 && qry[i].t < chg[tid - 1].t){
			tid--;
			int pos = chg[tid].pos;
			if(pos >= l && pos <= r) del(pos);
			swap(a[pos], chg[tid].val);
			if(pos >= l && pos <= r) add(pos);
		}
		ans[qry[i].id] = distinct;
	}
	for(auto x : ans) cout<<x<<"\n";
}
