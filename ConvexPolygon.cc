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
#define INF 10000

//Auxiliar function to sort the vector by x coordinate
struct myclass {
    bool operator() (const Point& pt1, const Point&pt2) { if (pt1.get_x()==pt2.get_x()) return pt1.get_y() < pt2.get_y();
			else return (pt1.get_x() < pt2.get_x());}
} myobject;

//Function to eliminate repeated points
static vector<Point> repeated(vector<Point> p){
  vector<Point> aux;
  aux.push_back(p[0]);
  for (int i =1; i < p.size(); i++){
    if (p[i]!= p[i-1]) aux.push_back(p[i]);
  }
  return aux;
}


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
static bool onSegment(const Point& p,const Point& q,const Point& r)
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
static int orientation(const Point& p,const Point& q,const Point& r)
{
    double val = (q.get_y() - p.get_y()) * (r.get_x() - q.get_x()) -
              (q.get_x() - p.get_x()) * (r.get_y() - q.get_y());


    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
static bool doIntersect(const Point& p1, const Point& q1,const Point& p2,const Point& q2)
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

//Function to see if to lines are colinear, its very helpful
// in the intersection
static bool colinear (const Point& a,const Point& b,const Point& c,const Point& d){
  double a1 = b.get_y() - a.get_y();
  double b1 = a.get_x() - b.get_x();

  // Line CD represented as a2x + b2y = c2
  double a2 = d.get_y() - c.get_y();
  double b2 = c.get_x() - d.get_x();

  double determinant = a1*b2 - a2*b1;

  if (determinant == 0) return true;
  else return false;
}

//bool for colinear points in Convex Hull
static bool collinear(const Point& a,const Point& b,const Point& c)
{
    double abx = (b.get_x()-a.get_x());
    double aby = (b.get_y()-a.get_y());
    double bcx = (c.get_x()-b.get_x());
    double bcy = (c.get_y()-b.get_y());
    return abx*bcy-aby*bcx == 0;

}

//Eliminate 3 colinear points
static vector<Point> depure(const vector<Point>& p){
  if (p.size() <= 2) return p;
  vector<Point> aux;
  // if 3 points are colineal or not
  bool col = false;
  int n = p.size();
  for (int i = 0; i < n-2; i++){
    if (not col) aux.push_back(p[i]);
    if (not collinear(p[i],p[i+1],p[i+2])) col = false;
    else col  = true;
  }
    if (not col) aux.push_back(p[n-2]);
    if (not collinear(p[n-2],p[n-1],p[0])) aux.push_back(p[n-1]);

  return aux;
}

//returns the intersection of 2 lines given 2 points of the line
static Point lineintersection(const Point& a,const Point& b,const Point& c,const Point& d){
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
          assert(false);
	    }
	    else
	    {
	        double x = (b2*c1 - b1*c2)/(determinant);
	        double y = (a1*c2 - a2*c1)/(determinant);
	        return Point(x, y);
	    }
	}

//Function to do the ConvexHull vector of points
static vector<Point> ConvexHull(vector<Point> points){
  if (points.size() == 0){
    return points;
  }
  else{
	sortx(points);
  points = repeated(points);
  int n = points.size();
  vector<Point> hull;
  // Pick the leftmost point
  int left = 0;
  for (int i = 1; i < n; i++){
    if (points[i].get_x() < points[left].get_x()) left = i;
	}
  	int p = left;
  do {
    hull.push_back(points[p]);  // Add point to the convex hull
		int q = (p + 1)%n; // Pick a point different from p
		for (int i = 0; i < n; i++){
    if (orientation(points[p], points[q], points[i]) == 2) q = i;
	}
    p = q; // Leftmost point for the convex hull
  } while (p != left);  // While not closing polygon
  hull = depure(hull);
  return hull;
}
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
  // sum of the distance of all vertices
	for(int i=0 ; i < n; i++){
		perimeter += dist(v[i], v[i+1]);
	}
  // distance first point and last
	return (perimeter+=dist(v[0], v[n]));
}

void ConvexPolygon::print() const{
	int n = v.size();
  //go through all the vector and print it
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

bool ConvexPolygon::insidepoly (const ConvexPolygon& p) const{
	int nvert2 = v.size();
  // go through the ConvexPolygon and see if all points are inside the other
	for (int i = 0; i < nvert2; i++){
		if (p.insidepoint(v[i]) == false) return false;
	}
	return true;
}

bool ConvexPolygon::insidepoint (const Point& p) const{
    int n = v.size();
    // There must be at least 3 vertices in polygon[]
    if (n < 3)  return false;

    // Create a point for line segment from p to infinite
    Point extreme = {INF, p.get_y()};

    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
        int next = (i+1)%n;

        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(v[i], v[next], p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(v[i], p, v[next]) == 0)
               return onSegment(v[i], p, v[next]);

            count++;
        }
        i = next;
    } while (i != 0);

    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
}



