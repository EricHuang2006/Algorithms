/*
  Created : 2024.5.6
  Description : leftist heap
  Support merging heaps and deletion of an arbitrary node in O(logn)
  Can be made persistent
*/

struct node{
	int ch[2], val, d;
	node(){}
} st[maxn];

int merge(int x, int y){
	if(!x || !y) return x + y;
	if(st[x].val > st[y].val) swap(x, y);
	st[x].ch[1] = merge(st[x].ch[1], y);
	if(st[st[x].ch[0]].d < st[st[x].ch[1]].d) swap(st[x].ch[0], st[x].ch[1]);
	st[x].d = st[st[x].ch[1]].d + 1;
	return x;
}
