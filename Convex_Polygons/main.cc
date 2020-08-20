#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <fstream>
#include <pngwriter.h>
#include <cmath>
#include <locale>
using namespace std;
#include "Point.hh"
#include "ConvexPolygon.hh"


// ************************************************************************************
double dist(const Point &a, const Point& b){
	double dx = a.get_x() - b.get_x();
	double dy = a.get_y() - b.get_y();
	return sqrt((dx*dx) + (dy*dy));
}

void coment(){
  string coment;
  getline(cin,coment);
  istringstream iss(coment);
  cout << "#" << endl;
}

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
    auto it = polygons.find(name);
    if (it == polygons.end()) {
      polygons.insert(pair<string,ConvexPolygon>(name,ConvexPolygon(vp)));

    }
    else polygons[name] = ConvexPolygon(vp);
    cout << "ok" << endl;

}

void print (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    auto it = polygons.find(name);
    if (it != polygons.end()) {
      cout << name << " ";
      polygons[name].print();
    }
    else cout << "error: undeclared identifier" << endl;
}

void area (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    auto it = polygons.find(name);
    if (it != polygons.end()) cout << polygons[name].area() << endl;
    else cout << "error: undeclared identifier" << endl;

}
void perimeter (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    auto it = polygons.find(name);
    if (it != polygons.end()) cout << polygons[name].perimeter() << endl;
    else cout << "error: undeclared identifier" << endl;
}
void vertices (map<string, ConvexPolygon>& polygons) {
    string name;
    cin >> name;
    auto it = polygons.find(name);
    if (it != polygons.end()) cout << polygons[name].vertices() << endl;
    else cout << "error: undeclared identifier" << endl;
}
void list (map<string, ConvexPolygon>& polygons) {
    if (polygons.empty()) cout << "error: diccionary is empty" << endl;
    else {for (auto it : polygons){
      cout << it.first << " ";
    }
    cout << endl;
    }
}
void setcol (map<string, ConvexPolygon>& polygons) {
    double color;
    string name; cin >> name;
    auto it = polygons.find(name);
    if (it != polygons.end()){
    vector<double> rgb(3);
    for (int i = 0;i < rgb.size(); i++){
      cin >> color;
      rgb[i] = color;
    }
    polygons[name].setcol(rgb);
    cout << "ok" << endl;
  }
    else cout << "error: undeclared identifier" << endl;
}

void centroid (map<string, ConvexPolygon>& polygons) {
  string name;
  cin >> name;
  auto it = polygons.find(name);
  if (it != polygons.end()) cout << polygons[name].centroid().get_x() << " "  <<  polygons[name].centroid(
  ).get_y() << endl;
  else cout << "error: undeclared identifier" << endl;

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
  if (!myfile){
    cout << "Failed to open file" << endl;
    return;
  }
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
  vector<string> name;
  string names;
  getline(cin,names);
  istringstream iss(names);
  string aux;
  while(iss >> aux){
    name.push_back(aux);
  }
  if (name.size() == 2){
    polygons[name[0]] = polygons[name[0]].intersection(polygons[name[1]]);
    cout << "ok" << endl;
  }
  else if (name.size() == 3){
    polygons[name[0]] = polygons[name[1]].intersection(polygons[name[2]]);
    cout << "ok" << endl;
  }
  else cout << "error: undeclared identifier" << endl;
}

void unio (map<string, ConvexPolygon>& polygons) {
  vector<string> name;
  string names;
  getline(cin,names);
  istringstream iss(names);
  string aux;
  while(iss >> aux){
    name.push_back(aux);
  }
  if (name.size() == 2){
    polygons[name[0]] = polygons[name[0]].unio(polygons[name[1]]);
    cout << "ok" << endl;
  }
  else if (name.size() == 3){
    polygons[name[0]] = polygons[name[1]].unio(polygons[name[2]]);
    cout << "ok" << endl;
  }
  else cout << "error: undeclared identifier" << endl;
}

void inside (map<string, ConvexPolygon>& polygons) {
  string name, name2;  cin >> name >> name2;
  auto it = polygons.find(name);
  auto it2 = polygons.find(name2);
  if (it != polygons.end() &  it2 != polygons.end()){
    if(polygons[name].insidepoly(polygons[name2])) cout <<"yes" << endl;
    else cout << "no" << endl;
  }
  else cout << "error: undeclared identifier" << endl;


}
void draw (map<string, ConvexPolygon>& polygons) {
    string file;  cin >> file;
    string name;  getline(cin,name);
    istringstream iss(name);
    string name2;
    const int size = 500;
    pngwriter png(size, size, 1.0 , file.c_str());
    ConvexPolygon bbox;
    vector<ConvexPolygon> aux;
    // We save all the polygons into a vector of Convex Polygons
    // We do the bbox of all polygons
    while(iss >> name2){
      aux.push_back(polygons[name2]);
      bbox = polygons[name2].bbox(bbox);
    }
    // We scale all the polygons with the bounding box
    int dx = -bbox[0].get_x();
    int dy = -bbox[0].get_y();
    int llarg = max(dist(bbox[0],bbox[1]),dist(bbox[0],bbox[3]));
    int k = 498/llarg;

    // We print the polygons with the scale
    for (int j = 0; j < aux.size(); j++){
      ConvexPolygon v = aux[j];
      int n = v.vertices()-1;
      for (int i = 0; i < n; i++){
        png.line((v[i].get_x()+dx)*k+1,(v[i].get_y()+dy)*k+1,(v[i+1].get_x()+dx)*k+1,(v[i+1].get_y()+dy)*k+1,v.getcol(0),v.getcol(1),v.getcol(2));
      }
      png.line((v[n].get_x()+dx)*k+1,(v[n].get_y()+dy)*k+1,(v[0].get_x()+dx)*k+1,(v[0].get_y()+dy)*k+1,v.getcol(0),v.getcol(1),v.getcol(2));
    }
  png.close();
  cout << "ok" << endl;

}



void bbox (map<string, ConvexPolygon>& polygons) {
  ConvexPolygon bbox;
  string name;
  cin >> name;
  string names;
  getline(cin,names);
  istringstream iss(names);
  string input;
  while(iss >>input){
    bbox = polygons[input].bbox(bbox);
  }
  polygons.insert(pair<string,ConvexPolygon>(name,ConvexPolygon(bbox)));
  cout << "ok" << endl;


}

int main () {
    cout.setf(ios::fixed);
    cout.precision(3);
    map<string, ConvexPolygon> polygons;
    string action;
    while (cin >> action) {
        if (action == "polygon")                polygon(polygons);
        else if (action == "#")                      coment();
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