ConvexPolygon ConvexPolygon::intersection (ConvexPolygon p){
	vector<Point> inter;
  // if any polygon is inside the other return that polygon
	if (p.insidepoly(ConvexPolygon(v))) return p;
	if (ConvexPolygon(v).insidepoly(p)) return ConvexPolygon(v);
  int n = v.size();
  int n2 = p.vertices();
	for (int i = 0; i < n2-1; i++){
		// We compare all the edges of the 2 polygons
			for (int j = 0; j < n-1;  j++){
				if(doIntersect(v[i],v[i+1], p[j],p[j+1]) && not colinear(v[i],v[i+1], p[j],p[j+1])){
					inter.push_back(lineintersection(v[i],v[i+1],p[j],p[j+1]));
        }
			}
    }

    //Last edges
    for (int i = 0; i < n-1;  i++){
      if(doIntersect(v[i],v[i+1], p[0],p[n2-1]) && not colinear(v[i],v[i+1], p[0],p[n2-1])){
        inter.push_back(lineintersection(v[i],v[i+1],p[0],p[n2-1]));
      }
    }
    for (int i = 0; i < n2-1;  i++){
      if(doIntersect(v[0],v[n-1], p[i],p[i+1]) && not colinear(v[0],v[n-1], p[i],p[i+1])){
        inter.push_back(lineintersection(v[0],v[n-1],p[i],p[i+1]));
      }
    }
    if(doIntersect(v[0],v[n-1], p[0],p[n2-1]) && not colinear(v[0],v[n-1], p[0],p[n2-1])){
      inter.push_back(lineintersection(v[0],v[n-1],p[0],p[n2-1]));
    }


  for (int i = 0; i <= v.size()-1; i++){
    // If a point is inside the other polygon it's in the intersection
      if (p.insidepoint(v[i])) inter.push_back(v[i]);

  }
  for (int i = 0; i <= p.vertices()-1; i++){
      // If a point is inside the other polygon it's in the intersection
      if (ConvexPolygon(v).insidepoint(p[i])) inter.push_back(p[i]);
  }

	return ConvexPolygon(inter);
}


ConvexPolygon ConvexPolygon::unio(ConvexPolygon p){
  vector<Point> aux;
  //The Convex Union is the Convex Hull of the 2 polygons
  for(int i = 0; i < v.size(); i++){
		aux.push_back(v[i]);
	}
	for(int i = 0; i < p.vertices(); i++){
		aux.push_back(p[i]);
	}
 	return ConvexPolygon(ConvexHull(aux));
}

ConvexPolygon ConvexPolygon::bbox(ConvexPolygon p){
	vector<Point> bbox;
	double minx = v[0].get_x();
  double miny = v[0].get_y();
  double maxx = v[0].get_x();
  double maxy = v[0].get_y();
  //We compare all the points of the polygons and return the minimum and maximum
  if (v.size() > 0){
	   for(int i = 0; i < v.size(); i++){
		     if (v[i].get_y() < miny) miny = v[i].get_y();
         if (v[i].get_x() < minx) minx = v[i].get_x();
		     if (v[i].get_y() > maxx) maxx = v[i].get_x();
		     if (v[i].get_x() > maxy) maxy = v[i].get_y();
	            }
      }
  if(p.vertices() > 0){
    for(int i = 0; i < p.vertices(); i++){
  		if (p[i].get_y() < miny) miny = p[i].get_y();
  		if (p[i].get_x() < minx) minx = p[i].get_x();
  		if (p[i].get_y() > maxx) maxx = p[i].get_x();
  		if (p[i].get_x() > maxy) maxy = p[i].get_y();
  	}
  }
 	bbox.push_back(Point(minx,miny));
 	bbox.push_back(Point(minx,maxy));
 	bbox.push_back(Point(maxx,maxy));
 	bbox.push_back(Point(maxx,miny));
	return ConvexPolygon(bbox);

}

void ConvexPolygon::setcol(const vector<double>& color){
	for (int i = 0; i < color.size(); i++){
		rgb[i] = color[i];
	}
}
