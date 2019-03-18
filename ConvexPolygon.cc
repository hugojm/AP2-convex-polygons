#include "ConvexPolygon.hh"
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <pngwriter.h>
using namespace std;


static double dist(const Point &a, const Point& b){
	double dx = a.get_x() - b.get_x();
	double dy = a.get_y() - b.get_y();
	return sqrt((dx*dx) + (dy*dy));
}

//Constructor
ConvexPolygon::ConvexPolygon(const vector<Point>& p, vector<double> color): v(p), rgb(color) {}

int ConvexPolygon::vertices() const{
	return v.size();
}
int ConvexPolygon::edges() const {
	if (v.size() < 3) return 1;
	else return v.size();
}

Point ConvexPolygon::index(int i) const{
	return v[i];
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
			// We aply the Shoelace formula of Gauss
			area+= (v[i].get_x()*v[i+1].get_y()) - (v[i+1].get_x()*v[i].get_y());
		}
		return abs(area/2);

}
Point ConvexPolygon::centroid()const{
	double area = ConvexPolygon::area();
	int n = v.size() -1 ;
	double x= 0.0; double y= 0.0;
	for (int i = 0;  i <= n-1; i++){
		x += (v[i].get_x()+v[i+1].get_x())*((v[i].get_x()*v[i+1].get_y())-(v[i+1].get_x()*v[i].get_y()));
		y += (v[i].get_y()+v[i+1].get_y())*((v[i].get_x()*v[i+1].get_y())-(v[i+1].get_x()*v[i].get_y()));
	}
	return Point(-x*(1/(6*area)),-y*(1/(6*area)));

}

bool ConvexPolygon::inside(ConvexPolygon p) const{
	int i, j = 0;
	int nvert = v.size();
	int nvert2 = p.vertices();
	for (int z = 0; z < nvert2; z++){
		bool c = false;
  	for (i = 0, j = nvert-1; i < nvert; j = i++) {
    	if ( ((v[i].get_y() > p.index(z).get_y()) != (v[j].get_y()>p.index(z).get_y())) &&
			(p.index(z).get_x() < (v[j].get_x()-v[i].get_x()) * (p.index(z).get_y()-v[i].get_y()) / (v[j].get_y()-v[i].get_y()) + v[i].get_x()) )
       	c = !c;
  	}
		if (c ==  0) return c;
	}
  	return true;
}
void ConvexPolygon::setcol(vector<double> color){
	for (int i = 0; i < color.size(); i++){
		rgb[i] = color[i];
	}
}

void ConvexPolygon::draw(string file) const{
	const int size = 50;
	int n = v.size()-1;
	pngwriter png(size, size, 0 , file.c_str());
	for (int i = 0; i < n; i++){
		png.line(v[i].get_x(),v[i].get_y(),v[i+1].get_x(),v[i+1].get_y(),rgb[0],rgb[1],rgb[2]);
	}
	png.line(v[n].get_x(),v[n].get_y(),v[0].get_x(),v[0].get_y(),rgb[0],rgb[1],rgb[2]);
	png.close();
}
