#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#pragma GCC optimize("Ofast")
#define eb emplace_back
#define pb push_back
#define f first
#define s second
const int maxn = 2e5 + 5;
int n, q, cnt = 0;

struct node{
	ll sum;
	node *l, *r;
	node(ll x) : sum(x), l(nullptr), r(nullptr){}
	node(node *_l, node *_r) : sum(_l->sum + _r->sum), l(_l), r(_r){}
	node(node *nd) : sum(nd->sum), l(nd->l), r(nd->r){}
};

node *rt[maxn]; // root of the persistent arrays
node* build(vector<ll>& a, int l = 0, int r = n - 1){
	if(l == r) return new node(a[l]);
	int m = (l + r) / 2;
	return new node(build(a, l, m), build(a, m + 1, r));
}

node* upd(node *nd, int pos, ll val, int l = 0, int r = n - 1){
	if(l == r) return new node(val);
	int m = (l + r) / 2;
	if(pos <= m) return new node(upd(nd->l, pos, val, l, m), nd->r);
	else return new node(nd->l, upd(nd->r, pos, val, m + 1, r));
}

ll qry(node *nd, int l, int r, int L = 0, int R = n - 1){
	if(l > R || r < L) return 0;
	if(l <= L && r >= R) return nd->sum;
	int m = (L + R) / 2;
	return qry(nd->l, l, r, L, m) + qry(nd->r, l, r, m + 1, R);
}

int main(void){
	fastio;	
	cin>>n>>q;
	vector<ll> a(n);
	for(int i = 0; i < n; i++) cin>>a[i];
	rt[cnt++] = build(a);
	for(int i = 0; i < q; i++){
		int t;
		cin>>t;
		if(t == 1){
			int k, a, x;
			cin>>k>>a>>x;
			k--, a--;
			rt[k] = upd(rt[k], a, x);
		}
		else if(t == 2){
			int k, a, b;
			cin>>k>>a>>b;
			k--, a--, b--;
			cout<<qry(rt[k], a, b)<<"\n";
		}
		else{
			int k;
			cin>>k;
			k--;
			rt[cnt++] = new node(rt[k]);
		}
	}
	
}
