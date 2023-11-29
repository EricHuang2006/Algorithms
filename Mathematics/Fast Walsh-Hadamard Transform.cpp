/*
  Date : 2023.11.29
  Description : perform Xor convolution in O(nlogn)
*/

void fwt(vector<int> &a){
	int n = 1;
	while(n < a.size()) n *= 2;
	a.resize(n);
	for(int len = 1; 2 * len <= n; len <<= 1){
		for(int i = 0; i < n; i += 2 * len){
			for(int j = 0; j < len; j++){
				int u = a[i + j], v = a[i + j + len];
				a[i + j] = (u + v) % mod, a[i + j + len] = (u - v) % mod;
			}
		}
	}
}
