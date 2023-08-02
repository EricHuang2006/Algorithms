/*
  * Miller_Rabin Primiality Test
  * Created : 2023/08/02
  * Check for primality of a number in O(log^3n) 
  * For n < 2^64, we can use a = {2, 3, 5, 7, 11,13,17, 19, 23, 29, 31, 37}
*/
#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false), cin.tie(0)

using u64 = uint64_t;
using u128 = __uint128_t;

u64 fpow(u64 a, u64 b, u64 n){
	u64 ret = 1;
	while(b > 0){
		if(b & 1) ret = (u128)ret * a % n;
		a = (u128)a * a % n;
		b >>= 1;
	}
	return ret;
}
bool check_composite(u64 n, u64 a, u64 d, int s){
	u64 x = fpow(a, d, n);
	if(x == 1 || x == n - 1) return false;
	for(int r = 1; r < s; r++){
		x = (u128)x * x % n;
		if(x == n - 1) return false;
	}
	return true;
}
bool MillerRabin(u64 n){
	if(n < 2) return false;
	int s = 0;
	u64 d = n - 1;
	while(!(d & 1)){
		d >>= 1;	
		s++;
	}
	for(auto a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){ // sufficient for n < 2^64
		if(n == a) return true;
		if(check_composite(n, a, d, s)) return false;
	}
	return true;
}
int main(void){
	fastio;
	int t;
	cin>>t;
	while(t--){
		u64 n;
		cin>>n;
		if(MillerRabin(n)) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
