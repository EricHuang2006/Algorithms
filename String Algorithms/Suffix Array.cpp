#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
typedef long long ll;

//O(nlogn) construction of Suffix Array
struct SuffixArray{
	string s;
	int sa[maxn], tmp[2][maxn], c[maxn];
	void init(string _s){s = _s; GetSA(); GetLCP();}
	void GetSA(){
		int *x = tmp[0], *y = tmp[1], m = 256, n = s.size();
		for(int i = 0; i < m; i++) c[i] = 0;
		for(int i = 0; i < n; i++) c[x[i] = s[i]] ++;
		for(int i = 1; i < m; i++) c[i] += c[i - 1];
		for(int i = 0; i < n; i++) sa[--c[x[i]]] = i;
		for(int k = 1; k < n; k <<= 1){
			for(int i = 0; i < m; i++) c[i] = 0;
			for(int i = 0; i < n; i++) c[x[i]] ++;
			for(int i = 1; i < m; i++) c[i] += c[i - 1];
			int p = 0;
			for(int i = n - k; i < n; i++) y[p++] = i;
			for(int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
			for(int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
			//update equivalent classes
			y[sa[0]] = p = 0;
			for(int i = 1; i < n; i++){
				int a = sa[i], b = sa[i - 1];
				if(x[a] == x[b] && a + k < n && b + k < n && x[a + k] == x[b + k]);
				else p++;
				y[sa[i]] = p;
			}
			if(p + 1 == n) break;
			swap(x, y);
			m = p + 1;
		}
	}
	int rk[maxn], lcp[maxn];
	void GetLCP(){ // Kasai's Algo 
		int n = s.size(), val = 0;
		for(int i = 0; i < n; i++) rk[sa[i]] = i;
		for(int i = 0; i < n; i++){ // compute by ascending length of suffixes
			if(rk[i] == 0) val = 0;
			else{
				if(val) val--;
				int p = sa[rk[i] - 1]; // lcp[i] = lcp(sa[i], sa[i - 1])=> lcp[0] = 0
				while(i + val < n && p + val < n && s[i + val] == s[p + val]) val++;
				lcp[rk[i]] = val;
			}
		}
	}
};
SuffixArray SA;
int main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
    	SA.init(s);
	for(int i = 0; i < n; i++) cout<<SA.sa[i]<<" ";
	cout<<"\n";
}
