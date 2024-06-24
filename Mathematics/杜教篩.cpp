/*
 * Created : 2024.6.24
 * 杜教篩
 * Description : 在亞線性的時間內求數論函數的前綴和
 * 複雜度：O(n^(2/3))
 * 例題：P4213 【模板】杜教筛 (https://www.luogu.com.cn/problem/P4213)
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
#define pb push_back
#define eb emplace_back 
#define f first
#define s second
#define int long long
#define lowbit(x) x&-x
const int maxn = 1e6 + 5;
int sum_mu[maxn];
map<ll, ll> mp_mu;
int mu[maxn], lp[maxn];
vector<int> pr;
int n;

int S_mu(int n){
	if(n < maxn) return sum_mu[n];
	if(mp_mu.find(n) != mp_mu.end()) return mp_mu[n];
	int ret = 1;
	for(int i = 2, j; i <= n; i = j + 1){
		j = n / (n / i);
		ret -= S_mu(n / i) * (j - i + 1);
	}
	return mp_mu[n] = ret;
}

int S_phi(int n){
	int ret = 0;
	for(int i = 1, j; i <= n; i = j + 1){
		j = n / (n / i);
		ret += (S_mu(j) - S_mu(i - 1)) * (n / i) * (n / i);
	}
	return (ret - 1) / 2 + 1;
}
signed main(void){
	fastio;
	int t;
	cin>>t;
	mu[1] = 1;
	for(int i = 2; i < maxn; i++){
		if(!lp[i]) lp[i] = i, pr.pb(i), mu[i] = -1;
		for(auto x : pr){
			if(i * x >= maxn) break;
			lp[i * x] = x, mu[i * x] = -1 * mu[i];
			if(lp[i] == x){
				mu[i * x] = 0;
				break;
			}
		}
	}
	for(int i = 1; i < maxn; i++) sum_mu[i] = sum_mu[i - 1] + mu[i];
	while(t--){
		cin>>n;
		cout<<S_phi(n)<<" "<<S_mu(n)<<"\n";
	}
}
