/*   
    Updated : 2024.10.28
    Description : Hungarian algorithm for maximum perfect bipartite matching in O(n^3)
    Verification : Library Checker - Assignment Problem https://judge.yosupo.jp/problem/assignment
*/

int l, r, m;
int mx[maxn], my[maxn], dx[maxn], dy[maxn], vis[maxn];
vector<int> adj[maxn];
int n, lim;

int dfs(int pos){
    for(auto x : adj[pos]){
        if(!vis[x] && dy[x] == dx[pos] + 1){
            vis[x] = 1;
            if(my[x] != -1 && dy[x] == lim) continue;
            if(my[x] == -1 || dfs(my[x])){
                my[x] = pos, mx[pos] = x;
                return true;
            }
        }
    }
    return false;
}

int bfs(){
    fill(dx, dx + l, -1);
    fill(dy, dy + r, -1);
    queue<int> q;
    for(int i = 0; i < l; i++){
        if(mx[i] == -1) dx[i] = 0, q.push(i);
    }
    lim = INF;
    while(!q.empty()){
        int pos = q.front(); q.pop();
        if(dx[pos] > lim) break;
        for(auto x : adj[pos]){
            if(dy[x] == -1){
                dy[x] = dx[pos] + 1;
                if(my[x] == -1) lim = dy[x];
                else dx[my[x]] = dy[x] + 1, q.push(my[x]);
            }
        }
    }
    return lim != INF;
}

void Hopcroft_Karp(){
    int res = 0;
    while(bfs()){
        fill(vis, vis + l + r, 0);
        for(int i = 0; i < l; i++){
            if(mx[i] == -1 && dfs(i)) res++;
        }
    }
    cout<<res<<"\n";
    for(int i = 0; i < l; i++){
        if(mx[i] != -1) cout<<i<<" "<<mx[i]<<"\n";
    }
}
