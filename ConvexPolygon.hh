#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh
#include <vector>

#include "Point.hh"


class ConvexPolygon {

public:
	ConvexPolygon();
	ConvexPolygon(const vector<Point>);
	double area() const;
	int perimeter() const;
	int vertices() const;
	Point centroid() const;



private:

	vector<Point> p;
};

#endif
