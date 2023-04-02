#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

inline ll divceil(ll a, ll b){
	return a / b + ((a < 0) != (b > 0) && (a % b)); // round up for both pos and neg numbers
}

struct line{
	static bool flag; // control what to compare in operator < 
	ll m, k, l, r; // y = mx + k, valid in range [l, r)
	line(ll a, ll b, ll _l = -INF, ll _r = INF) : m(a), k(b), l(_l), r(_r){}
	ll operator()( ll x) const { return m * x + k; }
	bool operator < (const line& other) const{
		return flag ? m < other.m || (m == other.m && k < other.k) : l < other.l;
	}
	ll intersect(const line& other) const{
		return divceil(k - other.k, other.m - m);
	}
};

bool line::flag = true;

class ConvexHullMax {
	set<line> convex;
	void insertline(ll m, ll k){
		line now = line(m, k);
		if(convex.empty()){
			convex.insert(now);
			return;
		}
		line::flag = true;
		auto it = convex.lower_bound(now);
		auto prv = it == convex.begin() ? it : prev(it);
		if(it != convex.end() && ((it != convex.begin() && (*it)(it->l) >= now(it->l) &&
			(*prv)(prv->r - 1) >= now(prv->r - 1)) || (it == convex.begin() && it->m == now.m))){
			return;
			/* 	current line is useful if it satifies one of the following:
				1. It has the greatest slope (or slope is equal but k is greater) along all lines (it == convex.end())
				2. post(now) is not the first line( pre(now) --- now --- post(now) ), and it is
				not covered by both sides at the same time
				3. post(now) is the first line, but slope(now) < slope(post(now)) || 
				(slope(now) == slope(post(now)) && now->k > post(now)->k);
			*/
		}
		if(it != convex.begin()){
			// erase useless lines prior to it
			while(prv != convex.begin() && (*prv)(prv->l) <= now(prv->l)){
				prv = --convex.erase(prv);
			}
			if(prv == convex.begin() && now.m == prv->m){
				convex.erase(prv);
			}
		}
		if(it != convex.end()){
			// erase useless lines after it
			while(it != --convex.end() && (*it)(it->r) <= now(it->r)){
				it = convex.erase(it);
			}
		}
		if(it != convex.begin()){
			prv = prev(it);
			const_cast<line*>(&*prv)->r = now.l = prv->intersect(now);
		}
		if(it != convex.end()){
			const_cast<line*>(&*it)->l = now.r = it->intersect(now);
		}
		convex.insert(it, now);
	}
	ll qry(ll a) const{
		if(convex.empty()) return -INF;
		line::flag = false;
		auto it = --convex.upper_bound(line(0, 0, a, 0));
		return (*it)(a);
	}
};

int main(void){

}
