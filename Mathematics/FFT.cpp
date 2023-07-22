/*
	* FFT
 	* Date: 2023/07/22
  	* Description: multiply two polynomials in O(nlogn)
*/
#include<bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert = 0){
	int n = a.size();
	if(n == 1) return;
	vector<cd> a0(n / 2), a1(n / 2);
	for(int i = 0; 2 * i < n; i++){ //分離係數
		a0[i] = a[2 * i];
		a1[i] = a[2 * i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);
	double ang = 2 * PI / n * (invert ? -1 : 1);
	cd w(1), wn(cos(ang), sin(ang));
	for(int i = 0; 2 * i < n; i++){
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if(invert){
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}
		w *= wn;
	} 
}

void fft(vector<cd> &a, bool invert = 0){ // interative version
	int n = a.size();
	int lg_n = __lg(n);
	for(int i = 1, j = 0; i < n; i++){ //fbit-reversal permutation
		int bit = n >> 1;
		for(; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if(i < j) swap(a[i], a[j]);
	}
	for(int len = 2; len <= n; len <<= 1){
		double ang = 2 * PI / len * (invert? -1 : 1);
		cd wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len){
			cd w(1);
			for(int j = 0; j < len / 2; j++){
				cd u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if(invert) for(auto &x : a) x /= n;
}

vector<int> multiply(vector<int> const& a, vector<int> const& b){
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
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
	vector<int> result(n);
	for(int i = 0; i < n; i++){
		result[i] = round(fa[i].real());
	}
	return result;
}
int main(){
	int n, m;
	cin>>n>>m;
	vector<int> a(n), b(m);
	for(int i = 0; i < n; i++) cin>>a[i];
	for(int i = 0; i < m; i++) cin>>b[i];
	auto v = multiply(a, b);
	for(auto x : v) cout<<x<<" ";
	cout<<"\n";
}
