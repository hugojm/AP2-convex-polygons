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
	return sqrt(dx*dx + dy*dy);
}

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
	for(int i=0 ; i < v.size()-1; i++){
		perimeter += dist(v[i], v[i+1]);
	}
	return perimeter;
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
    // Calculate value of shoelace formula
    int j = v.size() - 1;
		int n = v.size();
    for (int i = 0; i < n; i++)
    {
        area += (v[i].get_x() + v[j].get_x()) * (v[i].get_y() - v[j].get_y());
        j = i;  // j is previous vertex to i
    }
    // Return absolute value
    return abs(area / 2.0);
}
