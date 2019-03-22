#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh
#include <vector>
#include <pngwriter.h>
#include "Point.hh"
using namespace std;

class ConvexPolygon {
public:
	//Constructor: vector of Points (if no parameter, creates an empty vector)
	ConvexPolygon (const vector<Point>& p={}, vector<double> color = {0.0,0.0,0.0});
	//Returns the area of the ConvexPolygon
	double area() const;
	//Returns the perimeter
	double perimeter() const;
	//Returns the numer of vertices
	int vertices() const;
	//Returns the number of edges
	int edges() const;
	//Displays a convex polygon
	void print() const;
	//Return the point in the center
	Point centroid() const;
	// Sets the colours of the polygon
	void setcol(vector<double> color);
	// Returns true if a polygon is inside an other
	bool insidepoly (ConvexPolygon p) const;
	// The same with Points
	bool insidepoint (Point p);
	// gets the color of the polygon
	double getcol(int color);
	// returns the union of 2 convex polygons
	ConvexPolygon intersection(ConvexPolygon p);
	// get a point of the convex polygon
	Point& operator[] (int i);
	// returns the union of 2 convex polygons
	ConvexPolygon unio(ConvexPolygon p);
	// returns the bbox of 2 convex polygons
	ConvexPolygon bbox (ConvexPolygon p);


private:
	vector<Point> v;     //Vector of points
	vector<double> rgb;	 //Vector of  double for rgb(setcol function)
};

#endif
