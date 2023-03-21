#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
typedef long long ll;
 
string s;
int sa[maxn], tmp[2][maxn], c[maxn];
 
void GetSA(){
    int *x = tmp[0], *y = tmp[1], m = 500, n = s.size();
    for(int i = 0; i < m; i++) c[i] = 0;
    for(int i = 0; i < n; i++) c[x[i] = s[i]] ++;
    for(int i = 1; i < m; i++) c[i] += c[i - 1];
    for(int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
    for(int k = 1; k < n; k <<= 1){
        for(int i = 0; i < m; i++) c[i] = 0;
        for(int i = 0; i < n; i++) c[x[i]] ++;
        for(int i = 1; i < m; i++) c[i] += c[i - 1]; // construct count array for the first cardinality
        int p = 0;
        for(int i = n - k; i < n; i++) y[p++] = i; // the second index of the suffix is out of bounds ( >= n), therefore we view them as the smallest elements
        for(int i = 0; i < n; i++){
            if(sa[i] >= k) y[p++] = sa[i] - k; // if sa[i] < k, it does not need to be considered since it won't be the second part of the suffix we are constructing here
        }//in line 19 ~ 21 we have constructed a ranking array y based on the second cardinality of substrings of length k
        for(int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
        y[sa[0]] = p = 0;
        for(int i = 1; i < n; i++){
            int a = sa[i], b = sa[i - 1];
            if(x[a] == x[b] && a + k < n && b + k < n && x[a + k] == x[b + k]);
            else p++;
            y[sa[i]] = p;
        }
        if(n == p + 1) break;
        swap(x, y);
        m = p + 1;
    }
}
int rk[maxn], lcp[maxn];
void GetLCP(){
    int n = s.size(), val = 0;
    for(int i = 0; i < n; i++) rk[sa[i]] = i;
    for(int i = 0; i < n; i++){
        if(rk[i] == 0) lcp[rk[i]] = 0;
        else{
            if(val) val--;
            int p = sa[rk[i] - 1];
            while(val + i < n && val + p < n && s[val + i] == s[val + p]) val++;
            lcp[rk[i]] = val;
        }
    }
}
 
void print(){
    int n = s.length();
    for(int i = 0; i < n; i++){
        cout<<lcp[i]<<" ";
        for(int j = sa[i]; j < n; j++) cout<<s[j];
        cout<<endl;
    }
}
 
int main(){
	int n;
	cin>>n;
    cin>>s;
    GetSA();
    GetLCP();
    //print();
    //ll n = s.length();
    //for(int i = 0; i < n; i++) cout<<sa[i]<<endl;
    cout<<*max_element(lcp, lcp + s.size());
}
