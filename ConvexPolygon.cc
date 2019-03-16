#include "ConvexPolygon.hh"
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;


static double dist(const Point &a, const Point& b){
	double dx = a.get_x() - b.get_x();
	double dy = a.get_y() - b.get_y();
	return sqrt((dx*dx) + (dy*dy));
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

void ConvexPolygon::print_load(string file,string name) const{
	ofstream myfile;
  myfile.open(file);
	int n = v.size();
	myfile << name << " ";
	for (int i = 0; i < n; i ++){
		myfile << v[i].get_x() << " " << v[i].get_y() << " ";
	}
	myfile << endl;
	myfile.close();
}

double ConvexPolygon::area() const{
    // Initialze area
    double area = 0.0;
		int n = v.size() -1;
    for (int i = 0; i <= n-1; i++){
			area+= (v[i].get_x()*v[i+1].get_y() + v[0].get_y()*v[n].get_x()) -
			(v[i+1].get_x()*v[i].get_y() - v[0].get_x()*v[n].get_y());
		}
		return abs(area/2);

}
