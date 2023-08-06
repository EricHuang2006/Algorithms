/*
  * Created: 2023/08/06
  * 類歐幾里得算法
  * f(n, a, b, c) = sum_{0<=i<=n}{(ai + b)/c}, g(n, a, b, c) = sum_{0<=i<=n}{i(ai + b)/c}, h(n, a, b, c) = sum_{0<=i<=n}{((ai + b)/c)^2}, 
  * Qualification : Luogu P5170 【模板】类欧几里得算法 https://www.luogu.com.cn/problem/P5170
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
const int N = 998244353;
const int i2 = (N + 1) / 2, i6 = 166374059;
struct info{
	ll f, g, h;
	info(){f = g = h = 0;}
};
info calc(ll n, ll a, ll b, ll c){
	ll ac = a / c, bc = b / c, m = (a * n + b) / c, n1 = n + 1, n21 = n * 2 + 1;
	info d;
	if(a == 0){
		d.f = bc * n1 % N;
		d.g = bc * n % N * n1 % N * i2 % N;
		d.h = bc * bc % N * n1 % N;
		return d;
	}
	if(a >= c || b >= c){
		d.f = n * n1 % N * i2 % N * ac % N + bc * n1 % N;
		d.g = ac * n % N * n1 % N * n21 % N * i6 % N + bc * n % N * n1 % N * i2 % N;
		d.h = ac * ac % N * n % N * n1 % N * n21 % N * i6 % N + bc * bc % N * n1 % N + ac * bc % N * n % N * n1 % N;

		info e = calc(n, a % c, b % c, c);

		d.h += e.h + 2 * bc * e.f % N + 2 * ac % N * e.g % N;
		d.g += e.g, d.f += e.f;
		d.f %= N, d.g %= N, d.h %= N;
		return d; 
	}
	info e = calc(m - 1, c, c - b - 1, a);
	d.f = (n * m % N - e.f + N) % N;
	d.g = m * n % N * n1 % N - e.h - e.f; d.g = (d.g * i2 % N + N) % N;
	d.h = n * m % N * (m + 1) % N - 2 * e.g - 2 * e.f - d.f; d.h = (d.h % N + N) % N;
	return d;
}

int main(void){
	fastio;
	int t;
	cin>>t;
	while(t--){
		ll n, a, b, c;
		cin >> n >> a >> b >> c;
		info d = calc(n, a, b, c);
		cout<<d.f<<" "<<d.h<<" "<<d.g<<"\n";
	}
}
