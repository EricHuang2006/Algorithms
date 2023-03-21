#include<bits/stdc++.h>
using namespace std;
 
 
struct state{
    int len, link, cnt;
    map<char, int> next; // transitions
};
 
const int maxn = 1e5 + 5;
state st[maxn * 2];
int sz, last;
 
void sa_init(){
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}
 
void sa_extend(char c){
    int cur = sz++;
    st[cur].cnt = 1;
    st[cur].len = st[last].len + 1;
    int p = last;
    while(p != -1 && !st[p].next.count(c)){
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if(p == -1){
        st[cur].link = 0;
    }
    else{
        int q = st[p].next[c];
        if(st[p].len + 1 == st[q].len){
            st[cur].link = q;
        }
        else{
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while(p != -1 && st[p].next[c] == q){
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
 
void sa_updcnt(){
    vector<int> states_by_len[sz];
    for(int i = 0; i < sz; i++) states_by_len[st[i].len].push_back(i);
    for(int i = sz - 1; i >= 0; i--){
        for(auto u : states_by_len[i]){
            if(st[u].link != -1) st[st[u].link].cnt += st[u].cnt;
        }
    }
}
 
int sa_qry(string s){
    int now = 0;
    for(int i = 0; i < s.size(); i++){
        if(!st[now].next.count(s[i])) return 0;
        now = st[now].next[s[i]];
    }
    return st[now].cnt;
}
int main(void){
 
    string s;
    cin>>s;
    int t;
    cin>>t;
    sa_init();
    for(int i = 0; i < s.size(); i++) sa_extend(s[i]);
    sa_updcnt();
    while(t--){
        string temp;
        cin>>temp;
        cout<<sa_qry(temp)<<endl;
    }
}
