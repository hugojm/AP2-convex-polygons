#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh
#include <vector>
#include "Point.hh"
using namespace std;

class ConvexPolygon {
public:
	//Constructor: vector of Points (if no parameter, creates an empty vector)
	ConvexPolygon (const vector<Point>& p={}, vector<double> color = {1.0,1.0,1.0});
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
	// auxiliar function to print into a  file
	void print_load(string file, string name) const;
	//Return the point in the center
	Point centroid() const;
	// Sets the colours of the polygon
	void setcol(vector<double> color);
	bool inside(ConvexPolygon p) const;
	void draw (string file) const;
	Point index(int i) const;


private:
	vector<Point> v;     //Vector of points
	vector<double> rgb;	 //Vector of  double for rgb
};

#endif
