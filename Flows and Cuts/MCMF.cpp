/*
  * Created : 2023/09/10 
  * Min-Cost-Max-Flow
  * Description : uses SPFA to replace bfs in Dinic's algorithm to find the minimum cost path
  *               Since there are negative weight (cost) edges, we can't use dijkstra
  * Requirements : no negative cycle
  * Time Complexity : O(VEf) worst case, O(kEf) on random graph (k is the constant for running spfa)
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
#define pf push_front
#define eb emplace_back
const int INF = 2e9 + 7;

struct MCMF{
    using T = int;
    struct edge{
        int to;
        T cap, cost;
        edge(){}
        edge(int _to, T _cap, T _cost) : to(_to), cap(_cap), cost(_cost){}
    };
    vector<edge> e;
    vector<vector<int>> adj;
    vector<int> iter, inq;
    vector<T> dist;
    int n, s, t;
    void init(int _n, int _s, int _t){
        n = _n, s = _s, t = _t;
        adj = vector<vector<int>>(n);
        iter = vector<int>(n);
        dist = vector<T>(n);
        inq = vector<int>(n);
        e.clear();
    }
    void add_edge(int from, int to, T cap, T cost = 0){
        adj[from].pb(e.size()), adj[to].pb(e.size() + 1);
        e.pb(edge(to, cap, cost)), e.pb(edge(from, 0, -cost));
    }
    bool spfa(){
        fill(dist.begin(), dist.end(), INF);
        queue<int> q;
        q.push(s);
        dist[s] = 0, inq[s] = 1;
        while(!q.empty()){
            int pos = q.front(); q.pop();
            inq[pos] = 0;
            for(auto id : adj[pos]){
                auto [to, cap, cost] = e[id];
                if(cap && dist[to] > dist[pos] + cost){
                    dist[to] = dist[pos] + cost;
                    if(!inq[to]) q.push(to), inq[to] = 1;
                }
            }
        }
        return dist[t] != INF;
    }
    T dfs(int pos, T flow){
        if(pos == t) return flow;
        inq[pos] = 1;
        for(int &i = iter[pos]; i < adj[pos].size(); i++){
            auto [to, cap, cost] = e[adj[pos][i]];
            if(!inq[to] && dist[to] == dist[pos] + cost && cap){
                T tmp = dfs(to, min(flow, cap));
                if(tmp){
                    inq[pos] = 0;
                    e[adj[pos][i]].cap -= tmp;
                    e[adj[pos][i] ^ 1].cap += tmp;
                    return tmp; 
                }
            }
        }
        inq[pos] = 0;
        return 0;
    }
    pair<T, T> mcmf(){
        T flow = 0, cost = 0;
        while(true){
            if(!spfa()) break;
            fill(iter.begin(), iter.end(), 0);
            T tmp;
            while((tmp = dfs(s, INF)) > 0){
                flow += tmp, cost += tmp * dist[t];
            }
        }
        return {flow, cost};
    }
} flow;


int main(void){
    fastio;
  
}
