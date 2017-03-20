// week7.cpp : Cartesian manipulator
// Classes to store and manipulate n-dim vectors, 4vectors and particles
// Author:  Dónal Murray
// Date:	20/03/2017

#include <cmath>    // pow, sqrt
#include <iostream> // std io
#include <stdlib.h> // c style exit

using namespace std;

// Cartesian class which defines addition, subtraction, multiplication
class Cartesian // Cartesian class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, Cartesian &vect1);  // ostreams
  friend istream &operator>>(istream &ins, Cartesian &vect1); // istreams

protected:
  // member data
  int dimensions;  // number of dimensions
  double *data{0}; // pointer to array where Cartesian elements are stored

public:
  // default constructor
  Cartesian();
  // parametrised constructor
  Cartesian(const int &dim);
  // destructor - free up memory
  ~Cartesian() { delete[] data; }
  // copy constructor
  Cartesian(const Cartesian &vect2);
  // move constructor
  Cartesian(Cartesian &&vect2);
  // assignment operator
  Cartesian &operator=(const Cartesian &vect2);
  // move assignment operator
  Cartesian &operator=(Cartesian &&vect2);

  // accessors
  double &operator[](const int i) { return data[i]; } // access element
  int get_dimensions() const { return dimensions; }   // no of dimensions

  // member functions
  double dot_product(const Cartesian &vect2) const; // calc dot product
};
// end of class

// default constructor
Cartesian::Cartesian() : dimensions{3} {
  // create 3d vector and fill with zeroes
  data = new double[dimensions];
  for (int i = 0; i < dimensions; i++) {
    data[i] = 0;
  }
}

// parametrised constructor
Cartesian::Cartesian(const int &dim) : dimensions{dim} {
  // create 3d vector and fill with zeroes
  data = new double[dimensions];
  for (int i = 0; i < dimensions; i++) {
    data[i] = 0;
  }
}

// copy constructor
Cartesian::Cartesian(const Cartesian &vect2) : dimensions{vect2.dimensions} {
  data = new double[dimensions];
  // copy data element by element
  for (int i{0}; i < dimensions; i++) {
    data[i] = vect2.data[i];
  }
}

// move constructor
Cartesian::Cartesian(Cartesian &&vect2)
    : data{vect2.data}, dimensions{vect2.dimensions} {
  // reset vect2
  vect2.data = 0;
  vect2.dimensions = 0;
}

// copy assignment operator
Cartesian &Cartesian::operator=(const Cartesian &vect2) {
  // no self assignment
  if (&vect2 == this)
    return *this;

  // delete old array and change member data
  delete[] data;
  dimensions = vect2.dimensions;

  // make and fill new array
  data = new double[vect2.dimensions];
  for (int i = 0; i < dimensions; i++) {
    data[i] = vect2.data[i];
  }

  return *this;
}

// move assignment operator
Cartesian &Cartesian::operator=(Cartesian &&vect2) {
  // no self assignment
  if (&vect2 == this)
    return *this;

  // delete old array and change member data
  delete[] data;
  dimensions = vect2.dimensions;

  // make and fill new array
  data = new double[vect2.dimensions];
  for (int i = 0; i < dimensions; i++) {
    data[i] = vect2.data[i];
  }

  // reset rvalue vector
  vect2.dimensions = 0;
  vect2.data = 0;

  return *this;
}

// calc dot product
double Cartesian::dot_product(const Cartesian &vect2) const {
  double result{0};
  if (dimensions != vect2.dimensions) {
    cout << "Error: vectors must be same length.\n";
    exit(1);
  }
  for (int i{0}; i < dimensions; i++) {
    result += data[i] * vect2.data[i];
  }
  return result;
}

// define ostream behaviour
ostream &operator<<(ostream &os, Cartesian &vect1) {
  os << "(";
  for (int i{0}; i < vect1.get_dimensions(); i++) {
    if (i == vect1.get_dimensions() - 1) {
      os << vect1[i] << ")";
    } else {
      os << vect1[i] << ", ";
    }
  }
  return os;
}

// define istream behaviour
istream &operator>>(istream &is, Cartesian &vect1) {
  for (int i{0}; i < vect1.get_dimensions(); i++) {
    is >> vect1[i];
    is.ignore(); // ignore the space
  }
  return is;
}

// class for 4-vectors - inherits from Cartesian
// (ct,x,y,z)
class Fourvector : public Cartesian // 4-vector class
{
protected:
  int dimensions{4}; // number of dimensions fixed at 4

public:
  // parametrised constructors
  Fourvector(const double &t, const double &x, const double &y,
             const double &z);
  Fourvector(const double &t, const Cartesian &r);
  // destructor
  ~Fourvector();
  using Cartesian::operator=;
};

Fourvector::Fourvector

    int
    main() {
  //---show off cartesian class---
  // default constructor
  Cartesian v1;
  cout << "Default constructor: v1 = " << v1 << endl;
  cout << "Enter a 3-vector to fill v1 (comma separated): " cin >> v1;

  // parametrised constructor
  Cartesian v2{4};
  Cartesian v3{4};
  cout << "Parametrised constructor: v2 = " << v2 << endl
       << "Enter 2 4d vectors v2 and v3 (comma separated):\nv2: ";
  cin >> v2;
  cout << "v3: ";
  cin >> v3;

  // dot product member function
  cout << "v2 = " << v2 << endl
       << "v3 = " << v3 << endl
       << "(v2 . v3) = " << v2.dot_product(v3) << endl;
  //------------------------------

  //---show off 4-vector class---
  //-----------------------------
  Fourvector four1{2, 3, 4, 5};
  Fourvector four2{4, v1};

  cout << "4-vector1 = " << four1 << endl << "4-vector2 = " << four2 << endl;

  //---show off particle class---
  //-----------------------------

  // exit
  return 0;
}
