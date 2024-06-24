/*
  * Created : 2024.6.24
  * Powerful Number 篩
  * Description : 求積性函數的前綴和
  * f = g * h，若 G(n) 能 O(1) 求，複雜度 O(sqrt(n) * log(n))，若用杜教篩則為杜教篩的複雜度
  * 例題：P5325 【模板】Min_25 筛 (https://www.luogu.com.cn/problem/P5325)
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
#define eb emplace_back 
#define f first
#define s second
#define int long long
#define lowbit(x) x&-x
const int maxn = 2e6 + 5;
const int N = 1e9 + 7;
const int INF = 1e18;
int lp[maxn], phi[maxn], sum[maxn], h[maxn][35], vis[maxn][35];
map<int, int> mp_G;
vector<int> pr;
int n, ans = 0;

ll fpow(ll a, ll b){
	ll ret = 1;
	while(b){
		if(b & 1) ret = ret * a % N;
		a = a * a % N;
		b >>= 1;
	}
	return ret;
}
ll inv(ll a){ return fpow(a, N - 2);}

void linearsieve(){
	phi[1] = 1;
	for(int i = 2; i < maxn; i++){
		if(!lp[i]) pr.pb(i), lp[i] = i, phi[i] = i - 1;
		for(auto x : pr){
			if(i * x >= maxn) break;
			lp[i * x] = x;
			if(lp[i] == x){
				phi[i * x] = phi[i] * x;
				break;
			}
			phi[i * x] = phi[i] * (x - 1);
		}
	}
	for(int i = 1; i < maxn; i++) sum[i] = (sum[i - 1] + i * phi[i]) % N;
}

int s2(int n){
	static const int inv6 = inv(6);
	n %= N;
	return n * (n + 1) % N * (2 * n + 1) % N * inv6 % N;
}

int G(int n){
	static const int inv2 = inv(2);
	if(n < maxn) return sum[n];
	if(mp_G.count(n)) return mp_G[n];
	int ans = s2(n);
	for(int i = 2, j; i <= n; i = j + 1){
		j = n / (n / i);
		(ans -= (i + j) % N * (j - i + 1) % N * inv2 % N * G(n / i) % N - N) %= N;
	}
	return mp_G[n] = ans;
}

void dfs(int d, int hd, int p){ // dfs 出所有 PN
	(ans += hd * G(n / d)) %= N;
	for(int i = p; i < pr.size(); i++){
		if(d > n / pr[i] / pr[i]) break;
		int c = 2;
		for(int x = d * pr[i] * pr[i]; x <= n; x *= pr[i], c++){
			if(!vis[i][c]){
				int f = fpow(pr[i], c);
				f = f * (f - 1) % N;
				int g = pr[i] * (pr[i] - 1) % N;
				int t = pr[i] * pr[i] % N;
				for(int j = 1; j <= c; j++){
					(f -= g * h[i][c - j] % N - N) %= N;
					(g *= t) %= N;
				}
				h[i][c] = f;
				vis[i][c] = true;
			}
			if(h[i][c]) dfs(x, hd * h[i][c] % N, i + 1);
		}
	}
}

signed main(void){
	fastio;
	cin>>n;
	linearsieve();
	for(int i = 0; i < pr.size(); i++) h[i][0] = 1;
	dfs(1, 1, 0);
	cout<<ans<<"\n";
}
