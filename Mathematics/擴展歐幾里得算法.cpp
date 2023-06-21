/*
  2023-6-21
  求 ax + by = gcd(a, b) 的一組解
  兩種算法 ： 遞迴法與迭代法
  應用 ： 求模逆元 ： a^(-1) ≡ b 
                  => ax + by = 1 
                  => ax ≡ 1 (mod b)
                  => x = a^(-1)
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//遞迴式
ll extgcd(ll a, ll b, ll &x, ll &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	extgcd(b, a % b, y, x);
	y -= (a / b) * x;
	return y;
}

//迭代法 ： 利用矩陣轉移
/*
|x1 x2|     transition : |0      1   |
|x3 x4|                  |1  -(a / b)|
*/
ll extgcd2(ll a, ll b, ll &x, ll &y){
    ll x1 = 1, x2 = 0, x3 = 0, x4 = 1;
    while(b != 0){
        ll c = a / b;
        tie(x1, x2, x3, x4, a, b) = make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
    }
    x = x1, y = x2;
    return a;
}
