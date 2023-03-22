//see: https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html#kuhns-algorithm
//Kuhn's algorithm is a subroutine in the Hungarian algorithm, also known as the Kuhn-Munkres algorithm.
#include<bits/stdc++.h>
using namespace std;
int n, k; // n = number of vertices in the first part, k = number of vertices in the second part
vector<vector<int>> adj;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int v){
	if(used[v]) return false;
	used[v] = true;
	for(auto x : adj[v]){
		if(mt[x] == -1 || try_kuhn(mt[x])){
			mt[x] = v;
			return true;
		}
	}
	return false;
}
int main(void){
	cin>>n;
	
	mt.assign(k, -1);
	vector<bool> used1(n, false);
	for(int i = 0; i <n; i++){
		for(auto x : adj[i]){
			if(mt[x] == -1){
				mt[x] = i;
				used[i] = true;
				break;
			}
		}
	}
	for(int i = 0; i < n; i++){
		if(used1[i]) continue;
		used.assign(n, false);
		try_kuhn(i);
	}
	
	for(int i = 0; i < k; i++){
		if(mt[i] != -1){
			cout<<mt[i] + 1<<" "<<i + 1<<endl;
		}
	}
}
