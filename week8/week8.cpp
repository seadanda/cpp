// week8.cpp: Shape manipulator
// Class heirarchy to deal with various 2- and 3D shapes
// Author:  Dónal Murray
// Date:    21/03/2017

#include <cmath>    //M_PI
#include <iostream> // std io

using namespace std;

class Shape // abstract base class
{

protected:
  int side_ct;
  double *sides;

public:
  Shape(const int &dim) { sides = new double[dim]; } // constructor
  virtual ~Shape() { delete[] sides; };              // destructor
  virtual double area() = 0;                         // calculate area
  virtual double volume() = 0;                       // calculate volume
};

// 2D shapes
class TwoD : public Shape // abstract derived class for 2d shapes
{
public:
  // default constructor
  TwoD() : Shape(2) {
    sides[0] = 0;
    sides[1] = 0;
  }
  // parametrised constructor
  TwoD(const double &length, const double &width) : Shape(2) {
    sides[0] = length;
    sides[1] = width;
  }
  double volume() { return 0; }
};

class Rectangle : public TwoD // derived class for rectangles
{
public:
  Rectangle(const double &length, const double &width) : TwoD(length, width) {}
  double area() { return sides[0] * sides[1]; }
};

class Square : public Rectangle // specialisation of Rectangle for squares
{
public:
  Square(const double &length) : Rectangle(length, length) {}
};

class Ellipse : public TwoD // derived class for ellipses
{
public:
  Ellipse(const double &major, const double &minor) : TwoD(major, minor) {}
  double area() { return M_PI * sides[0] * sides[1]; }
};

class Circle : public Ellipse // specialisation of Ellipse for circles
{
public:
  Circle(const double &radius) : Ellipse(radius, radius) {}
};

// 3D shapes
class ThreeD : public Shape // abstract derived class for 3d shapes
{
public:
  // default constructor
  ThreeD() : Shape(3) {
    sides[0] = 0;
    sides[1] = 0;
    sides[2] = 0;
  }
  // parametrised constructor
  ThreeD(const double &length, const double &width, const double &height)
      : Shape(3) {
    sides[0] = length;
    sides[1] = width;
    sides[2] = height;
  }
  double area() { return 0; }
};

class Cuboid : public ThreeD // derived class for cuboids
{
public:
  Cuboid(const double &length, const double &width, const double &height)
      : ThreeD(length, width, height) {}
  double volume() { return sides[0] * sides[1] * sides[2]; }
};

class Cube : public Cuboid // specialisation of Cuboid for cubes
{
public:
  Cube(const double &length) : Cuboid(length, length, length) {}
};

class Ellipsoid : public ThreeD // derived class for ellipsoids
{
public:
  Ellipsoid(const double &major, const double &minor, const double &semi)
      : ThreeD(major, minor, semi) {}
  double volume() { return 4 / 3 * M_PI * sides[0] * sides[1]; }
};

class Sphere : public Ellipsoid // specialisation of Ellipsoid for spheres
{
public:
  Sphere(const double &radius) : Ellipsoid(radius, radius, radius) {}
};

int main() {
  //---2D Shapes---
  cout << "---------------\n---2D shapes---\n";
  Rectangle rect1{2, 3};
  Square squa1{3};
  Ellipse elli1{2, 3};
  Circle circ1{3};
  // print out areas
  cout << "rectangle area = " << rect1.area() << endl
       << "square area    = " << squa1.area() << endl
       << "ellipse area   = " << elli1.area() << endl
       << "circle area    = " << circ1.area() << endl
       << endl
       // volumes
       << "rectangle volume = " << rect1.volume() << endl
       << "square volume    = " << squa1.volume() << endl
       << "ellipse volume   = " << elli1.volume() << endl
       << "circle volume    = " << circ1.volume() << endl
       << "---------------\n";
  //---------------

  //---3D Shapes---
  cout << "\n---3D shapes---\n";
  Cuboid cuboi1{2, 3, 4};
  Cube cuube1{3};
  Ellipsoid ellip1{2, 3, 4};
  Sphere spher1{3};
  // print out surface areas
  /*
    cout << "cuboid surface area      = " << cuboi1.area() << endl
         << "cube surface area        = " << cuube1.area() << endl
         << "ellipsoid surface area   = " << ellip1.area() << endl
         << "sphere surface area      = " << spher1.area() << endl
         << endl;
         */
  // volumes
  cout << "cuboid volume    = " << cuboi1.volume() << endl
       << "cube volume      = " << cuube1.volume() << endl
       << "ellipsoid volume = " << ellip1.volume() << endl
       << "sphere volume    = " << spher1.volume() << endl
       << "---------------\n";
  //---------------

  // exit
  return 0;
}
