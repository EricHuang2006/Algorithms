/*   
    Updated : 2024.10.28
    Description : Hungarian algorithm for maximum perfect bipartite matching in O(n^3)
    Verification : Library Checker - Assignment Problem https://judge.yosupo.jp/problem/assignment
*/

struct Hungarian{
    using T = ll;
    vector<T> lx, ly, slack;
    vector<int> vx, vy, match;
    vector<vector<T>> w;
    queue<int> q;
    int n;
    void init(int _n){
        n = _n;
        lx.resize(n), ly.resize(n), slack.resize(n);
        vx.resize(n), vy.resize(n), match.resize(n, -1);
        w.resize(n, vector<T>(n));
    }
    void inp(int x, int y, int val){
        w[x][y] = val;
        lx[x] = max(lx[x], val);
    }
    int dfs(int x){
        if(vx[x]) return false;
        vx[x] = 1;
        for(int i = 0; i < n; i++){
            if(lx[x] + ly[i] == w[x][i] && !vy[i]){
                vy[i] = true;
                if(match[i] == -1 || dfs(match[i])){
                    match[i] = x;
                    return true;
                }
            }

        }
        return false;
    }
    int pdfs(int x){
        fill(vx.begin(), vx.end(), 0);
        fill(vy.begin(), vy.end(), 0);
        return dfs(x);
    }
    void upd(int x){
        for(int i = 0; i < n; i++){
            if(!slack[i]) continue;
            slack[i] = min(slack[i], lx[x] + ly[i] - w[x][i]);
            if(!slack[i] && !vy[i]) q.push(i);
        }
    }
    void relabel(){
        T mn = numeric_limits<T>::max() / 3;
        for(int i = 0; i < n; i++){
            if(!vy[i]) mn = min(mn, slack[i]);
        }
        for(int i = 0; i < n; i++){
            if(vx[i]) lx[i] -= mn;
            if(vy[i]) ly[i] += mn;
            else{
                slack[i] -= mn;
                if(!slack[i]) q.push(i);
            }
        }
    }
    auto solve(){
        for(int i = 0; i < n; i++){
            if(pdfs(i)) continue;
            while(!q.empty()) q.pop();
            fill(slack.begin(), slack.end(), INF);
            for(int j = 0; j < n; j++) if(vx[j]) upd(j);
            int ok = 0;
            while(!ok){
                relabel();
                while(!q.empty()){
                    int j = q.front(); q.pop();
                    if(match[j] == -1){
                        pdfs(i);
                        ok = 1;
                        break;
                    }
                    vy[j] = vx[match[j]] = 1, upd(match[j]);
                }
            }
        }
        T ans = 0;
        for(int i = 0; i < n; i++){
            ans += w[match[i]][i];
        }
        for(int i = 0; i < n; i++) lx[match[i]] = i;
        return make_pair(ans, lx);
    }
} h;
