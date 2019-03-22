#include "ConvexPolygon.hh"
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <pngwriter.h>
#include <cfloat>
#include <stdlib.h>
using namespace std;

//Auxiliar function to sort the vector by x coordinate
struct myclass {
    bool operator() (const Point& pt1, const Point&pt2) { return (pt1.get_x() < pt2.get_x());}
} myobject;
//sort vector by x coordinate
static void sortx(vector<Point>& p){
	sort(p.begin(),p.end(),myobject);
}
//funcion to calculate the distance between 2 points
static double dist(const Point &a, const Point& b){
	double dx = a.get_x() - b.get_x();
	double dy = a.get_y() - b.get_y();
	return sqrt((dx*dx) + (dy*dy));
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
static bool onSegment(Point p, Point q, Point r)
{
    if (q.get_x() <= max(p.get_x(), r.get_x()) && q.get_x() >= min(p.get_x(), r.get_x()) &&
        q.get_y() <= max(p.get_y(), r.get_y()) && q.get_y() >= min(p.get_y(), r.get_y()))
       return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
static int orientation(Point p, Point q, Point r)
{
    int val = (q.get_y() - p.get_y()) * (r.get_x() - q.get_x()) -
              (q.get_x() - p.get_x()) * (r.get_y() - q.get_y());

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
static bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}

//returns the intersection of 2 lines given 2 points of the line
static Point lineintersection(Point a, Point b, Point c, Point d){
			double a1 = b.get_y() - a.get_y();
	    double b1 = a.get_x() - b.get_x();
	    double c1 = a1*(a.get_x()) + b1*(a.get_y());

	    // Line CD represented as a2x + b2y = c2
	    double a2 = d.get_y() - c.get_y();
	    double b2 = c.get_x() - d.get_x();
	    double c2 = a2*(c.get_x())+ b2*(c.get_y());

	    double determinant = a1*b2 - a2*b1;

	    if (determinant == 0)
	    {
	        // The lines are parallel. This is simplified
	        // by returning a pair of FLT_MAX
	        return  0;
	    }
	    else
	    {
	        double x = (b2*c1 - b1*c2)/determinant;
	        double y = (a1*c2 - a2*c1)/determinant;
	        return Point(int(x), int(y));
	    }
	}

// Returns true if p3 is at the left of p1p2
static bool leftof(Point p1, Point p2, Point p3) {
	return (p2.get_x() - p1.get_x()) * (p3.get_y() - p1.get_y()) > (p2.get_y()- p1.get_y()) * (p3.get_x() - p1.get_x());
}

//Function to do the ConvexHull vector of points
static vector<Point> ConvexHull(vector<Point> p){
	vector<Point> q(p.size());
	sortx(p);
	int m = 1;
	for (int i=0; i <= 2; i++){
		q[i]=p[i];
	}
	int n = p.size();
	for (int k = 2; k < n; k++){
		//if the point pk its on the left we have to go back and pop back the last element
		while (leftof(q[m-1], q[m] , p[k])){
			m = m - 1;
			q.pop_back();
		}
		m = m+ 1;
		q[m]=p[k];
	}
	return q;
}

//Constructor
ConvexPolygon::ConvexPolygon(const vector<Point>& p, vector<double> color): v(ConvexHull(p)), rgb(color) {}


int ConvexPolygon::vertices() const{
	return v.size();
}

int ConvexPolygon::edges() const {
	if (v.size() < 3) return v.size()-1;
	else return v.size();
}

Point& ConvexPolygon::operator[] (int i){
	return v[i];
}
double ConvexPolygon::getcol(int color){
	return rgb[color];
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

bool ConvexPolygon::insidepoly (ConvexPolygon p) const{
	int nvert2 = p.vertices();
	for (int i = 0; i < nvert2; i++){
		if (not p.insidepoint(v[i])) return false;
	}
	return true;
}

bool ConvexPolygon::insidepoint (Point p) {
	int i, j, c = 0;
	int nvert = v.size();
	for (i = 0, j = nvert-1; i < nvert; j = i++) {
		if ( ((v[i].get_y() > p.get_y()) != (v[j].get_y() >p .get_y())) &&
		(p.get_x() < (v[j].get_x()-v[i].get_x()) * (p.get_y()-v[i].get_y()) / (v[j].get_y()-v[i].get_y()) + v[i].get_x()) )
			c = !c;
	}
	return c;
}

ConvexPolygon ConvexPolygon::intersection (ConvexPolygon p){
	vector<Point> inter;
	if (p.insidepoly(ConvexPolygon(v))) return p;
	if (ConvexPolygon(v).insidepoly(p)) return ConvexPolygon(v);

	for (int i = 0; i < p.vertices()-1; i++){
		// If a point is inside the other polygon it's in the intersection
		if (ConvexPolygon(v).insidepoint(p[i])){
			inter.push_back(p[i]);
		}
		if (p.insidepoint(v[i])){
			inter.push_back(v[i]);
		}
		if(doIntersect(v[i],v[i+1], p[0],p[p.vertices()-1])){
			inter.push_back(lineintersection(v[i],v[i+1],p[0],p[p.vertices()-1]));
		}
		// We compare all the  of 
			for (int j = 0; j < v.size()-1;  j++){
				if(doIntersect(v[i],v[i+1], p[j],p[j+1])){
					inter.push_back(lineintersection(v[i],v[i+1],p[j],p[j+1]));
				}

				if(doIntersect(v[0],v[v.size()], p[j],p[j+1])){
					inter.push_back(lineintersection(v[0],v[v.size()],p[j],p[j+1]));
				}
			}
		}
	return inter;
}

ConvexPolygon ConvexPolygon::unio(ConvexPolygon  p){
	vector<Point> unio;
	for(int i = 0; i < p.vertices(); i++){
		v.push_back(p[i]);
	}
 	return ConvexHull(v);
}

ConvexPolygon ConvexPolygon::bbox(ConvexPolygon p){
	vector<Point> bbox;
	double minx, miny, maxx, maxy;
	for(int i = 0; i < v.size(); i++){
		if (v[i].get_y() > miny) miny = v[i].get_y();
		if (v[i].get_x() > minx) minx = v[i].get_x();
		if (v[i].get_y() > maxx) maxx = v[i].get_x();
		if (v[i].get_x() > maxy) maxy = v[i].get_y();
	}
	for(int i = 0; i < p.vertices(); i++){
		if (p[i].get_y() > miny) miny = p[i].get_y();
		if (p[i].get_x() > minx) minx = p[i].get_x();
		if (p[i].get_y() > maxx) maxx = p[i].get_x();
		if (p[i].get_x() > maxy) maxy = p[i].get_y();
	}
 	bbox.push_back(Point(minx,miny));
 	bbox.push_back(Point(minx,maxy));
 	bbox.push_back(Point(maxx,maxy));
 	bbox.push_back(Point(maxx,miny));
	return bbox;

}

void ConvexPolygon::setcol(vector<double> color){
	for (int i = 0; i < color.size(); i++){
		rgb[i] = color[i];
	}
}
