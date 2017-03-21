// week7.cpp : Vector manipulator
// Classes to store and manipulate n-dim vectors, 4vectors and particles
// Author:  Dónal Murray
// Date:	20/03/2017

#include <cmath>    // pow, sqrt
#include <iostream> // std io
#include <stdlib.h> // c style exit

using namespace std;

// Vector class which defines addition, subtraction, multiplication
class Vector // Vector class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, Vector &vect1);  // ostreams
  friend istream &operator>>(istream &ins, Vector &vect1); // istreams

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
  double &operator[](const int i) { return data[i]; } // access element
  int get_dimensions() const { return dimensions; }   // no of dimensions

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
ostream &operator<<(ostream &os, Vector &vect1) {
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

// define istream behaviour for Vector
istream &operator>>(istream &is, Vector &vect1) {
  for (int i{0}; i < vect1.get_dimensions(); i++) {
    is >> vect1[i];
    is.ignore(); // ignore the space
  }
  return is;
}

// class for 4-vectors - inherits from Vector
// (ct,x,y,z)
class Fourvector : public Vector // 4-vector class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, Fourvector &fvect1);  // ostreams
  friend istream &operator>>(istream &ins, Fourvector &fvect1); // istreams

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
Fourvector::Fourvector(Fourvector &&fvect2) : Vector(fvect2) {
  // reset fvect2
  fvect2.data = 0;
}

// copy assignment operator
Fourvector &Fourvector::operator=(const Fourvector &fvect2) {
  // use Vector assignment operator to do heavy lifting
  Vector::operator=(fvect2);

  return *this;
}

// move assignment operator
Fourvector &Fourvector::operator=(Fourvector &&fvect2) {
  // use Vector assignment operator to do heavy lifting
  Vector::operator=(fvect2);

  // reset rvalue vector
  fvect2.data = 0;

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
  os << "(";
  for (int i{0}; i < fvect1.get_dimensions(); i++) {
    if (i == fvect1.get_dimensions() - 1) {
      os << fvect1[i] << ")";
    } else {
      os << fvect1[i] << ", ";
    }
  }
  return os;
}

// define istream behaviour
istream &operator>>(istream &is, Fourvector &fvect1) {
  for (int i{0}; i < fvect1.get_dimensions(); i++) {
    is >> fvect1[i];
    is.ignore(); // ignore the space
  }
  return is;
}

// particle class
class Particle // class for particles
{
  // friends of the class
  friend ostream &operator<<(ostream &os, Particle &part1);
  friend istream &operator>>(istream &is, Particle &part1);

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
    momentum[i] = get_gamma() * mass * beta[i];
  }
  return momentum;
}

// define ostream behaviour for particle class
ostream &operator<<(ostream &os, Particle &part1) {
  os << "r = " << part1.position << ", m = " << part1.mass
     << ", B = " << part1.beta;
  return os;
}

// define istream behaviour for particle class
istream &operator>>(istream &is, Particle &part1) {
  is >> part1.position; // read in position vector
  is.ignore();          // ignore separating character
  is >> part1.mass;     // read in mass
  is.ignore();          // ignore separating character
  is >> part1.beta;     // read in beta
  return is;
}

int main() {
  //---show off Vector class---
  // default constructor
  Vector v1;
  cout << "Default constructor: v1 = " << v1 << endl;
  cout << "Enter a 3-vector to fill v1 (comma separated): ";
  cin >> v1;
  cout << v1 << endl;
  // parametrised constructor
  Vector v2{4};
  Vector v3{4};
  cout << "Parametrised constructor: v2 = " << v2 << endl
       << "Enter 2 4d vectors v2 and v3 (comma separated):\nv2: ";
  cin >> v2;
  cout << "v3: ";
  cin >> v3;

  // dot product member function
  cout << "v2 = " << v2 << endl
       << "v3 = " << v3 << endl
       << endl
       << "(v2 . v3) = " << v2.dot_product(v3) << endl;
  //------------------------------

  //---show off 4-vector class---
  //-----------------------------
  Fourvector f1;
  Fourvector f2{1.0, 2.0, 3.0, 4.0};
  Fourvector f3{1.0, v1};

  cout << "4-vector1 = " << f1 << endl
       << "4-vector2 = " << f2 << endl
       << "4-vector3 = " << f3 << endl
       << endl
       << "f2 . f3 = " << f2.dot_product(f3) << endl;

  // lorentz boost f3
  Vector beta1{3};
  cout << "Enter beta (3-vector): ";
  cin >> beta1;
  Fourvector f4{f3.lorentz_boost(beta1)};
  cout << "lorentz boost of f3 by " << beta1 << " = " << f4 << endl;

  //---show off particle class---
  //-----------------------------
  Fourvector r;
  double m;
  Vector B;

  cin >> r;
  cin >> m;
  cin >> B;

  Particle p1{r, m, B};

  cout << p1 << endl;

  // exit
  return 0;
}
