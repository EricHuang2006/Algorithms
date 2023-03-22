#include<bits/stdc++.h>
using namespace std;
int n, m, k;
struct dsu_save{
	
	int v, rnkv, u, rnku;
	dsu_save(){}
	dsu_save(int _v, int _rnkv, int _u, int _rnku) : v(_v), u(_u), rnkv(_rnkv), rnku(_rnku){}	
};

struct dsu_with_rollback{
	vector<int> par, rnk;
	int comps;
	stack<dsu_save> op;
	
	dsu_with_rollback(){}
	dsu_with_rollback(int n){
		par.resize(n);
		rnk.resize(n);
		for(int i = 0; i < n; i++){
			par[i] = i;
			rnk[i] = 0;
		}
		comps = n;
	}
	
	int find_set(int v){
//		cout<<v<<" "<<par[v]<<endl;;
		return (v == par[v]) ? v : find_set(par[v]);
	}
	
	bool unite(int v, int u){
		v = find_set(v);
		u = find_set(u);
//		cout<<"roots: "<<v<<" "<<u<<endl;
		if(v == u) {
//			cout<<"no";
			return false;	
		}
//		cout<<"unite : "<<v<<" "<<u<<endl;
		comps--;
		if(rnk[v] > rnk[u]) swap(v, u);
		op.push(dsu_save(v, rnk[v], u, rnk[u]));
		par[v] = u;
		if(rnk[u] == rnk[v]) rnk[u] ++;
		return true;
	}
	
	void roll_back(){
		if(!op.empty()){
			auto x = op.top(); op.pop();
//			cout<<"Roll_back : "<<x.v<<" "<<x.u<<endl;
			comps++;
			par[x.v] = x.v;
			rnk[x.v] = x.rnkv;
			par[x.u] = x.u;
			rnk[x.u] = x.rnku;
		}
	}	
};

struct query{
	int v, u;
	bool united = 0;
	query(int _v, int _u) : v(_v), u(_u){}
};

bool operator <(const query& a, const query& b){
	return a.v < b.v || (a.v == b.v && a.u < b.u);
}
struct Tree{
	vector<vector<query>> t;
	dsu_with_rollback dsu;
	int T;
	
	Tree(){}
	Tree(int _T, int n) : T(_T){
		dsu = dsu_with_rollback(n);
		t.resize(4 * T + 4);
	}
	void insert(int v, int l, int r, int ql, int qr, query q){
		if(ql > qr) return;
		if(l == ql && r == qr){
//			cout<<"insert: "<<l<<" "<<r<<" "<<q.v<<" "<<q.u<<endl;
			t[v].push_back(q);
			return;
		}
		int mid = (l + r) / 2;
		insert(2 * v, l, mid, ql, min(qr, mid), q);
		insert(2 * v + 1, mid + 1, r, max(ql, mid + 1), qr, q);
	}
	
	void traversal(int idx, int l, int r, vector<int>& ans){
//		cout<<"traversal : "<<idx<<" "<<l<<" "<<r<<endl;
		for(auto& q : t[idx]){
//			cout<<q.united<<" "<<q.v<<" "<<q.u<<endl;
			q.united = dsu.unite(q.v, q.u);
//			cout<<q.united<<endl;
		}
		if(l == r){
			ans[l] = dsu.comps;
//			cout<<"ans["<<l<<"]: "<<ans[l]<<endl;
		}
		else{
			int mid = (l + r) / 2;
			traversal(2 * idx, l, mid, ans);
			traversal(2 * idx + 1, mid + 1, r, ans);
		}
		for(query q : t[idx]){
			if(q.united){
				dsu.roll_back();
			}
		}
	}
	vector<int> solve(){
		vector<int> ans(T);
		traversal(1, 0, T - 1, ans);
		return ans;
	}
};


int main(void){
	
	cin>>n>>m>>k;
	Tree segtree(k + 1, n);
	map<query, int> mp;
	for(int i = 0; i < m; i++){
		int a, b;
		cin>>a>>b;
		a--, b--;
		if(a > b) swap(a, b);
		mp[query(a, b)] = 1;
	}
	for(int i = 2; i < k + 2; i++){
		int type, a, b;
		cin>>type>>a>>b;
		a--, b--;
		if(a > b) swap(a, b);
		query q = query(a, b);
		if(type == 2){
			segtree.insert(1, 0, k, mp[q] - 1, i - 2, q);
			mp[q] = 0;
		}
		else{
			mp[q] = i;
		}
	}
	for(auto [q, val]: mp){
		if(val != 0){
			segtree.insert(1, 0, k, mp[q] - 1, k, q);
		}
	}
	vector<int> ans(segtree.solve());
	//segtree.traversal(1, 0, k + 1, ans);
	for(auto x : ans) cout<<x<<endl;
}
/*
10 10 10
6 3
8 3
5 4
9 5
2 1
9 7
8 7
8 6
4 2
7 10
2 9 5
2 7 10
1 10 8
1 10 9
2 2 1
1 5 10
1 2 8
1 9 6
2 6 3
2 8 3
*/
