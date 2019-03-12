CXXFLAGS = -Wall -std=c++11 -O2

all: main.exe

main.exe: main.o Point.o ConvexPolygon.o
	$(CXX) $^ -o $@

main.o: main.cc Point.hh ConvexPolygon.hh

Point.o: Point.cc Point.hh

ConvexPolygon.o: ConvexPolygon.cc ConvexPolygon.hh Point.hh
