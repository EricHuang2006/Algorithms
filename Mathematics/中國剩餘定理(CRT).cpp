//例題：abc286 - F - Guess The Number 2 
/*
  2023-6-21
  解線性同餘方程(Linear Congruences)
  要求：模數兩兩互質，模數不一定要是質數(使用extgcd求模逆元)
  下面列出樸素算法與 Garner 算法
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll extgcd(ll a, ll b, ll &x, ll &y){
    ll x1 = 1, x2 = 0, x3 = 0, x4 = 1;
    while(b != 0){
        ll c = a / b;
        tie(x1, x2, x3, x4, a, b) = make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
    }
    x = x1, y = x2;
    return a;
}

//Garner 算法使用 mixed radix representation : n = x1 + x2 * p1 + x3 * p1 * p2 + x4 * p1 * p2 * p3 ...
ll CRT(vector<ll> p, vector<ll> a){
	int n = p.size();
	vector<vector<ll>> r(n, vector<ll>(n)); //r[i][j] 為p[i] 對 p[j] 的模逆元
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			ll x, y;
			extgcd(p[i], p[j], x, y);
			r[i][j] = x;
		}
	}
	vector<ll> x(n);
	for(int i = 0; i < n; i++){
		x[i] = a[i];
		for(int j = 0; j < i; j++){
			x[i] = ((x[i] - x[j]) * r[j][i] % p[i] + p[i]) % p[i]; // 主要運算過程
		}
	}
	ll prod = 1, ret = 0;
	for(int i = 0; i < n; i++) prod *= p[i];
	for(int i = 0; i < n; i++){
		ll term = x[i];
		for(int j = 0; j < i; j++) (term *= p[j]) %= prod;
		(ret += term) %= prod;
	}
	return ret;
}

//樸素算法(程式碼短很多?)
ll CRT2(vector<ll> p, vector<ll> a){
	ll n = p.size(), prod = 1, ret = 0;
	for(int i = 0; i < n; i++) prod *= p[i];
	for(int i = 0; i < n; i++){
		ll m = (prod / p[i]);
		ll x, y;
		extgcd(m, p[i], x, y);
		ret = ((ret + a[i] * m * x) % prod + prod) % prod;
	}
	return ret;
}
