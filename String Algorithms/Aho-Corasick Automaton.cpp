/*
	* Aho-Corasick Automaton
	* Date: 2023/07/13
	* Description: essentially doing KMP on a Trie
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<pll, ll> tll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#pragma optimize GCC("Ofast")
#define pb push_back
#define eb emplace_back
#define f first
#define s second
const int maxn = 5e5 + 5;
//AC Automaton
namespace AC{
 
	int ch[maxn][26], fail[maxn], idx[maxn], last[maxn], pt[maxn];
	int val[maxn], cnt[maxn], tot = 0; // val[id] = number of times node id is visited, cnt[i] = 字串 i 出現的次數
 
	void init(){
		memset(ch, 0, sizeof(ch));
		memset(fail, 0, sizeof(fail));
		memset(idx, 0, sizeof(idx));
		memset(last, 0, sizeof(last));
		memset(val, 0, sizeof(val));
		memset(cnt, 0, sizeof(cnt));
		tot = 0;
	}
	void insert(string &s, int id){ // id is 1-based
		int cur = 0;
		for(int i = 0; i < s.size(); i++){
			if(!ch[cur][s[i] - 'a']) ch[cur][s[i] - 'a'] = ++tot;
			cur = ch[cur][s[i] - 'a'];
		}
		if(idx[cur] == 0) idx[cur] = id;
		else pt[id] = idx[cur];
	}
	void build(){
		queue<int> q;
		for(int i = 0; i < 26; i++){
			if(ch[0][i]) q.push(ch[0][i]);
		}
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int i = 0; i < 26; i++){
				if(ch[u][i]) {
					fail[ch[u][i]] = ch[fail[u]][i];
					q.push(ch[u][i]);
				}
				else ch[u][i] = ch[fail[u]][i];
				last[ch[u][i]] = idx[fail[ch[u][i]]] ? fail[ch[u][i]] : last[fail[ch[u][i]]];
			}
		}
	}
 
	int qry(string &s){ // return number of maximum number of occurences of a string in s
		int u = 0, ret = 0;
		for(int i = 0; i < s.size(); i++){
			u = ch[u][s[i] - 'a'];
			for(int j = u; j; j = last[j]) val[j] ++;
		}
		for(int i = 0; i <= tot; i++){
			if(idx[i]) ret = max(ret, val[i]), cnt[idx[i]] = val[i];
		}
		return ret;
	}
};
 
void solve(){
	string t;
	cin>>t;
	int n;
	cin>>n;
	vector<string> s(n);
	AC::init();
	for(int i = 0; i < n; i++){
		cin>>s[i];
		AC::insert(s[i], i + 1);
	}
	AC::build();
	AC::qry(t);
	for(int i = 0; i < n; i++){
		if(AC::pt[i + 1] == 0) cout<<AC::cnt[i + 1]<<"\n";
		else cout<<AC::cnt[AC::pt[i + 1]]<<"\n";
	}
}
int main(void){
	fastio;
	int t = 1;
	// cin>>t;
	while(t--){
		solve();
	}
}
