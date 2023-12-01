/*
  * Date : 2023.12.1
  * Persistent Treap
  * Verification : P5055 【模板】可持久化文艺平衡树 (https://www.luogu.com.cn/problem/P5055) (still MLE on one case ...)
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define REP1(i, n) FOR(i, 0, n + 1)
#define SZ(x) (int)(x).size()
#define pb push_back
#define pf push_front
#define eb emplace_back
#define f first
#define s second
#define lowbit(x) x&-x
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
// #define int long long 
#define ls ch[x][0]
#define rs ch[x][1]
const int INF = 1e9 + 7;
const int maxn = 2e5 + 5;
int cnt = 0;

struct node{
    int val, sz, pri, rev = 0;
    int l, r;
    ll sum;
} t[maxn * 165];
int rt[maxn];
void clear(int v){
    t[v].val = t[v].sum = t[v].sz = t[v].rev = t[v].l = t[v].r = 0;
}
int newnode(int x){
    int cur = ++cnt;
    t[cur].val = t[cur].sum = x;
    t[cur].sz = 1, t[cur].pri = rand();
    return cur;
}
int clone(int v){
    int cur = ++cnt;
    t[cur].val = t[v].val, t[cur].sum = t[v].sum, t[cur].sz = t[v].sz, t[cur].pri = rand(), 
    t[cur].rev = t[v].rev, t[cur].l = t[v].l, t[cur].r = t[v].r;
    return cur;
}
void pull(int v){
    t[v].sum = t[v].val + t[t[v].l].sum + t[t[v].r].sum;
    t[v].sz = 1 + t[t[v].l].sz + t[t[v].r].sz;
}
void push(int v){
    if(!v) return;
    if(t[v].rev){
        if(t[v].l) t[v].l = clone(t[v].l), swap(t[t[v].l].l, t[t[v].l].r), t[t[v].l].rev ^= 1;
        if(t[v].r) t[v].r = clone(t[v].r), swap(t[t[v].r].l, t[t[v].r].r), t[t[v].r].rev ^= 1;
        t[v].rev = 0;
    }
}
pair<int, int> split(int org, int k){
    if(!org) return make_pair(0, 0);
    push(org);
    int nd = clone(org);
    if(t[t[nd].l].sz < k){
        auto p = split(t[nd].r, k - t[t[nd].l].sz - 1);
        t[nd].r = p.first;
        pull(nd);
        return make_pair(nd, p.second);
    }
    else{
        auto p = split(t[nd].l, k);
        t[nd].l = p.second;
        pull(nd);
        return make_pair(p.first, nd);
    }
}
int merge(int a, int b){
    if(!a && !b) return 0;
    if(!a || !b) return a ? a : b;
    push(a), push(b);
    int nd;
    if(t[a].pri > t[b].pri){
        nd = clone(a);
        t[nd].r = merge(t[a].r, b);
    }
    else{
        nd = clone(b);
        t[nd].l = merge(a, t[b].l);
    }
    pull(nd);
    return nd;
}

ll lst = 0;
signed main(void){
    fastio;
    int n;
    cin>>n;
    int v, op;
    ll p, x, l, r;
    for(int i = 1; i <= n; i++){
        int v, op;
        cin>>v>>op;
        if(op == 1){
            cin>>p>>x;
            p ^= lst, x ^= lst;
            auto [a, b] = split(rt[v], p);
            // cout<<"mid : ", print(a), cout<<" / ", print(b), cout<<"\n";
            // cout<<"mid : "<<a<<" "<<b<<"\n";
            rt[i] = merge(merge(a, newnode(x)), b);
        }
        else if(op == 2){
            cin>>p;
            p ^= lst;
            auto [a, b] = split(rt[v], p - 1);
            auto [c, d] = split(b, 1);
            rt[i] = merge(a, d);
        }
        else if(op == 3){
            cin>>l>>r;
            l ^= lst, r ^= lst;
            auto [a, b] = split(rt[v], l - 1);
            auto [c, d] = split(b, r - l + 1);
            swap(t[c].l, t[c].r), t[c].rev ^= 1;
            rt[i] = merge(merge(a, c), d);
        }
        else{
            cin>>l>>r;
            l ^= lst, r ^= lst;
            rt[i] = rt[v];
            auto [a, b] = split(rt[v], l - 1);
            auto [c, d] = split(b, r - l + 1);
            cout<<t[c].sum<<"\n";
            lst = t[c].sum;
        }
    }
}
