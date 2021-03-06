// week8.cpp: Shape manipulator
// Class heirarchy to deal with various 2- and 3D shapes
// Author:  Dónal Murray
// Date:    21/03/2017

#include <cmath>    // M_PI, sqrt, pow
#include <iomanip>  // setprecision
#include <iostream> // std io, fixed
#include <vector>   // polymorphic vector

using namespace std;

// Interface class for all shapes
class Shape // abstract base class
{
  friend class Prism;

protected:
  // member data
  int dimensions;  // number of lengths required to specify shape
  double *lengths; // array to store these lengths in

public:
  Shape(const int &dim) { lengths = new double[dim]; } // constructor
  virtual ~Shape() { delete[] lengths; };              // destructor
  // pure virtual member functions
  virtual double area() = 0;   // calculate area
  virtual double volume() = 0; // calculate volume
};
// end of interface for all shapes

// 2D shapes
class TwoD : public Shape // abstract derived class for 2d shapes
{
public:
  TwoD();                                          // default constructor
  TwoD(const double &length, const double &width); // parametrised constructor

  // member functions
  double volume() { return 0; } // volume of 2d shapes is always zero
};

// default constructor for 2d shapes
TwoD::TwoD() : Shape(2) {
  lengths[0] = 0;
  lengths[1] = 0;
}

// parametrised constructor for 2d shapes
TwoD::TwoD(const double &length, const double &width) : Shape(2) {
  lengths[0] = length;
  lengths[1] = width;
}
// end of 2d abstract derived class

// rectangle class
class Rectangle : public TwoD // derived class for rectangles
{
public:
  // default constructor
  Rectangle() : TwoD() {}
  // parametrised constructor
  Rectangle(const double &length, const double &width);

  // member functions
  double area();
};

// parametrised constructor for rectangle
Rectangle::Rectangle(const double &length, const double &width)
    : TwoD(length, width) {}

// area of rectangle
double Rectangle::area() { return lengths[0] * lengths[1]; }
// end of rectangle class

// square class
class Square : public Rectangle // specialisation of Rectangle for squares
{
public:
  // default constructor
  Square() : Rectangle() {}
  // parametrised constructor
  Square(const double &length) : Rectangle(length, length) {}
};
// end of square class

// ellipse class
class Ellipse : public TwoD // derived class for ellipses
{
public:
  // default constructor
  Ellipse() : TwoD() {}
  // parametrised constructor
  Ellipse(const double &major, const double &minor);

  // member functions
  double area(); // area
};
// parametrised constructor for ellipse
Ellipse::Ellipse(const double &major, const double &minor)
    : TwoD(major, minor) {}

// area of ellipse
double Ellipse::area() { return M_PI * lengths[0] * lengths[1]; }
// end of ellipse class

// circle class
class Circle : public Ellipse // specialisation of Ellipse for circles
{
public:
  // default constructor
  Circle() : Ellipse() {}
  // parametrised constructor
  Circle(const double &radius) : Ellipse(radius, radius) {}
};
// end of circle class

//
// 3D shapes
//
class ThreeD : public Shape // abstract derived class for 3d shapes
{
public:
  // default constructor
  ThreeD();
  // parametrised constructor
  ThreeD(const double &length, const double &width, const double &height);
};

// default constructor
ThreeD::ThreeD() : Shape(3) {
  lengths[0] = 0;
  lengths[1] = 0;
  lengths[2] = 0;
}
// parametrised constructor
ThreeD::ThreeD(const double &length, const double &width, const double &height)
    : Shape(3) {
  lengths[0] = length;
  lengths[1] = width;
  lengths[2] = height;
}
// end of 3d abstract derived class

// cuboid class
class Cuboid : public ThreeD // derived class for cuboids
{
public:
  // default constructor
  Cuboid() : ThreeD() {}
  // parametrised constructor
  Cuboid(const double &length, const double &width, const double &height);

  // member functions
  double volume(); // volume
  double area();   // surface area
};

// parametrised constructor for cuboid
Cuboid::Cuboid(const double &length, const double &width, const double &height)
    : ThreeD(length, width, height) {}

// volume of cuboid
double Cuboid::volume() { return lengths[0] * lengths[1] * lengths[2]; }

// surface area of cuboid
double Cuboid::area() {
  return 4 * lengths[0] * lengths[1] + 2 * lengths[1] * lengths[2];
}
// end of cuboid class

// cube class
class Cube : public Cuboid // specialisation of Cuboid for cubes
{
public:
  // default constructor
  Cube() : Cuboid() {}
  // parametrised constructor
  Cube(const double &length) : Cuboid(length, length, length) {}
};
// end of cube class

