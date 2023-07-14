/*
	* Date: 2023/07/14
 	* Suffix Automaton
  	* Description: all paths in the suffix automaton from starting point corresponds to a substring of the original string
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
const int maxn = 2e5 + 5;

struct SuffixAutomaton{
	int len[maxn], link[maxn]; // maxn >= 2 * n - 1
	ll cnt[maxn]; // size of endpos in a endpos-equivalent class
	map<char, int> nxt[maxn];
	int sz = 1, last = 0;
	void init(string s){
		link[0] = -1;
		for(auto x : s) sa_extend(x);
	}
	void sa_extend(char c){
		int cur = sz++;
		len[cur] = len[last] + 1;
		int p = last;
		while(p != -1 && !nxt[p].count(c)){
			nxt[p][c] = cur;
			p = link[p];
		}
		if(p == -1) link[cur] = 0;
		else{
			int q = nxt[p][c];
			if(len[q] == len[p] + 1) link[cur] = q;
			else{
				int clone = sz++;
				len[clone] = len[p] + 1;
				nxt[clone] = nxt[q];
				link[clone] = link[q];
				while(p != -1 && nxt[p][c] == q) {
					nxt[p][c] = clone;
					p = link[p];
				}
				link[cur] = link[q] = clone;
			}
		}
		last = cur;
	}
	ll getDistinct(int pos){ // number of distinct substrings starting at pos, including an empty string
		if(distinct[pos]) return distinct[pos];
		distinct[pos] = 1;
		for(auto [c, next] : nxt[pos]) distinct[pos] += getDistinct(next);
		return cnt[pos];
	}
	ll numDistinct(){
		return getDistinct(0) - 1; // excluding an empty string
	}
	ll numDistinct2(){
		ll tot = 0;
		for(int i = 1; i < sz; i++) tot += len[i] - len[link[i]];
		return tot;
	}
	string distinct_kth(ll k){
		numDistinct();
		string s;
		ll cur = 0, tally = 0;
		while(tally < k){
			for(auto [c, next] : nxt[cur]){
				if(tally + distinct[next] >= k){
					tally += 1;
					s += c;
					cur = next;
					break;
				}
				tally += distinct[next];
			}
		}
		return s;
	}
};
SuffixAutomaton automata;

void solve(){
	string s;
	cin>>s;
	ll k;
	cin>>k;
	automata.init(s);
	cout<<automata.qry_kth(k)<<"\n";
}
int main(void){
	fastio;
	int t = 1;
	// cin>>t;
	while(t--){
		solve();
	}
}
