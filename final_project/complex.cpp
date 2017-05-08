/* complex.cpp
 * Implementation of Complex class to store and manipulate complex numbers
 *  Interface:      complex.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include <cmath>    // sqrt, pow, atan2
#include <iomanip>  // set precision
#include <iostream> // std io

#include "complex.h" // class interface

// default constructor
Complex::Complex() : real{0}, imaginary{0} {}

// parametrised constructors
Complex::Complex(double re) : real{re}, imaginary{0} {}
Complex::Complex(double re, double im) : real{re}, imaginary{im} {}

// destructor
Complex::~Complex() {}

// modifiers
void Complex::set_real(const double re) { real = re; }
void Complex::set_imaginary(const double im) { imaginary = im; }

// accessors
double Complex::get_real() const { return real; }
double Complex::get_imaginary() const { return imaginary; }

// member functions to return modulus and argument
double Complex::modulus() const {
  return sqrt(pow(real, 2) + pow(imaginary, 2));
}
double Complex::argument() const { return pow(atan2(imaginary, real), 2); }

// function to calculate the complex conjugate of a complex number
Complex Complex::conjugate() const // return complex conjugate
{
  Complex temp{real, imaginary}; // clone input complex number
  temp.set_real(real);
  if (imaginary != 0) {
    // imaginary is not zero, invert the sign
    temp.set_imaginary(-1 * imaginary);
  }
  return temp;
}

// define the addition of two complex numbers
Complex Complex::operator+(const Complex &z2) const // return sum
{
  Complex temp{real + z2.real, imaginary + z2.imaginary};
  return temp;
}

// define the subtraction of two complex numbers
Complex Complex::operator-(const Complex &z2) const // return difference
{
  Complex temp{real - z2.real, imaginary - z2.imaginary};
  return temp;
}

// define the product of two complex numbers
Complex Complex::operator*(const Complex &z2) const // return product
{
  // x*y = (Re{x}*Re{y} - Im{x}*Im{y}) + i(Re{x}*Im{y}+Im{x}*Im{y})
  Complex temp{real * z2.real - imaginary * z2.imaginary,
               real * z2.imaginary + imaginary * z2.real};
  return temp;
}

// define the quotient of two complex numbers
Complex Complex::operator/(const Complex &z2) const // return quotient
{
  // x/y = x * conjugate(y) / modulus(y)
  double denom{z2.modulus()}; // denominator
  double re{(real * z2.real + imaginary * z2.imaginary) / denom};
  double im{(imaginary * z2.real - real * z2.imaginary) / denom};
  Complex temp{re, im};
  return temp;
}

// define how complex numbers are inserted into an ostream
ostream &operator<<(ostream &os, const Complex &z) // define ostream behaviour
{
  if (z.imaginary < 0) {
    // negative, minus already included in double
    os << z.real << z.imaginary << "i";
  } else {
    // positive or zero, insert + sign
    os << z.real << "+" << z.imaginary << "i";
  }
  return os;
}

// define how complex numbers are read from an istream
istream &operator>>(istream &is, Complex &z) // define istream behaviour
{
  double re; // real part
  double im; // imaginary part
  char sign; // sign of imaginary part (+/-)

  is >> re    // read first number
      >> sign // read sign of imaginary part
      >> im;  // read second number
  if (is.fail()) {
    // i is before the imaginary part, ignore it and read in the imaginary part
    is.clear();  // clear the fail bit
    is.ignore(); // ignore the i
    is >> im;    // read second number
  } else {
    // i is after imaginary part. ignore it to clear the stream
    is.ignore();
  }

  // a+ib a-ib
  // a+bi a-bi
  // set value of real part
  z.set_real(re);

  // set value of imaginary part depending on the sign
  if ((sign == '+') || (im == 0)) {
    // imaginary part is positive or zero
    z.set_imaginary(im);
  } else {
    // imaginary part is negative
    z.set_imaginary(-1 * im);
  }

  return is;
}
