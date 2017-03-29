// Assignment 5
// Write a C++ class to store complex numbers

#include <cmath>    // sqrt, pow, atan2
#include <iomanip>  // set precision
#include <iostream> // std io
#include <vector>   // vector class

using namespace std;

class Complex // class for complex numbers
{
  // friends of the class
  friend ostream &operator<<(ostream &outs, const Complex &z);
  friend Complex operator>>(istream &ins, Complex &z);

private:
  // member data
  double real;      // real part
  double imaginary; // imaginary part

public:
  // default constructor
  Complex() : real{0}, imaginary{0} {}
  // parametrised constructor
  Complex(double re, double im) : real{re}, imaginary{im} {}
  // destructor
  ~Complex() {}

  // modifiers
  void set_real(const double re) { real = re; }
  void set_imaginary(const double im) { imaginary = im; }

  // accessors
  double get_real() const { return real; }
  double get_imaginary() const { return imaginary; }

  // member functions to return modulus and argument
  double get_modulus() const { return sqrt(pow(real, 2) + pow(imaginary, 2)); }
  double get_argument() const { return pow(atan2(imaginary, real), 2); }

  // member function to return complex conjugate
  Complex get_conjugate() const;

  // member functions to overload + and - operators
  Complex operator+(const Complex &z2) const;
  Complex operator-(const Complex &z2) const;

  // member functions to overload * and / operators
  Complex operator*(const Complex &z2) const;
  Complex operator/(const Complex &z2) const;
}; // end of class

// function to return the complex conjugate of a complex number
Complex Complex::get_conjugate() const // return complex conjugate
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
  Complex tempz{real + z2.real, imaginary + z2.imaginary};
  return tempz;
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
  double denom{z2.get_modulus()}; // denominator
  double re{(real * z2.real + imaginary * z2.imaginary) / denom};
  double im{(imaginary * z2.real - real * z2.imaginary) / denom};
  Complex temp{re, im};
  return temp;
}

// define how complex numbers are inserted into an ostream
ostream &operator<<(ostream &outs, const Complex &z) // define ostream behaviour
{
  if (z.imaginary < 0) {
    // negative, minus already included in double
    outs << z.real << z.imaginary << "i";
  } else {
    // positive or zero, insert + sign
    outs << z.real << "+" << z.imaginary << "i";
  }
}

// define how complex numbers are read from an istream
Complex operator>>(istream &ins, Complex &z) // define istream behaviour
{
  double re; // real part
  double im; // imaginary part
  char sign; // sign of imaginary part (+/-)

  ins >> re   // read first number
      >> sign // read sign of imaginary part
      >> im;  // read second number
  if (ins.fail()) {
    // i is before the imaginary part, ignore it and read in the imaginary part
    ins.clear();  // clear the fail bit
    ins.ignore(); // ignore the i
    ins >> im;    // read second number
  } else {
    // i is after imaginary part. ignore it to clear the stream
    ins.ignore();
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
}

int main() // main
{
  // declare two complex numbers using the parametrised constructor
  Complex z1(3, 4);
  Complex z2(1, -2);

  // push complex numbers onto vector of zs
  vector<Complex *> zs;
  zs.push_back(&z1);
  zs.push_back(&z2);

  // show off overloaded operators +-*/
  cout << "z1 = " << z1 << endl
       << "z2 = " << z2 << endl
       << "    z1 + z2 = " << (z1 + z2) << endl
       << "    z1 - z2 = " << (z1 - z2) << endl
       << "    z1 x z2 = " << (z1 * z2) << endl
       << "    z1 / z2 = " << setprecision(3) << (z1 / z2) << endl;

  // read in two new complex numbers and do it all again
  Complex z3;
  Complex z4;
  cout << "Enter two more complex numbers and watch the magic happen...\nz3 = ";
  cin >> z3;
  cout << "z4 = ";
  cin >> z4;

  // show off all the pretty operators again
  cout << "    z3 + z4 = " << (z3 + z4) << endl
       << "    z3 - z4 = " << (z3 - z4) << endl
       << "    z3 x z4 = " << (z3 * z4) << endl
       << "    z3 / z4 = " << setprecision(3) << (z3 / z4) << endl;

  // push z3 and z4 onto the vector of zs
  zs.push_back(&z3);
  zs.push_back(&z4);

  // iterate through the vector of complex numbers and print the data
  int i{1}; // for labelling each complex number
  for (auto it = zs.begin(); it != zs.end(); it++) {
    // skip line
    cout << endl
         // print complex number
         << "z" << i << "=" << *(*it) << endl
         // print real part
         << "Re{z" << i << "}=" << (*it)->get_real() << endl
         // print imaginary part
         << "Im{z" << i << "}=" << (*it)->get_imaginary() << endl
         // print modulus
         << "Mod{z" << i << "}=" << (*it)->get_modulus() << endl
         // print argument
         << "Arg{z" << i << "}=" << setprecision(3) << (*it)->get_argument()
         << " rad." << endl
         // print conjugate
         << "z" << i << "*=" << (*it)->get_conjugate() << endl;
    // increment label for next z
    i++;
  }

  // exit
  return 0;
}
