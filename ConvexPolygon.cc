#include "ConvexPolygon.hh"
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;


static double dist(const Point &a, const Point& b){
	double dx = a.get_x() - b.get_x();
	double dy = a.get_y() - b.get_y();
	return sqrt((dx*dx) + (dy*dy));
}
static Point alt(const Point &a, const Point& b){
	double x = (b.get_x() - a.get_x())/2;
	double y = (b.get_y() - a.get_y())/2;
	return Point(x,y);
}

//Constructor
ConvexPolygon::ConvexPolygon(const vector<Point>& p): v(p) {}

int ConvexPolygon::vertices() const{
	return v.size();
}
int ConvexPolygon::edges() const {
	if (v.size() < 3) return 1;
	else return v.size();
}

double ConvexPolygon::perimeter() const{
	double perimeter = 0.0;
	int n = v.size()-1;
	for(int i=0 ; i < n; i++){
		perimeter += dist(v[i], v[i+1]);
	}
	return (perimeter+=dist(v[0], v[n]));
}

void ConvexPolygon::print() const{
	int n = v.size();
	for (int i = 0; i < n; i ++){
		cout << v[i].get_x() << " " << v[i].get_y() << " ";
	}
	cout << endl;
}

double ConvexPolygon::area() const{
    // Initialze area
    double area = 0.0;
		Point vect;
    for (int i = 2; i < v.size()-1; i++){
			vect = alt(v[0],v[i]);
			area+= dist(v[0],v[i])*dist(v[i-1],vect);
		}
		return area;

}
