#include<bits/stdc++.h>
using namespace std;

struct Point{
	
	double x, y;
	Point (double x = 0, double y = 0) : x(x), y(y){}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B){
	return Vector(A.x + B.x, A.y + B.y);
}

Vector operator - (Vector A, Vector B){
	return Vector(A.x - B.x, A.y - B.y);
}

Vector operator * (Vector A, double p){
	return Vector(A.x * p, A.y * p);
}

Vector operator / (Vector A, double p){
	return Vector(A.x / p, A.y / p);
}

bool operator < (const Point &a, const Point &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

const double eps = 1e-10;
int dcmp(double x){
	if(fabs(x) < eps) return 0; 
	else return x < 0? -1 : 1;
}

bool operator == (const Point &a, const Point &b) {
	return dcmp(a.x - b.x) == 0 && dcmp(a.x - b.y) == 0;
}

double dot(Vector A, Vector B){
	return A.x * B.x + A.y * B.y;	
}

double length(Vector A){
	return sqrt(dot(A, A));	
}	

double angle(Vector A, Vector B){
	return acos(dot(A, B) / length(A) / length(B));
}

double cross(Vector A, Vector B){
	return A.x * B.y - A.y * B.x;
}

double Area2(Point A, Point B, Point C){
	return cross(B - A, C - A);
}

Vector Rotate(Vector A, double rad){
	return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
Vector Normal(Vector A){ // unit normal of vector
	double L = length(A);
	return Vector(-A.y / L, A.x / L);
}

int main(void){
	
	Vector A;
	while(cin>>A.x>>A.y){
		cout<<length(A)<<endl;
	}
}
