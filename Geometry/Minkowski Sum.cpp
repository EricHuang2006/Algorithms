/*
  Created : 2024.8.17
  Description : Compute the sum of two convex hulls
  Can be used to compute the minimum distance between two convex hulls in O(|P| + |Q|)
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
// #pragma GCC optimize("Ofast")
#define pb push_back
#define eb emplace_back
#define f first
#define s second
const int maxn = 500 + 5;
const int INF = 4e18;

struct pt{
    int x, y;
    pt(){}
    pt(int _x, int _y) : x(_x), y(_y){}
};
pt operator + (pt a, pt b){ return pt(a.x + b.x, a.y + b.y);}
pt operator - (pt a, pt b){ return pt(a.x - b.x, a.y - b.y);}

int cross(pt a, pt b){
    return a.x * b.y - a.y * b.x;
}
int dot(pt a, pt b){
    return a.x * b.x + a.y * b.y;
}

void reorder(vector<pt> &a){
    int pos = 0;
    for(int j = 1; j < a.size(); j++){
        if(a[j].x < a[pos].x || (a[j].x == a[pos].x && a[j].y < a[pos].y)) pos = j;
    }
    rotate(a.begin(), a.begin() + pos, a.end());
}

vector<pt> minkowski(vector<pt> a, vector<pt> b){
    // for(int i = 0; i < b.size(); i++) b[i] = {-b[i].x, -b[i].y}; 最短距離：把 Q 鏡像，找凸包到 (0, 0) 的最短距離
    reorder(a), reorder(b);
    a.pb(a[0]), a.pb(a[1]);
    b.pb(b[0]), b.pb(b[1]);
    vector<pt> res;
    int i = 0, j = 0;
    while(i < a.size() - 2 || j < b.size() - 2){
        res.pb(a[i] + b[j]);
        int c = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
        if(c >= 0 && i < a.size() - 2) i++;
        if(c <= 0 && j < b.size() - 2) j++;
    }
    return res;
}
