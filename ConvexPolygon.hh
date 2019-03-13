#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh
#include <vector>
#include "Point.hh"
using namespace std;

class ConvexPolygon {
public:

	ConvexPolygon (const vector<Point>& p={});
	double area() const;
	double perimeter() const;
	int vertices() const;
	int edges() const;
	void print() const;
	Point centroid() const;



private:
	vector<Point> v;
};

#endif
