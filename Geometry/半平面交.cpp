/*
  Created : 2024.9.5
  Description : Half-plane Intersection
  Verification : [P4196 [CQOI2006] 凸多边形 /【模板】半平面交](https://www.luogu.com.cn/problem/P4196)
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
#define int long long
#define lowbit(x) x&-x
#define hp half_plane
const int maxn = 2e5 + 5;
const double INF = 1e10;
const double eps = 1e-9;

struct pt{
	double x, y;
	pt(){}
	pt(double _x, double _y) : x(_x), y(_y){}
};
pt operator + (pt a, pt b){ return pt(a.x + b.x, a.y + b.y);}
pt operator - (pt a, pt b){ return pt(a.x - b.x, a.y - b.y);}
pt operator / (pt a, double k){ return pt(a.x / k, a.y / k);}
pt operator * (pt a, double k){ return pt(a.x * k, a.y * k);}

struct half_plane{
	pt a, vec;
	double deg;
	half_plane(){}
	half_plane(pt _a, pt _vec) : a(_a), vec(_vec){
        deg = atan2(vec.x, vec.y);
    }  
	bool operator < (half_plane& other) const{
		return deg < other.deg;
	}
};

double cross(pt a, pt b){
	return a.x * b.y - a.y * b.x;
}

bool same_side(half_plane p, pt b){
	return cross(p.vec, b - p.a) > 0;
}
pt a[maxn];

hp t[maxn];
pt s[maxn];
int l, r;

pt its(hp a, hp b){
	double c = (a.a.x - b.a.x) * b.vec.y - (a.a.y - b.a.y) * b.vec.x;
	c /= (a.vec.y * b.vec.x - a.vec.x * b.vec.y);
	return a.a + a.vec * c;
}

void half_plane_intersection(vector<hp> p){
	l = r = 0;
	for(int i = 0; i < p.size(); i++){
		while(r - l > 1 && !same_side(p[i], s[r - 2])){
			r--;
		}
		while(r - l > 1 && !same_side(p[i], s[l])) l++;
		t[r++] = p[i];
		if(r - l > 1) s[r - 2] = its(t[r - 1], t[r - 2]);
	}
	while(r - l > 1 && !same_side(t[l], s[r - 2])) r--;
	s[r - 1] = its(t[l], t[r - 1]);
}

signed main(){
    fastio;
    int n;
    cin>>n;
    vector<hp> q;
    for(int i = 0; i < n; i++){
        int t;
        cin>>t;
        vector<pt> a(t + 1);
        for(int j = 0; j < t; j++) cin>>a[j].x>>a[j].y;
        a[t] = a[0];
        for(int j = 1; j <= t; j++){
            q.pb(hp(a[j - 1], a[j] - a[j - 1]));
        }
    }
	sort(q.begin(), q.end());
	vector<half_plane> res;
	for(auto p : q){
		if(!res.size()){
			res.pb(p);
			continue;
		}
		if(fabs(p.deg - res.back().deg) > eps) res.pb(p);
		else if(same_side(res.back(), p.a)){
			res.pop_back();
			res.pb(p);
		}
		else continue;
	}
	half_plane_intersection(res);
    double ans = 0;
    for(int i = l + 2; i < r; i++){
        ans += cross(s[i] - s[l], s[i - 1] - s[l]);
    }
    cout<<fixed<<setprecision(3)<<fabs(ans) / 2<<"\n";
}
