/*
	* Date: 2023-07-09
	* Implicit Treap: throw away the keys
	* The only part that differs from the original treap is the split function
*/
#include<bits/stdc++.h>
using namespace std;

struct node{
	int val, pri, c = 1; // val is additional information we wish to store at a node
	node *l, *r;
	node(int _val) : val(_val), pri(rand()), l(nullptr), r(nullptr){}
	void recalc();
} *rt;
int cnt(node *t){
	return t ? t->c : 0;
}
void node::recalc(){
	c = cnt(l) + cnt(r) + 1;
}
void split(node *&t, node *&l, node *&r, int val){ 
	if(!t){
		l = r = nullptr;
		return;
	}
	if(cnt(t->l) < val){
		split(t->r, t->r, r, val - cnt(t->l) - 1);
		l = t;
	}
	else{
		split(t->l, l, t->l, val);
		r = t;
	}
	t->recalc();
}

node* merge(node *a, node *b){ //requirement : all keys in a are less than all keys in b
	if(!a || !b) return a ? a : b;
	if(a->pri > b->pri){
		a->r = merge(a->r, b);
		return a;
	}
	else{
		b->l = merge(l, b->l);
		return b;
	}
}

node* insert(node *t, int k){
	node *a, *b;
	split(t, k, a, b);
	return merge(merge(a, new node(k)), b);
}

node remove(node *t, int k){
	node *a, *b, *c;
	split(t, k - 1, a, b);
	split(b, k, b, c);
	return merge(a, c);
}

int main(void){
	fastio;

}
