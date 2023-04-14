//題目 : ABC261: F - Sorting Color Balls
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 5;	
int n;

struct node{
	node *l, *r;
	int cnt;
	node() : cnt(0), l(nullptr), r(nullptr){}
	node(ll c) : cnt(c), l(nullptr), r(nullptr){}
};
ll cnt(node *nd) {
	return nd? nd->cnt : 0;
}
void upd(node *nd, int pos, int val = 1, int l = 0, int r = n - 1){
	if(l == r){
		nd->cnt += val;
		return;
	}
	int m = (l + r) / 2;
	if(nd->l == nullptr) nd->l = new node();
	if(nd->r == nullptr) nd->r = new node();
	if(pos <= m) upd(nd->l, pos, val, l, m);
	else upd(nd->r, pos, val, m + 1, r);
	nd->cnt = nd->l->cnt + nd->r->cnt;	
}

ll qry(node *nd, int l, int r, int L = 0, int R = n - 1){
	if(nd == nullptr) return 0;
	if(l == L && r == R){
		return nd->cnt;
	}
	int m = (L + R) / 2;
	if(l > m) return qry(nd->r, l, r, m + 1, R);
	else if(r <= m) return qry(nd->l, l, r, L, m);
	return qry(nd->l, l, m, L, m) + qry(nd->r, m + 1, r, m + 1, R);
}
node* seg[maxn];

void init(){
	for(int i = 0; i < maxn; i++){
		seg[i] = new node();
	}
}

int main(void){
	init();
	cin>>n;
	vector<int> x(n), c(n + 1), sz(n + 1);
	for(int i = 0; i < n; i++) cin>>c[i];
	for(int i = 0; i < n; i++){
		cin>>x[i];
		x[i] --;
	}
	ll ans = 0;
	for(int i = 0; i < n; i++){
		ans += i - qry(seg[0], 0, x[i]);
		ans -= sz[c[i]] - qry(seg[c[i]], 0, x[i]);
		sz[c[i]] ++;
		upd(seg[0], x[i]);
		upd(seg[c[i]], x[i]);
	}
	cout<<ans<<"\n";
}
