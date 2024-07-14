/*
  Created : 2024.7.14
  Description : Palindrome Tree
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;

struct EERTREE{
	int sz, tot, last;
	int cnt[maxn], ch[maxn][26], len[maxn], fail[maxn];
	char s[maxn];
	int node(int l){
		sz++;
		memset(ch[sz], 0, sizeof(ch[sz]));
		len[sz] = l;
		fail[sz] = cnt[sz] = 0;
		return sz;
	}
	void init(){
		sz = -1;
		last = 0;
		s[tot = 0] = '$';
		node(0);
		node(-1);
		fail[0] = 1;
	}
	int getfail(int x){
		while(s[tot - len[x] - 1] != s[tot]) x = fail[x];
		return x;
	}
	void insert(char c){
		s[++tot] = c;
		int now = getfail(last);
		if(!ch[now][c - 'a']){
			int x = node(len[now] + 2);
			fail[x] = ch[getfail(fail[now])][c - 'a'];
			ch[now][c - 'a'] = x;
		}
		last = ch[now][c - 'a'];
		cnt[last]++;
	}
} pam;
