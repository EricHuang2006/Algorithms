#include<bits/stdc++.h>
using namespace std;
//Duval Algorithm : divide the string s into three strings s = s1s2s3, s1 has been processed, s2 is pre-simple, and s3 has not been touched
vector<string> duval(string const &s){
	int n = s.length();
	int i = 0;
	while(i < n){
		int j = i + 1, k = i; // i = the beginning of s2, j = the beginning of s3, k = the current character that we are comparing to ( i <= k < j )
		while(j < n && s[k] <= s[j]){
			if(s[k] < s[j]) k = i;
			else k++;
			j++;
		}
		while(i <= k){
			factorization.push_back(s.substr(i, j - k)); //abcabca|a	abcabc|ccb		b|b|b|b|a
			i += j - k;
		}
	}
	return factorization;
}
int main(void){
		
}
