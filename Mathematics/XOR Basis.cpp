/*
	* Created: 2023/08/23
 	* Basic operations using Xor Basis
*/
#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define pb push_back
int basis[30]; // basis[i] : 最高bit為i的一組basis

bool add(int x){
	for(int i = 29; i >= 0; i--){
		if(x & (1 << i)){
			if(!basis[i]){
				basis[i] = x;
				return true;
			}
			x ^= basis[i];
		}
	}
	return false;
}

int find(int x){
	for(int i = 29; i >= 0; i--){
		if(x & (1 << i)) x ^= basis[i];
	}
	return x == 0;
}

int mx(){
 	int mx = 0;
 	for(int i = 29; i >= 0; i--){
		if((x & (1 << i) == 0 && basis[i]) mx ^= basis[i];
  	}
  	return mx;
}
