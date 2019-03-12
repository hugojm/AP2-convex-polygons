#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh
#include <vector>

#include "Point.hh"


class ConvexPolygon {
public:

	ConvexPolygon (const vector<Point>& p(0));
	ConvexPolygon operator =(vector<Point> r);
	double area() const;
	int perimeter() const;
	int vertices() const;
	Point centroid() const;



private:
	vector<Point> v;
};

#endif
