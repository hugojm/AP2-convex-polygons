#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

#include "Point.hh"
#include "ConvexPolygon.hh"


// ************************************************************************************


void polygon (map<string, ConvexPolygon>& polygons) {
    string name;
    ConvexPolygon v;
    cin >> name;
    double x, y;
    vector<Point> aux;
    while(cin >> x >> y){
        aux.push_back(Point(x,y));
    }
    v = aux;
    polygons[name] =  v;
}


void area (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    polygons[name].area();
}

/*void point_get_x (map<string, Point>& points) {
    string name;
    cin >> name;
    cout << points[name].get_x() << endl;
}


void point_get_y (map<string, Point>& points) {
    string name;
    cin >> name;
    cout << points[name].get_y() << endl;
}


void point_radius (map<string, Point>& points) {
    string name;
    cin >> name;
    cout << points[name].radius() << endl;
}


void point_angle (map<string, Point>& points) {
    string name;
    cin >> name;
    cout << points[name].angle() << endl;
}


void point_distance (map<string, Point>& points) {
    string name1, name2;
    cin >> name1 >> name2;
    cout << points[name1].distance(points[name2]) << endl;
}


void point_eq (map<string, Point>& points) {
    string name1, name2;
    cin >> name1 >> name2;
    cout << (points[name1] == points[name2]) << endl;
}


void point_ne (map<string, Point>& points) {
    string name1, name2;
    cin >> name1 >> name2;
    cout << (points[name1] != points[name2]) << endl;
}


void point_add (map<string, Point>& points) {
    string name1, name2;
    cin >> name1 >> name2;
    points[name1] += points[name2];
}
*/

int main () {
    map<string, ConvexPolygon> polygons;
    string action;
    while (cin >> action) {
/*         if (action == "polygon")             point_def(polygons); */
        if (action == "polygons")  polygon(polygons);
        else if (action == "area") area(polygons);
/*        else if (action == "perimeter")           point_get_y(points);
        else if (action == "vertices")          point_radius(points);
        else if (action == "centroid")           point_angle(points);
        else if (action == "save")              point_distance(points);
        else if (action == "load")              point_eq(points);
        else if (action == "union")              point_ne(points);
        else if (action == "inside")             point_add(points);
        else if (action == "setcol")              rect_def(points, rects);

        else assert(false);
*/
        /** Extend for Circle !!! **/
    }
}
