#include "ConvexPolygon.hh"
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;


static double dist(const Point &a, const Point& b){
	double dx = a.get_x() - b.get_x();
	double dy = a.get_y() - b.get_y();
	return sqrt(dx*dx + dy*dy);
}

ConvexPolygon::ConvexPolygon(vector<Point> p) {
  v = p;
}

ConvexPolygon& ConvexPolygon::operator = (vector<Point> r){
	return vector<Point> r;
}

int ConvexPolygon::vertices(){
	return v.size();
}

double ConvexPolygon::perimeter(){
	double perimeter;
	for(int i=0 ; i < p.size()-1){
		perimeter += dist(p[i], p[i+1]);
	}
	return perimeter;
}

double ConvexPolygon::area(){
    // Initialze area
    double area = 0.0;
    // Calculate value of shoelace formula
    int j = p.size() - 1;
    for (int i = 0; i < n; i++){
        area += (p[i].get_x() + p[j].get_x()) * (p[i].get_y() - p[j].get_y());
        j = i;  // j is previous vertex to i
    }
    // Return absolute value
    return abs(area / 2.0);
}
