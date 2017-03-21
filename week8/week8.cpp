// week8.cpp: Shape manipulator
// Class heirarchy to deal with various 2- and 3D shapes
// Author:  Dónal Murray
// Date:    21/03/2017

#include <iostream> // std io

using namespace std;

class Shape // abstract base class
{
protected:
  int sides_ct;  // number of sides (/specified lengths in case of ellipse etc)
  double *sides; // pointer to array of doubles to store side lengths
public:
  virtual ~Shape() { delete[] sides; }; // destructor
  virtual double area() = 0;            // calculate area
  virtual double volume() = 0;          // calculate volume
};

// 2D shapes
class TwoD : public Shape // abstract derived class for 2d shapes
{};

class Rectangle : public TwoD // derived class for rectangles
{};

class Square : public Rectangle // specialisation of Rectangle for squares
{};

class Ellipse : public TwoD // derived class for ellipses
{};

class Circle : public Ellipse // specialisation of Ellipse for circles
{};

// 3D shapes
class ThreeD : public Shape // abstract derived class for 3d shapes
{};

class Cuboid : public ThreeD // derived class for cuboids
{};

class Cube : public Cuboid // specialisation of Cuboid for cubes
{};

class Ellipsoid : public ThreeD // derived class for ellipsoids
{};

class Sphere : public Ellipsoid // specialisation of Ellipsoid for spheres
{};

int main() {
  cout << "Abandon all hope, ye who enter here.\n";
  return 0;
}
