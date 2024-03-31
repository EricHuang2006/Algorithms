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
	int cnt[maxn], distinct[maxn];
	bool is_clone[maxn];
   	int first_pos[maxn];
   	vector<int> inv_link[maxn]; //suffix references
	map<char, int> nxt[maxn];
	int sz = 1, last = 0;
	void init(string s){
		link[0] = -1;
		for(auto x : s) sa_extend(x);
	}
	void sa_extend(char c){
		int cur = sz++;
		len[cur] = len[last] + 1;
		firstpos[cur] = len[cur] - 1;
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
				is_clone[clone] = true;
				firstpos[clone] = q;
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
	//Applications
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
	//inverse links
	void genLink(){
	    for(int i = 1; i < sz; i++){
	       st[st[v].link].inv.pb(v);
	    }
	}
	
	void get_all_occur(vector<int>& oc, int v){
	    if(!st[v].is_clone) oc.pb(st[v].first_pos);
	    for(auto u : st[v].inv_link) get_all_occur(oc, u);
	}
	vector<int> all_occ(string s){ // get all occurrences of s in automaton
	    int cur = 0;
	    for(auto x : s){
	        if(!st[cur].next.count(x)) return {};
	        cur = st[cur].next[x];
	    }
	    vector<int> oc;
	    get_all_occur(oc, cur);
	    for(auto &x : oc) x += 1 - s.length(); //translate to starting positions
	    sort(oc.begin(), oc.end());
	    return oc;
	}
	int lcs(string t){
		int v = 0, l = 0, ans = 0;
		for(auto x : t){
			while(v && !nxt[v].count(x)){
				v = link[v];
				l = len[v];
			}
			if(nxt[v].count(x)){
				v = nxt[v][x];
				l++;
			}
			ans = max(ans, l);
		}
		return ans;
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
