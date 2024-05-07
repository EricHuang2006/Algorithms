/*
  Created : 2024.5.6
  Description : leftist heap
  Support merging heaps and deletion of an arbitrary node in O(logn)
  Can be made persistent
*/

struct LeftistTree{
	int cnt, rt[maxn], lc[maxn * 20], rc[maxn * 20], d[maxn * 20];
	int v[maxn * 20];
	LeftistTree(){}
	int newnode(pll nd){
		cnt++;
		v[cnt] = nd;
		return cnt;
	}
	int merge(int x, int y){
		if(!x || !y) return x + y;
		if(v[x] > v[y]) swap(x, y);
		int p = ++cnt;
		lc[p] = lc[x], v[p] = v[x];
		rc[p] = merge(rc[x], y);
		if(d[lc[p]] < d[rc[p]]) swap(lc[p], rc[p]);
		d[p] = d[rc[p]] + 1;
		return p;
	}
} st;
