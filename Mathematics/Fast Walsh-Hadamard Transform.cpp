/*
  Date : 2023.11.29
  Description : perform subset convolution (and, or, xor) in O(nlogn)
*/

void fwt(vector<int> &a, bool inv){
	int n = 1;
	while(n < a.size()) n *= 2;
	a.resize(n);
	for(int len = 1; 2 * len <= n; len <<= 1){
		for(int i = 0; i < n; i += 2 * len){
			for(int j = 0; j < len; j++){
				int &u = a[i + j], &v = a[i + j + len]; tie(u, v) = 
				// inv ? pll(u - v, v) : pll(u + v, v); // and
				// inv ? pll(u, v - u) : pll(u, u + v); // or
				pll(u + v, u - v); // xor
			}
		}
	}
	if(inv) for(auto &x : a) x /= n; // xor only
}
