#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6;
const int maxw = 26;
map<int, vector<int>> mp;
int ans[maxn];
namespace AC{

	int ch[maxn][maxw], fail[maxn], leaf[maxn], last[maxn], pos = 0;
	
	void insert(string s, int idx){
		int now = 0;
		for(auto c : s){
			if(!ch[now][c - 'a']) ch[now][c - 'a'] = ++pos;
			now = ch[now][c - 'a'];
		}
		leaf[now] ++;
		mp[now].push_back(idx);
	}	
	
	void build(){
		queue<int> q;
		for(int i = 0; i < 26; i++){
			if(ch[0][i]) q.push(ch[0][i]);
		}
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int i = 0; i < 26; i++){
				if(ch[u][i]){
					fail[ch[u][i]] = ch[fail[u]][i];
					q.push(ch[u][i]);
				}
				else{
					ch[u][i] = ch[fail[u]][i];
				}
				last[ch[u][i]] = leaf[fail[ch[u][i]]] ? fail[ch[u][i]] : last[fail[ch[u][i]]];
			}
		}
	}
	void add(int idx){
		if(idx){
			if(ans[mp[idx][0]] != 0) return;
			for(auto x : mp[idx])
				ans[x] = 1;
			add(last[idx]);
		}
	}
	void qry(string s){
		int now = 0;
		for(int i = 0; i < s.length(); i++){
			while(now && ch[now][s[i] - 'a'] == 0) now = fail[now];
			if(ch[now][s[i] - 'a']){
				now = ch[now][s[i] - 'a'];
			}
			if(leaf[now] > 0){
				add(now);
			}
			else if(last[now] > 0){
				add(last[now]);
			}
		}
	}
};


int main(void){
	
	string key;
	cin>>key;
	int n;
	cin>>n;
	vector<string> s(n);
	for(int i = 0; i < n; i++){
		cin>>s[i];
		AC::insert(s[i], i);
	}
	AC::build();
	AC::qry(key);
	for(int i = 0; i < n; i++){
		cout<<(ans[i] ? "YES" : "NO")<<endl;
	}
	
	
}
