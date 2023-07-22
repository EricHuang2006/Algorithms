/*
  * NTT
  * Date: 2023/07/23
  * Description: calculate polynomial multiplication module a prime in O(nlogn)
  * Verfication: Yosupo Library Checker - Convolution: https://judge.yosupo.jp/submission/151758
*/
#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
typedef long long ll;
const int N = 998244353, g = 3;
using cd = complex<double>;
const double PI = acos(-1);

ll fpow(ll a, ll b){
	ll ret = 1;
	while(b > 0){
		if(b & 1) ret = ret * a % N;
		a = a * a % N;
		b >>= 1;
	}
	return ret;
}
ll inv(ll a){ return fpow(a, N - 2); }
void fft(vector<ll> &a, bool invert = 0){ // interative version
	int n = a.size();
	int lg_n = __lg(n);
	for(int i = 1, j = 0; i < n; i++){ //bit-reversal permutation
		int bit = n >> 1;
		for(; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if(i < j) swap(a[i], a[j]);
	}
	for(int len = 2; len <= n; len <<= 1){
		ll wn = fpow(g, (N - 1) / len); // g ^ (N - 1) = 1, wn ^ len = 1
		if(invert) wn = inv(wn); 	
		for(int i = 0; i < n; i += len){
			ll w = 1;
			for(int j = 0; j < len / 2; j++){
				ll u = a[i + j], v = a[i + j + len / 2] * w % N;
				a[i + j] = (u + v) % N;
				a[i + j + len / 2] = (u - v + N) % N;
				(w *= wn) %= N;
			}
		}
	}
	ll n_1 = inv(n);
	if(invert) for(auto &x : a) (x *= n_1) %= N;
}
vector<int> multiply(vector<ll> const& a, vector<ll> const& b){
	vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < a.size() + b.size()){
		n <<= 1;
	}
	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for(int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, true);
	vector<int> result(a.size() + b.size() - 1);
	for(int i = 0; i < a.size() + b.size() - 1; i++){
		result[i] = fa[i];
	}
	return result;
}
int main(){
	fastio;
	int n, m;
	cin>>n>>m;
	vector<ll> a(n), b(m);
	for(int i = 0; i < n; i++) cin>>a[i];
	for(int i = 0; i < m; i++) cin>>b[i];
	auto v = multiply(a, b);
	for(auto x : v) cout<<x<<" ";
	cout<<"\n";
}