// ellipsoid class
class Ellipsoid : public ThreeD // derived class for ellipsoids
{
public:
  // default constructor
  Ellipsoid() : ThreeD() {}
  // parametrised constructor
  Ellipsoid(const double &major, const double &minor, const double &semi);

  // member functions
  double volume(); // volume
  double area();   // surface area (assuming prolate)
};

// parametrised constructor for ellipsoid
Ellipsoid::Ellipsoid(const double &major, const double &minor,
                     const double &semi)
    : ThreeD(major, minor, semi) {}

// volume of ellipsoid
double Ellipsoid::volume() { return 4 / 3 * M_PI * lengths[0] * lengths[1]; }

// surface area of ellipsoid using Knud Thomsen's formula obtained from
// http://www.web-formulas.com/Math_Formulas/Geometry_Surface_of_Ellipsoid.aspx
double Ellipsoid::area() {
  double a{lengths[0]};   // semi major
  double b{lengths[1]};   // semi minor
  double c{lengths[2]};   // z
  const double p{1.6075}; // knud thomsen const
  return 4 * M_PI *
         pow((pow(a * b, p) + pow(a * c, p) + pow(b * c, p)) / 3, 1 / p);
}
// end of ellipsoid class

// Sphere class
class Sphere : public Ellipsoid // specialisation of Ellipsoid for spheres
{
public:
  // default constructor
  Sphere() : Ellipsoid() {}
  // parametrised constructor
  Sphere(const double &radius) : Ellipsoid(radius, radius, radius) {}
};
// end of sphere class

// prism class
class Prism : public ThreeD // class for prisms
{
private:
  double face_area;

public:
  // parametrised constructor
  Prism(const double &depth, Shape *face_in);

  // member functions
  double volume(); // volume of prism
  double area() { return 0; }
};

// parametrised constructor
Prism::Prism(const double &depth, Shape *face_in)
    : ThreeD(depth, face_in->lengths[0], face_in->lengths[1]) {
  face_area = face_in->area();
}

// volume of prism
double Prism::volume() { return lengths[0] * face_area; }
// end of prism class

// main program
int main() {
  // declare polymorphic vector to store shapes
  vector<Shape *> shapes;

  // fill vector with one of each shape
  shapes.push_back(new Rectangle{2, 3});
  shapes.push_back(new Square{3});
  shapes.push_back(new Ellipse{2, 3});
  shapes.push_back(new Circle{3});
  shapes.push_back(new Cuboid{2, 3, 4});
  shapes.push_back(new Cube{3});
  shapes.push_back(new Ellipsoid{2, 3, 4});
  shapes.push_back(new Sphere{3});

  // make a table of areas (/surface areas) and volumes
  cout << "\nTable of areas (/surface areas) and volumes of all shapes:\n"
       << "  rectangle  square  ellipse  circle  cuboid  cube  ellipsoid  "
          "sphere\narea  : ";

  // iterate through vector and get the area of each shape
  for (auto shape_it = shapes.begin(); shape_it != shapes.end(); shape_it++) {
    cout << setprecision(2) << fixed << (*shape_it)->area() << "   ";
  }

  cout << endl << "volume:  ";

  // iterate through vector and get the volume of each shape
  for (auto shape_it = shapes.begin(); shape_it != shapes.end(); shape_it++) {
    cout << setprecision(2) << fixed << (*shape_it)->volume() << "   ";
  }

  // new line after table
  cout << endl << endl << "Prism class (all depths set to 2 for clarity):\n";

  // create prisms vector of base pointers
  vector<Shape *> prisms;

  // create iterator to get 2d shapes from shapes vector
  auto face_it = shapes.begin();

  // create prisms with this 2d face and push them onto the prisms vector
  for (int i{0}; i < 4; i++) {
    prisms.push_back(new Prism{2, *face_it++});
  }

  // output table of prism volumes denoted by face
  cout << "Table of volumes of all prisms (denoted by face):\n"
       << "      rectangle  square  ellipse  circle\nvolume: ";

  // iterate through vector and get the volume of each shape
  for (auto prism_it = prisms.begin(); prism_it != prisms.end(); prism_it++) {
    cout << setprecision(2) << fixed << (*prism_it)->volume() << "    ";
  }

  cout << endl; // newline after the table

  // iterate through vector and free up memory
  for (auto shape_it = shapes.begin(); shape_it != shapes.end(); shape_it++) {
    delete *shape_it;
  }

  // reset vector
  shapes.clear();

  // exit
  return 0;
}
