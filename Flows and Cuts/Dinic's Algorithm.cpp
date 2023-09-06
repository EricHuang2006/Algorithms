#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Dinic{

    static const int N = 1e5;
    static const int INF = 1e9 + 7;
    struct edge{
        int to, cap, rev;
        edge(){}
        edge(int _to, ll _cap, int _rev) : to(_to), cap(_cap), rev(_rev){}
    };
    vector<edge> g[N];
    void add_edge(int from, int to, int cap){
        g[from].push_back(edge(to, cap, int(g[to].size())));
        g[to].push_back(edge(from, 0, int(g[from].size() - 1)));
    }
    int n, s, t;
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        for(int i = 0; i <= n; i++){
            g[i].clear();
        }
    }
    int level[N], iter[N]; //level[i] = d[i], iter[i] = m[i]

    void bfs(){
        memset(level, -1, sizeof(level));
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int cur = q.front(); q.pop();
            for(auto e : g[cur]){
                if(e.cap > 0 && level[e.to] == -1){
                    level[e.to] = level[cur] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    ll dfs(int now, int flow){
        if(now == t) return flow; // reached termination, return flow
        for(int& i = iter[now]; i < g[now].size(); i++){
            edge &e = g[now][i];
            if(e.cap > 0 && level[e.to] == level[now] + 1){
            //    cout<<now<<" "<<flow<<" "<<e.cap<<endl;
                int ret = dfs(e.to, min(flow, e.cap));
                if(ret > 0){ // successfully found an augmenting path
                    e.cap -= ret;
                    g[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    ll flow(){
        ll ret = 0;
        while(true){
            bfs();
            if(level[t] == -1) break;
            memset(iter, 0, sizeof(iter));
            ll tmp = 0;
            while((tmp = dfs(s, INF)) > 0){
                ret += tmp;
            }
        }
        return ret;
    }
} flow;

int main(){
    int n, m;
    cin>>n>>m;
    flow.init(n, 0, n - 1);
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin>>a>>b>>w;
        a--, b--;
        flow.add_edge(a, b, w);
    }
    cout<<flow.flow();
}
