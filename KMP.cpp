#include<bits/stdc++.h>
using namespace std;

vector<int> f;
int pos;

void getfail(string s){
	int n = s.length();
	f.resize(n + 1);
	f[0] = pos = -1;
	for(int i = 1; i < n; i++){	
		while(pos != -1 && s[pos + 1] != s[i]) pos = f[pos];
		if(s[pos + 1] == s[i]) pos++;
		f[i] = pos;
	}
}

void find(string s, string t){
	int n = s.length();
	getfail(t);
	int now = -1, ans = 0;
	for(int i = 0; i < n; i++){
	 	while(now != -1 && s[i] != t[now + 1]) now = f[now];
	 	if(s[i] == t[now + 1]) now++;
	 	if(now + 1 == t.length()){
			ans++;
			now = f[now];
		}
	}
	cout<<ans;
}

int main(void){
	
	string s, t;
	cin>>s>>t;
	find(s, t);
}
