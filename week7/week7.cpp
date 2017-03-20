// week7.cpp : Cartesian manipulator
// Classes to store and manipulate n-dim vectors, 4vectors and particles
// Author:  Dónal Murray
// Date:	20/03/2017

#include <cmath>    // pow, sqrt
#include <iostream> // std io

using namespace std;

// Cartesian class which defines addition, subtraction, multiplication and
// iostream
// behaviour
class Cartesian // Cartesian class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, Cartesian &vect1);  // ostreams
  friend istream &operator>>(istream &ins, Cartesian &vect1); // istreams

private:
  // member data
  int dim_ct;      // number of dimensions
  double *data{0}; // pointer to array where Cartesian elements are stored

public:
  // default constructor
  Cartesian();
  // parametrised constructor
  Cartesian(const int &dim);
  // destructor - free up memory
  ~Cartesian() { delete[] data; }
  // copy constructor
  Cartesian(const Cartesian &vect1);
  // move constructor
  Cartesian(Cartesian &&vect1);
  // assignment operator
  Cartesian &operator=(const Cartesian &vect1);
  // move assignment operator
  Cartesian &operator=(Cartesian &&vect1);

  // accessors
  int get_dim_ct() const { return dim_ct; } // no of dimensions

  // overloaded operators
  Cartesian operator+(const Cartesian &vect1) const; // addition
  Cartesian operator-(const Cartesian &vect1) const; // subtraction
  Cartesian operator*(const Cartesian &vect1) const; // multiplication
  double &operator[](const int i) { return data[i]; }
};
// end of class

// default constructor
Cartesian::Cartesian() : dim_ct{3} {
  // create 3d vector and fill with zeroes
  data = new double[dim_ct];
  for (int i = 0; i < dim_ct; i++) {
    data[i] = 0;
  }
}

// parametrised constructor
Cartesian::Cartesian(const int &dim) : dim_ct{dim} {
  // create 3d vector and fill with zeroes
  data = new double[dim_ct];
  for (int i = 0; i < dim_ct; i++) {
    data[i] = 0;
  }
}

// copy constructor
Cartesian::Cartesian(const Cartesian &vect1) : dim_ct{vect1.dim_ct} {
  data = new double[dim_ct];
  // copy data element by element
  for (int i{0}; i < dim_ct; i++) {
    data[i] = vect1.data[i];
  }
}

// move constructor
Cartesian::Cartesian(Cartesian &&vect1)
    : data{vect1.data}, dim_ct{vect1.dim_ct} {
  // reset vect1
  vect1.data = 0;
  vect1.dim_ct = 0;
}

// define ostream behaviour
ostream &operator<<(ostream &os, Cartesian &vect1) {
  os << "(";
  for (int i{0}; i < vect1.get_dim_ct(); i++) {
    if (i == vect1.get_dim_ct() - 1) {
      os << vect1[i] << ")";
    } else {
      os << vect1[i] << ", ";
    }
  }
  return os;
}

// define istream behaviour
istream &operator>>(istream &is, Cartesian &vect1) {
  for (int i{0}; i < vect1.get_dim_ct(); i++) {
    is >> vect1[i];
    is.ignore(); // ignore the space
  }
  return is;
}

int main() {
  //------------------------------
  //---show off cartesian class---
  //------------------------------
  // default constructor
  Cartesian v1;
  cout << "Default constructor: v1 = " << v1 << endl;

  // parametrised constructor
  Cartesian v2{4};
  cout << "Parametrised constructor: v2 = " << v2 << endl;
  cout << "Enter a 4d vector to fill v2 (comma separated): ";
  cin >> v2;
  cout << "v2 = " << v2 << endl;

  return 0;
}
