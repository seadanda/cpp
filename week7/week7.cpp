// week7.cpp : Vector manipulator
// Classes to store and manipulate n-dim vectors, 4vectors and particles
// Author:  Dónal Murray
// Date:    20/03/2017

#include <cmath>    // pow, sqrt
#include <iostream> // std io
#include <stdlib.h> // c style exit

using namespace std;

// Vector class which defines addition, subtraction, multiplication
class Vector // Vector class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, const Vector &vect1); // ostreams

protected:
  // member data
  int dimensions;  // number of dimensions
  double *data{0}; // pointer to array where Vector elements are stored

public:
  // default constructor
  Vector();
  // parametrised constructor
  Vector(const int &dim);
  // destructor - free up memory
  ~Vector() { delete[] data; }
  // copy constructor
  Vector(const Vector &vect2);
  // move constructor
  Vector(Vector &&vect2);
  // assignment operator
  Vector &operator=(const Vector &vect2);
  // move assignment operator
  Vector &operator=(Vector &&vect2);

  // accessors
  double &operator[](const int i);                  // access element
  int get_dimensions() const { return dimensions; } // no of dimensions

  // member functions
  double dot_product(const Vector &vect2) const; // calc dot product
};
// end of class

// default constructor
Vector::Vector() : dimensions{3} {
  // create 3d vector and fill with zeroes
  data = new double[dimensions];
  for (int i = 0; i < dimensions; i++) {
    data[i] = 0;
  }
}

// parametrised constructor
Vector::Vector(const int &dim) : dimensions{dim} {
  // create 3d vector and fill with zeroes
  data = new double[dimensions];
  for (int i = 0; i < dimensions; i++) {
    data[i] = 0;
  }
}

// copy constructor
Vector::Vector(const Vector &vect2) : dimensions{vect2.dimensions} {
  data = new double[dimensions];
  // copy data element by element
  for (int i{0}; i < dimensions; i++) {
    data[i] = vect2.data[i];
  }
}

// move constructor
Vector::Vector(Vector &&vect2)
    : data{vect2.data}, dimensions{vect2.dimensions} {
  // reset vect2
  vect2.data = 0;
  vect2.dimensions = 0;
}

