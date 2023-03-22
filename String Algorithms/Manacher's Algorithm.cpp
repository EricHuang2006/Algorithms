#include<bits/stdc++.h>
using namespace std;
 
int main(void){
    string s, ss;
    cin>>ss;
    s.resize(2 * ss.size() + 1, '#');
    for(int i = 0; i < ss.size();i++) s[i + i + 1] = ss[i];
    //Manacher's Algorithm
    vector<int> p(s.size(), 1);
    int l = 0, r = 0;
    for(int i = 0; i < s.size(); i++){
        p[i] = max(min(p[l + l - i], r - i), 1);
        while(i - p[i] >= 0 && i + p[i] < s.size() && s[i - p[i]] == s[i + p[i]]){
            l = i, r = i + p[i], p[i]++;
        }
    }
    int idx = max_element(p.begin(), p.end()) - p.begin();
    int len = p[idx] * 2 - 1;;
    idx = idx - p[idx] + 1;
    for(int i = 0; i < len; i++, idx++){
        if(s[idx] != '#') cout<<s[idx];
    }
}
