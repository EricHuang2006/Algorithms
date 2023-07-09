/*
	* Date: 2023-07-09
	* Normal Treap with keys and randomized priorities
*/
#include<bits/stdc++.h>
using namespace std;

struct node{
	int val, pri, c = 1;
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
void split(node *&t, int x, node *&l, node *&r){ 
	if(!t){
		l = r = nullptr;
		return;
	}
	if(t->val <= x){
		split(t->r, x, t->r, r);
		l = t;
	}
	else{
		split(t->l, x, l, t->l);
		r = t;
	}
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
