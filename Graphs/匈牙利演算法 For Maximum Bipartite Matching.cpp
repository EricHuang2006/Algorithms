//TIOJ 2197. E. 密室逃脫 https://tioj.ck.tp.edu.tw/problems/2197
#include<bits/stdc++.h>
using namespace std;
const int maxn = 600;
typedef long long ll;
typedef pair<ll, ll> pll;
ll lx[600], ly[600], vx[600], vy[600], match[600];
int n;
vector<vector<ll>> w;

int dfs(int x){
    //cout<<"dfs : "<<x<<endl;
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

void relabel(){
    int mn = 1e9;
    for(int i = 0; i < n; i++){
        if(!vx[i]) continue;
        for(int j = 0; j < n; j++){
            if(vy[j]) continue;
            int val = lx[i] + ly[j] - w[i][j];
            mn = min(mn, val);
        }
    }
    for(int i = 0; i < n; i++) if(vx[i]) lx[i] -= mn;
    for(int i = 0; i < n; i++) if(vy[i]) ly[i] += mn;
}

void hungarian(){
    for(int i = 0; i < n; i++){
        while(true){
            fill(vx, vx + n, 0);
            fill(vy, vy + n, 0);
            if(dfs(i)) break;
            relabel();
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += w[match[i]][i];
    }
    cout<<ans<<endl;
    for(int i = 0; i < n; i++) cout<<lx[i]<<" ";
    cout<<endl;
    for(int i = 0; i < n; i++) cout<<ly[i]<<" ";
}

int main(void){
    cin>>n;
    w.resize(n, vector<ll>(n));
    fill(match, match + n, -1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin>>w[i][j];
            lx[i] = max(lx[i], w[i][j]);
        }
    }
    hungarian();
}
