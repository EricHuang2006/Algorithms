#include<bits/stdc++.h>
using namespace std;

vector<int> z_array(string s){
	int n = s.length();
	vector<int> z(n, 0);
	int x = 0, y = 0;
	for(int i = 0; i < n; i++){
		z[i] = max(0, min(z[i-x], y-1-i));
		while(i+z[i] < n && s[i+z[i]] == s[z[i]]){
			x = i;
			y = i + z[i];
			z[i]++;
		}
	}
	return z;
}
int main(void){
	
	string s;
	cin>>s;
	string p;
	cin>>p;
	int len = p.length();
	string ss;
	ss = p + '#' + s;
	auto z = z_array(ss);
	int ans = 0;
	for(int i = 1; i < z.size(); i++){
		if(z[i] == len) ans++;
	}
	cout<<ans;
	
	
	
	
}
