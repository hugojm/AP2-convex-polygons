#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <fstream>
#include <pngwriter.h>
#include <cmath>
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
    double color;
    string name; cin >> name;
    vector<double> rgb(3);
    for (int i = 0;i < rgb.size(); i++){
      cin >> color;
      rgb[i] = color;
    }
    polygons[name].setcol(rgb);
    cout << "ok" << endl;
}

void centroid (map<string, ConvexPolygon>& polygons) {
  string name;
  cin >> name;
  cout << polygons[name].centroid().get_x() << " "  <<  polygons[name].centroid(
  ).get_y() << endl;
}
void save (map<string, ConvexPolygon>& polygons) {
  string file; cin >> file;
  string names;
  getline(cin,names);
  istringstream iss(names);
  string name;
  ofstream myfile;
  myfile.open(file);
  while(iss >> name){
    int n = polygons[name].vertices();
  	myfile << name << " ";
  	for (int i = 0; i < n; i ++){
  		myfile << polygons[name][i].get_x() << " " << polygons[name][i].get_y() << " ";
  	}
    myfile << endl;
  }
	myfile.close();
  cout << "ok" << endl;
}
void load (map<string, ConvexPolygon>& polygons) {
  string file;   cin >> file;
  string line;
  ifstream myfile (file);
  while(getline(myfile,line)){
    istringstream iss(line);
    string name; iss >> name;
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
    string name, name2; cin >> name >> name2;
    polygons[name] = polygons[name].intersection(polygons[name2]);
    cout << "ok" << endl;
}
void unio (map<string, ConvexPolygon>& polygons) {
  string name, name2; cin >> name >> name2;
  polygons[name] = polygons[name].unio(polygons[name2]);
  cout << "ok" << endl;
}

void inside (map<string, ConvexPolygon>& polygons) {
  string name, name2;  cin >> name >> name2;
  if(polygons[name].insidepoly(polygons[name2])) cout <<"yes" << endl;
  else cout << "no" << endl;
}
void draw (map<string, ConvexPolygon>& polygons) {
    string file;  cin >> file;
    string name;  getline(cin,name);
    istringstream iss(name);
    string name2;
    const int size = 500;
    pngwriter png(size, size, 1.0 , file.c_str());
    while(iss >> name2){
      ConvexPolygon v = polygons[name2];
      //escale the polygon to the center
      double escalex = abs(ConvexPolygon(v).centroid().get_x()-249);
      double escaley = abs(ConvexPolygon(v).centroid().get_y()-249);
    	int n = v.vertices()-1;
    	for (int i = 0; i < n; i++){
    		png.line(v[i].get_x()+escalex,v[i].get_y()+escaley,v[i+1].get_x()+escalex,v[i+1].get_y()+escaley,v.getcol(0),v.getcol(1),v.getcol(2));
    	}
    	png.line(v[n].get_x()+escalex,v[n].get_y()+escaley,v[0].get_x()+escalex,v[0].get_y()+escaley,v.getcol(0),v.getcol(1),v.getcol(2));
    }
    png.close();
    cout << "ok" << endl;
}
void bbox (map<string, ConvexPolygon>& polygons) {
  ConvexPolygon bbox;
  string name;
  cin >> name;
  string names;
  getline(cin,name);
  istringstream iss(names);
  string input;
  while(iss >>input){
    bbox = polygons[input].bbox(bbox);
  }
  polygons[name] = bbox;

}

int main () {
   co
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
