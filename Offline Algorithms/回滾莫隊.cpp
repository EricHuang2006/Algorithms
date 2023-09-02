/*
  	* 回滾莫隊 : CF - F. Souvenirs https://codeforces.com/contest/765/problem/F
 	* Created : 2023/09/02
  	* 想法：當加入和刪除只有一種操作好做時，就只做一種操作，剩下交給回滾解決
	* Description :
                                  7 continue
                              --------->
   	  6 (roll_back all)
  	<----
         	 5 (roll_back to query range, 算貢獻)
	      <------
             4 (delete)
  	----------->
                	 3 (roll_back to query range)
                     --------> 
                            	      2 (delete)
              	      <---------------------------------
                           1 (create entire list)
  	<---------------------------------------------->
  	|-----*------|--------*-------------------------    | | = block range, * * = query range
   
   	* 做兩次，一次只算 [br, n] 對自己的貢獻(不擴張到[bl, br - 1])，一次照上面的方法做，計算[bl, br - 1]的貢獻
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#pragma GCC optimize("Ofast")
#define pb push_back
#define pf push_front
#define eb emplace_back
#define f first
#define s second
#define all(v) v.begin(), v.end()
#define lowbit(x) x&-x
#define ckmin(a, b) a = min(a, b)
const int maxn = 2e5 + 5;
const int INF = 2e9 + 7;
const int bk = 400;
int a[maxn];
int n;
struct qry{
	int l, r, id;
	qry(){}
	qry(int _l, int _r, int _id) : l(_l), r(_r), id(_id){}
	bool operator < (const qry& other) const{
		return r < other.r;
	}
};
struct list{
	int pre[maxn], nxt[maxn];
	void init(){
		for(int i = 0; i < maxn; i++) pre[i] = 0, nxt[i] = maxn - 1;
	}
	void del(int x){
		nxt[pre[x]] = nxt[x];
		pre[nxt[x]] = pre[x];
	}
	void add_link(int x, int y){
		nxt[x] = y, pre[y] = x;
	}
	int back(int x){
		nxt[pre[x]] = x;
		pre[nxt[x]] = x;
		int res = INF;
		if(pre[x] != 0) res = min(res, abs(a[x] - a[pre[x]]));
		if(nxt[x] != maxn - 1) res = min(res, abs(a[x] - a[nxt[x]]));
		return res;
	}
	void ck(){
		int cur = 0;
		cout<<"list : ";
		while(cur != maxn - 1){
			cout<<cur<<" ";
			cur = nxt[cur];
		}
		cout<<"\n";
	}
} ls, ls2;
int main(void){
	fastio;
	cin>>n;
	vector<pll> p(n);
	for(int i = 1; i <= n; i++) cin>>a[i], p[i - 1] = {a[i], i};
	int m;
	cin>>m;
	vector<vector<qry>> q(n / bk + 1);
	for(int i = 0; i < m; i++){
		int l, r;
		cin>>l>>r;
		q[(l - 1) / bk].pb(qry(l, r, i));
	}
	for(int i = 0; i < q.size(); i++) sort(q[i].begin(), q[i].end());
	sort(p.begin(), p.end());
	vector<int> ans(m);
	for(int i = 0; i < q.size(); i++){
		if(!q[i].size()) continue;
		int bl = i * bk + 1, br = min(n + 1, (i + 1) * bk + 1); //bl = 此塊起點，br = 下一塊起點
		ls.init(), ls2.init();
		int pre = 0, pre2 = 0;
		for(int j = 0; j < n; j++){
			if(p[j].s < bl) continue;
			ls2.add_link(pre2, p[j].s);
			pre2 = p[j].s;
			if(p[j].s < br) continue;
			ls.add_link(pre, p[j].s);
			pre = p[j].s;
		}
		for(int j = n; j >= br; j--) ls.del(j), ls2.del(j);
		for(int j = br - 1; j > q[i][0].r; j--) ls2.del(j);
		int l, r = br - 1, r2 = min(br - 1, q[i][0].r);
		int res = INF;
		for(auto [ql, qr, id] : q[i]){
			while(r2 < qr && r2 < br - 1) ls2.back(++r2);
			while(r < qr) res = min(res, ls.back(++r)), ls2.back(r); // 處理右端點擴張之貢獻
			int res2 = INF;
			for(int j = bl; j <= r2; j++) ls2.del(j);	
			for(int j = r2; j >= ql; j--) res2 = min(res2, ls2.back(j)); // 處理塊中的貢獻
			ans[id] = min(res, res2);
			for(int j = ql - 1; j >= bl; j--) ls2.back(j);
		}
	}
	for(auto x : ans) cout<<x<<"\n";
}
