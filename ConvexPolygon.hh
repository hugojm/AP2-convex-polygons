#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh
#include <vector>
#include "Point.hh"
using namespace std;

class ConvexPolygon {
public:
	//Constructor: vector of Points (if no parameter, creates an empty vector)
	ConvexPolygon (const vector<Point>& p={});
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
	void print_load(string file, string name) const;
	Point centroid() const;



private:
	vector<Point> v;     //Vector of points
};

#endif