// copy assignment operator
Vector &Vector::operator=(const Vector &vect2) {
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
Vector &Vector::operator=(Vector &&vect2) {
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

// overload subscript operator for accessing elements of Vector
double &Vector::operator[](const int i) {
  if ((i < 0) || (i > dimensions)) {
    cerr << "Error: element lies outside array.\n";
    exit(1);
  }
  return data[i];
}

// calc dot product
double Vector::dot_product(const Vector &vect2) const {
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

// define ostream behaviour for Vector
ostream &operator<<(ostream &os, const Vector &vect1) {
  if (vect1.get_dimensions() > 1) {
    os << "(";
  } else {
    os << "empty";
  }
  for (int i{0}; i < vect1.get_dimensions(); i++) {
    if (i == vect1.get_dimensions() - 1) {
      os << vect1.data[i] << ")";
    } else {
      os << vect1.data[i] << ", ";
    }
  }
  return os;
}

// class for 4-vectors - inherits from Vector
// (ct,x,y,z)
class Fourvector : public Vector // 4-vector class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, Fourvector &fvect1); // ostreams

public:
  // default constructor
  Fourvector();
  // parametrised constructors
  Fourvector(const double &t, const double &x, const double &y,
             const double &z);
  Fourvector(const double &t, Vector &r);
  // copy constructor
  Fourvector(const Fourvector &fvect2);
  // move constructor
  Fourvector(Fourvector &&fvect2);
  // copy assignment operator for Fourvector
  Fourvector &operator=(const Fourvector &fvect2);
  // move assignment operator for Fourvector
  Fourvector &operator=(Fourvector &&fvect2);

  // use subscript overload from Vector class
  using Vector::operator[];

  // Fourvector dot product
  double dot_product(const Fourvector &fvect2) const;

  // lorentz boost
  Fourvector lorentz_boost(Vector &beta);
};

// default constructor
Fourvector::Fourvector() : Vector(4) {}

// parametrised constructor with 4 doubles
Fourvector::Fourvector(const double &t, const double &x, const double &y,
                       const double &z)
    : Vector(4) {
  data[0] = t;
  data[1] = x;
  data[2] = y;
  data[3] = z;
}

// parametrised constructor with a double and a Vector vector
Fourvector::Fourvector(const double &t, Vector &r) : Vector(4) {
  data[0] = t;
  data[1] = r[0];
  data[2] = r[1];
  data[3] = r[2];
}

// copy constructor
Fourvector::Fourvector(const Fourvector &fvect2) : Vector(fvect2) {}

// move constructor
Fourvector::Fourvector(Fourvector &&fvect2) : Vector(move(fvect2)) {}

// copy assignment operator
Fourvector &Fourvector::operator=(const Fourvector &fvect2) {
  // use Vector assignment operator to do heavy lifting
  Vector::operator=(fvect2);
  return *this;
}

// move assignment operator
Fourvector &Fourvector::operator=(Fourvector &&fvect2) {
  // use Vector assignment operator to do heavy lifting
  Vector::operator=(move(fvect2));
  return *this;
}

// define dot product for four vectors (ie in minkowski spacetime)
double Fourvector::dot_product(const Fourvector &fvect2) const {
  double result{0};
  if ((dimensions != 4) || (fvect2.dimensions != 4)) {
    cout << "Error: not a 4-vector.\n";
    exit(1);
  }
  result += data[0] * fvect2.data[0]; // add square of timelike
  for (int i{1}; i < dimensions; i++) {
    result -= data[i] * fvect2.data[i]; // subtract square of spacelike
  }
  return result;
}

// lorentz boost
Fourvector Fourvector::lorentz_boost(Vector &beta) {
  // make sure input is valid
  if (beta.get_dimensions() != 3) {
    cerr << "Error: beta must be a 3 dimensional vector.\n";
    exit(1);
  }

  // declare necessary variables
  Fourvector result; // boosted fourvector
  Vector r{3};       // position 3vector
  double gamma;      // lorentz factor

  // get position 3vector from the 4vector
  for (int i{0}; i < 3; i++) {
    r[i] = this->data[i + 1];
  }

  // save space with two definitions
  double beta_sq{beta.dot_product(beta)}; // beta squared
  double beta_r{beta.dot_product(r)};     // dot product of beta and r

  // make sure beta is physical ie no comps > 1 and the square not > 1
  if ((beta_sq >= 1) || (beta[0] >= 1) || (beta[1] >= 1) || (beta[2] >= 1)) {
    cerr << "Error: beta is unphysical (v >= c).\n";
    exit(1);
  }

  // calculate lorentz factor
  gamma = 1 / sqrt(1 - beta_sq);

  // calculate boosted timelike component
  result[0] = gamma * (this->data[0] - beta_r);

  // calculate boosted spacelike components
  for (int i{0}; i < 0; i++) {
    result[i] =
        r[i] +
        ((gamma - 1) * beta_r / beta_sq - gamma * this->data[0]) * beta[i];
  }
  return result;
}

// define ostream behaviour
ostream &operator<<(ostream &os, Fourvector &fvect1) {
  if (fvect1.get_dimensions() > 1) {
    os << "(";
  } else {
    os << "empty";
  }
  for (int i{0}; i < fvect1.get_dimensions(); i++) {
    if (i == fvect1.get_dimensions() - 1) {
      os << fvect1[i] << ")";
    } else {
      os << fvect1[i] << ", ";
    }
  }
  return os;
}

// particle class
class Particle // class for particles
{
  // friends of the class
  friend ostream &operator<<(ostream &os, Particle &part1);

private:
  Fourvector position;
  double mass;
  Vector beta{3};

public:
  // parametrised constructor
  Particle(const Fourvector &r, const double &m, const Vector &B);
  // function to calculate the lorentz factor
  double get_gamma() const;
  // function to return total energy of the particle
  double get_energy();
  // function to return the momentum of the particle
  Vector get_momentum();
};

// parametrised constructor
Particle::Particle(const Fourvector &r, const double &m, const Vector &B)
    : position{r}, mass{m}, beta{B} {}

// function to calculate the lorentz factor
double Particle::get_gamma() const { return sqrt(1 - beta.dot_product(beta)); }

// function to return total energy of the particle
double Particle::get_energy() {
  double energy;
  double mom_sq{(get_momentum()).dot_product(get_momentum())};
  energy = sqrt(pow(mass, 2) + mom_sq);
  return energy;
}
// function to return the momentum of the particle
Vector Particle::get_momentum() {
  Vector momentum{3};
  for (int i{0}; i < 3; i++) {
    // p = g m B
    momentum[i] = get_gamma() * mass * beta[i];
  }
  return momentum;
}

// define ostream behaviour for particle class
ostream &operator<<(ostream &os, Particle &part1) {
  os << endl
     << "r = " << part1.position << endl
     << "m = " << part1.mass << endl
     << "B = " << part1.beta << endl;
  return os;
}

int main() {
  for (int i{0}; i < 20; i++)
    cout << endl; // clear screen for testing TODO remove before submission
  //---show off Vector class---
  cout << "---Vector class---\n";
  // default constructor
  Vector v1;
  cout << "Default constructor: v1 = " << v1 << endl;

  // parametrised constructor
  Vector v2{5};
  cout << "Parametrised constructor with an argument of 5: v2 = " << v2 << endl;

  // copy constructor
  Vector v3{3};
  for (int i{0}; i < 3; i++) {
    v3[i] = 1;
  }
  cout << "\ncopy constructor demo\n";
  cout << "vector v3 = " << v3 << endl;
  Vector v4{v3};
  cout << "vector v4 = " << v4 << endl;
  cout << "vector v3 = " << v3 << " is unchanged.\n";
  cout << "change vector v3 to (2, 2, 2) and show that v4 is unchanged.\n";
  for (int i{0}; i < 3; i++) {
    v3[i] = 2;
  }
  cout << "vector v3 = " << v3 << endl;
  cout << "vector v4 = " << v4 << endl;

  // copy assignment operator
  cout << "\ncopy assignment demo\n";
  Vector v5;
  v5 = v3;
  cout << "vector v5 = " << v5 << endl;
  cout << "vector v3 = " << v3 << " is unchanged.\n";
  cout << "change vector v3 to (3, 3, 3) and show that v5 is unchanged.\n";
  for (int i{0}; i < 3; i++) {
    v3[i] = 3;
  }
  cout << "vector v3 = " << v3 << endl;
  cout << "vector v5 = " << v5 << endl;

  // move constructor
  cout << "\nmove constructor\n";
  cout << "vector v5 = " << v5 << endl;
  cout << "move v5 into a new vector v6, show v5 is empty\n";
  Vector v6{move(v5)};
  cout << "vector v6 = " << v6 << endl;
  cout << "vector v5 = " << v5 << endl;

  // move assignment operator
  cout << "\nmove assignment demo\n";
  Vector v7;
  cout << "vector v7 = " << v7 << endl;
  cout << "vector v6 = " << v6 << endl;
  cout << "set vector v7 equal to v6, show v6 is empty\n";
  v7 = move(v6);
  cout << "vector v7 = " << v7 << endl;
  cout << "vector v6 = " << v6 << endl;

  // accessor
  cout << "\naccessor: v7[1] = " << v7[1] << endl;

  // dot product
  cout << "Dot product of two vectors:\n"
       << "v7 = " << v7 << endl
       << "v4 = " << v4 << endl
       << "(v7 . v4) = " << v7.dot_product(v4) << endl;

  //------------------------------

  //---show off 4-vector class---
  cout << endl << endl << "---4-vector class---\n";
  // parametrised constructor 1 (4 doubles)
  cout << "parametrised constructor with 4 doubles as arguments\n";
  cout << "ct = 2, x = 2, y = 2, z = 2\n";
  Fourvector f1{2, 2, 2, 2};
  cout << "f1 = " << f1 << endl;

  // parametrised constructor 2 (double and 3-vector)
  cout << "parametrised constructor with a double and a 3-vector as "
          "arguments\n";
  cout << "ct = 1, 3-vector = " << v7 << endl;
  Fourvector f2{1, v7};
  cout << "f2 = " << f2 << endl;

  // copy constructor
  Fourvector f3{3, 3, 3, 3};
  cout << "\ncopy constructor demo\n";
  cout << "Fourvector f3 = " << f3 << endl;
  Fourvector f4{f3};
  cout << "Fourvector f4 = " << f4 << endl;
  cout << "Fourvector f3 = " << f3 << " is unchanged.\n";
  cout << "change Fourvector f3 to (4, 4, 4, 4) and show that f4 is "
          "unchanged.\n";
  for (int i{0}; i < 4; i++) {
    f3[i] = 4;
  }
  cout << "Fourvector f3 = " << f3 << endl;
  cout << "Fourvector f4 = " << f4 << endl;

  // copy assignment operator
  cout << "\ncopy assignment demo\n";
  Fourvector f5;
  f5 = f3;
  cout << "Fourvector f5 = " << f5 << endl;
  cout << "Fourvector f3 = " << f3 << " is unchanged.\n";
  cout << "change Fourvector f3 to (5, 5, 5, 5) and show that f5 is "
          "unchanged.\n";
  for (int i{0}; i < 4; i++) {
    f3[i] = 5;
  }
  cout << "Fourvector f3 = " << f3 << endl;
  cout << "Fourvector f5 = " << f5 << endl;

  // move constructor
  cout << "\nmove constructor\n";
  cout << "Fourvector f5 = " << f5 << endl;
  cout << "move f5 into a new Fourvector f6, show f5 is empty\n";
  Fourvector f6{move(f5)};
  cout << "Fourvector f6 = " << f6 << endl;
  cout << "Fourvector f5 = " << f5 << endl;

  // move assignment operator
  cout << "\nmove assignment demo\n";
  Fourvector f7;
  cout << "Fourvector f7 = " << f7 << endl;
  cout << "Fourvector f6 = " << f6 << endl;
  cout << "set Fourvector f7 equal to f6, show f6 is empty\n";
  f7 = move(f6);
  cout << "Fourvector f7 = " << f7 << endl;
  cout << "Fourvector f6 = " << f6 << endl;

  // accessor
  cout << "\naccessor: f7[1] = " << v7[1] << endl;

  // dot product
  cout << "\nDot product of two Fourvectors:\n"
       << "f7 = " << f7 << endl
       << "f4 = " << f4 << endl
       << "(f7 . f4) = " << f7.dot_product(f4) << endl;

  // lorentz boost f3
  cout << "\nlorentz boost\n";
  Vector beta1{3};
  beta1[0] = 0.99; // set beta = (0.99,0,0)
  cout << "lorentz boost 4-vector f3 = " << f3 << " by B = " << beta1 << ":\n"
       << "f3' = " << f3.lorentz_boost(beta1) << endl;
  //-----------------------------

  //---show off particle class---
  cout << endl << endl << "---Particle class---\n";
  Fourvector r{3, 4, 5, 6}; // make a position vector
  double m{0.512e9};        // electron mass in eV
  Vector B{3};              // declare a 3d vector
  B[0] = 0.999;             // set B = (0.999,0,0)
  // parametrised constructor
  Particle p1{r, m, B}; // declare particle with parametrised constructor
  cout << "Parametrised constructor\n"
       << "Particle p1: " << p1 << endl // print it out
       // lorentz factor (gamma)
       << "p1 has:\n"
       << "Lorentz factor = " << p1.get_gamma() << endl
       // total energy
       << "Total energy   = " << p1.get_energy() << endl
       // momentum
       << "Momentum       = " << p1.get_momentum() << endl;

  //-----------------------------

  // exit
  return 0;
}
