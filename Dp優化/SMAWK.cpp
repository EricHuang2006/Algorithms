/*
  Created : 2024.4.14
  Description : Compute Row minima in O(n + m) in a totally monotone matrix
  Main functions : Reduce and Interpolate
  Task - CF - 1432M. Milutin's Plums
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#pragma GCC optimize("Ofast")
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define int long long
#define lowbit(x) x&-x
const int INF = 1e9 + 7;
const int N = 1e9 + 7;
const int maxn = 1e6 + 5;
//smawk : compute row minima in O(n + m)
map<pll, int> mp;
int f(int u, int v){
	if(mp.count({u, v})) return mp[{u, v}];
	cout<<"? "<<u + 1<<" "<<v + 1<<"\n";
	int x;
	cin>>x;
	return mp[{u, v}] = x;
}

bool select(int r, int u, int v){
	return f(r, u) > f(r, v);
}

vector<int> solve(vector<int> &r, vector<int> &c){
	if(r.size() == 1){
		vector<int> opt(1, 0);
		for(int i = 1; i < c.size(); i++){
			if(select(r[0], c[opt[0]], c[i])){
				opt[0] = i;
			}
		}
		return opt;
	}
	//reduce
	vector<int> st, rev;
	for(int i = 0; i < c.size(); i++){
		while(!st.empty() && select(r[st.size() - 1], st.back(), c[i])){
			st.pop_back();
			rev.pop_back();
		}
		if(st.size() < r.size()){
			st.pb(c[i]);
			rev.pb(i);
		}
	}
	//interpolate
	vector<int> half;
	for(int i = 0; i < r.size(); i += 2){
		half.pb(r[i]);
	}
	vector<int> ans(r.size());
	auto interp = solve(half, st);
	for(int i = 0; i < interp.size(); i++) ans[i * 2] = interp[i];
	for(int i = 1; i < ans.size(); i += 2){
		int s = ans[i - 1], e = (i + 1 < ans.size() ? ans[i + 1] : st.size() - 1);
		ans[i] = s;
		for(int j = s + 1; j <= e; j++){
			if(select(r[i], st[ans[i]], st[j])) ans[i] = j;
		}
	}
	for(int i = 0; i < ans.size(); i++) ans[i] = rev[ans[i]];
	return ans;
}

vector<int> smawk(int n, int m){
	vector<int> r(n), c(m);
	iota(r.begin(), r.end(), 0);
	iota(c.begin(), c.end(), 0);
	return solve(r, c);
}

signed main(void){
	// fastio;
	int n, m;
	cin>>n>>m;
	auto opt = smawk(n, m);
	int ans = INF;
	for(int i = 0; i < n; i++){
		ans = min(ans, f(i, opt[i]));
	}
	cout<<"! "<<ans<<"\n";
}
