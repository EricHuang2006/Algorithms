#include<bits/stdc++.h>
using namespace std;

struct pt{
	double x, y;
	pt (double x = 0, double y = 0) : x(x), y(y){}
};
typedef pt vec;

vec operator + (vec A, vec B){
	return vec(A.x + B.x, A.y + B.y);
}

vec operator - (vec A, vec B){
	return vec(A.x - B.x, A.y - B.y);
}

vec operator * (vec A, double p){
	return vec(A.x * p, A.y * p);
}

vec operator / (vec A, double p){
	return vec(A.x / p, A.y / p);
}

bool operator < (const pt &a, const pt &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double dot(vec A, vec B){
	return A.x * B.x + A.y * B.y;	
}

double len(vec A){
	return sqrt(dot(A, A));	
}	

double angle(vec A, vec B){
	return acos(dot(A, B) / len(A) / len(B));
}

double cross(vec A, vec B){
	return A.x * B.y - A.y * B.x;
}

double Area2(pt A, pt B, pt C){
	return cross(B - A, C - A);
}

vec Rotate(vec A, double rad){
	return vec(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}

vec Normal(vec A){ // unit normal of vector
	double L = len(A);
	return vec(-A.y / L, A.x / L);
}

const double eps = 1e-10;
int dcmp(double x){
	if(fabs(x) < eps) return 0; 
	else return x < 0? -1 : 1;
}

bool operator == (const pt &a, const pt &b) {
	return dcmp(a.x - b.x) == 0 && dcmp(a.x - b.y) == 0;
}

inline int ori(pt a, pt b, pt c){
	double area = cross(b - a, c - a);
	if(area > -eps && area < eps) return 0;
	return area > 0 ? 1 : -1;
}

inline int btw(pt a, pt b, pt c){ // return if c is between a and b
	if(fabs(cross(b - a, c - a)) > eps) return false;
	if(dot(b - a, c - a) > -eps && len(c - a) <= len(b - a)) return true;
	return false;
}

bool intersect(pt a, pt b, pt c, pt d){
	if(a == c || a == d || b == c || b == d) return true;
	int a123 = ori(a, b, c), a124 = ori(a, b, d), a341 = ori(c, d, a), a342 = ori(c, d, b);
	if(a123 == 0 && a124 == 0){
		if(btw(a, b, c) || btw(a, b, d) || btw(c, d, a) || btw(c, d, b)) return true;
		else return false;
	}
	else if(a123 * a124 <= 0 && a341 * a342 <= 0) return true;
	return false;
}

istream &operator>>(istream &s, pt &a){
	s >> a.x >> a.y;
	return s;
}

int main(void){
	
	vec A;
	while(cin >> A){
		cout<<len(A)<<endl;
	}
}
