#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh
#include <vector>

#include "Point.hh"


class ConvexPolygon {
public:
<<<<<<< HEAD
	ConvexPolygon();
	ConvexPolygon(const vector<Point>);
=======

	ConvexPolygon (const vector<Point>& p(0));
	ConvexPolygon operator =(vector<Point> r);
>>>>>>> AP2
	double area() const;
	int perimeter() const;
	int vertices() const;
	Point centroid() const;



private:
<<<<<<< HEAD

	vector<Point> p;
=======
	vector<Point> v;
>>>>>>> AP2
};

#endif
