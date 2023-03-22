#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int maxk = 2e5 + 5;
int n, k;

struct element{
	int x, y, z;
	int cnt; // count the number of lesser nodes
	int res;
	
	bool operator == (const element other){
		return (x == other.x) && (y == other.y) && (z == other.z);	
	}
};

element arr[maxn];
int res[maxn];

struct Binary_Indexed_Tree{
	int node[maxk];
	int lowbit(int x){
		return x & -x;
	}
	void add(int pos, int val){
		while(pos <= k){
			node[pos] += val;
			pos += lowbit(pos);
		}
		return;
	}
	int qry(int pos){
		int ret = 0;
		while(pos){
			ret += node[pos];
			pos -= lowbit(pos);
		}
		return ret;
	}
} BIT;

inline bool cmpx(element a, element b){
	if(a.x != b.x) return a.x < b.x;
	else if(a.y != b.y) return a.y < b.y;
	return a.z < b.z;
}

inline bool cmpy(element a, element b){
	if(a.y!= b.y) return a.y < b.y;
	return a.z < b.z;
}

void CDQ(int l, int r){
	if(l == r) return;
	int m = (l + r) / 2;
	CDQ(l, m);
	CDQ(m + 1, r);
	vector<element> temp;
	int i = l, j = m + 1;
	while(j <= r){
		while(i <= m && arr[i].y <= arr[j].y){
			temp.push_back(arr[i]);
			BIT.add(arr[i].z, arr[i].cnt);
			i++;
		}
		arr[j].res += BIT.qry(arr[j].z);
		temp.push_back(arr[j]);
		j++;
	}
	for(int k = l; k < i; k++){
		BIT.add(arr[k].z, -arr[k].cnt);
	}
	while(i <= m) temp.push_back(arr[i++]);
	while(j <= r) temp.push_back(arr[j++]);
	for(int i = l, k = 0; i <= r; i++, k++) arr[i] = temp[k];
}

int main(void){
	
	cin>>n>>k;
	int m = 0, t = 0;
	for(int i = 0; i < n; i++){
		cin>>arr[i].x>>arr[i].y>>arr[i].z;
	}
	sort(arr, arr + n, cmpx);
	for(int i = 0; i < n; i++){
		t++;
		if(!(arr[i] == arr[i + 1])){
			arr[m].x = arr[i].x;
			arr[m].y = arr[i].y;
			arr[m].z = arr[i].z;
			arr[m].cnt = t;
			m++;
			t = 0;
		}
	}
	CDQ(0, m - 1);
	for(int i = 0; i < m; i++){
		res[arr[i].res + arr[i].cnt - 1] += arr[i].cnt;
	}
	for(int i = 0; i < n; i++){
		cout<<res[i]<<endl;
	}
}
