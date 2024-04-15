/*
  Created : 2024.4.15
  Description : Find a factor of n in O(n^(1/4))
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define int long long

ll f(ll t, ll c, ll n){
	return (t * t + c) % n;
}

ll Pollard_Rho(ll x){
	ll t = 0;
	ll c = rand() % (x - 1) + 1;
	ll s = t;
	ll val = 1;
	for(int goal = 1;; goal <<= 1, s = t, val = 1){
		for(int step = 1; step <= goal; step++){
			t = f(t, c, x);
			val = val * abs(t - s) % x;
			if(!val) return x;
			if(step % 127 == 0){
				ll d = __gcd(val, x);
				if(d > 1) return d;
			}
		}
		ll d = __gcd(val, x);
		if(d > 1) return d;
	}
}
