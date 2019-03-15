#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <fstream>
using namespace std;

#include "Point.hh"
#include "ConvexPolygon.hh"


// ************************************************************************************


void polygon (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    string numbers;
    getline(cin,numbers);
    istringstream iss(numbers);
    double x, y;
    vector<Point> vp;
    while(iss >> x >> y){
        vp.push_back(Point(x,y));
    }
    polygons.insert(pair<string,ConvexPolygon>(name,ConvexPolygon(vp)));
    cout << "ok" << endl;
}

void print (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    polygons[name].print();
}

void area (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    cout << polygons[name].area() << endl;
}
void perimeter (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    cout << polygons[name].perimeter() << endl;
}
void vertices (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    cout << polygons[name].vertices() << endl;
}
void list (map<string, ConvexPolygon>& polygons) {
    for (auto it : polygons){
      cout << it.first << " ";
    }
    cout << endl;
}
void setcol (map<string, ConvexPolygon>& polygons) {
    int r,g,b;
    cin >> r >> g >> b;
    cout << "ok" << endl;
}

void centroid (map<string, ConvexPolygon>& polygons) {
    int r,g,b;
    cin >> r >> g >> b;
}
void save (map<string, ConvexPolygon>& polygons) {
  string file;
  cin >> file;
  string name;
  cin >> name;
  polygons[name].print_load(file,name);
  cout << "ok" << endl; 
}
void load (map<string, ConvexPolygon>& polygons) {
  string file;
  string line;
  cin >> file;
  ifstream myfile (file);
  while(getline(myfile,line)){
    istringstream iss(line);
    string name;
    iss >> name;
    double x, y;
    vector<Point> vp;
    while(iss >> x >> y){
        vp.push_back(Point(x,y));
    }
    polygons.insert(pair<string,ConvexPolygon>(name,ConvexPolygon(vp)));
  }
    cout << "ok" << endl;
}
void intersection (map<string, ConvexPolygon>& polygons) {
    int r,g,b;
    cin >> r >> g >> b;
}
void unio (map<string, ConvexPolygon>& polygons) {
    int r,g,b;
    cin >> r >> g >> b;
}
void inside (map<string, ConvexPolygon>& polygons) {
    int r,g,b;
    cin >> r >> g >> b;
}
void draw (map<string, ConvexPolygon>& polygons) {
    int r,g,b;
    cin >> r >> g >> b;
}
void bbox (map<string, ConvexPolygon>& polygons) {
    int r,g,b;
    cin >> r >> g >> b;
}

int main () {
    map<string, ConvexPolygon> polygons;
    string action;
    while (cin >> action) {
        if (action == "polygon")                polygon(polygons);
        else if (action == "area")              area(polygons);
        else if (action == "print")             print(polygons);
        else if (action == "perimeter")         perimeter(polygons);
        else if (action == "list")              list(polygons);
        else if (action == "vertices")          vertices(polygons);
        else if (action == "centroid")          centroid(polygons);
        else if (action == "save")              save(polygons);
        else if (action == "load")              load(polygons);
        else if (action == "intersection")      intersection(polygons);
        else if (action == "union")             unio(polygons);
        else if (action == "inside")            inside(polygons);
        else if (action == "setcol")            setcol(polygons);
        else if (action == "draw")              draw(polygons);
        else if (action == "bbox")              bbox(polygons);
        else cout << "error: unrecognized command" <<  endl;
    }
}
