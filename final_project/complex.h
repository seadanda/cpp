/* complex.h
 * Interface for Complex class to store and manipulate complex numbers
 *  Implementation: complex.cpp
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream> // i/ostream types

using namespace std;

class Complex // class for complex numbers
{
  // friend functions to overload << and >> to define iostream behaviour
  friend ostream &operator<<(ostream &os, const Complex &z); // ostreams
  friend istream &operator>>(istream &is, Complex &z);       // istreams

private:
  // member data
  double real;      // real part
  double imaginary; // imaginary part

public:
  // default constructor
  Complex();
  // parametrised constructor
  Complex(double re, double im);
  // destructor
  ~Complex();

  // modifiers
  void set_real(const double re);
  void set_imaginary(const double im);

  // accessors
  double get_real() const;
  double get_imaginary() const;

  // member functions
  double modulus() const;    // return modulus
  double argument() const;   // return argument
  Complex conjugate() const; // return conjugate

  // overload +-*/ operators
  Complex operator+(const Complex &z2) const;
  Complex operator-(const Complex &z2) const;
  Complex operator*(const Complex &z2) const;
  Complex operator/(const Complex &z2) const;
};

#endif
