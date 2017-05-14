/* inductor.cpp
 * Implementation of Inductor class to store and manipulate inductors
 *  Interface:      Inductor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include <sstream> // stringstream
#include <string>  // label

#define _USE_MATH_DEFINES // M_PI
#include <math.h>         // M_PI

#include "component.h" // component base class
#include "inductor.h"  // Inductor class interface

int Inductor::inductor_count{0}; // initialise static data member

// parametrised constructor
Inductor::Inductor(const double &L) : Component(90, L, "L") {
  inductor_count++;
  // add inductor number to label
  stringstream comp_label;
  comp_label << label << inductor_count;
  label = comp_label.str();
}

// destructor
Inductor::~Inductor() {}

// calculate impedance of inductor
Complex Inductor::get_impedance(const double &freq) const {
  Complex result; // use complex class
  // Z = jwL
  result.set_real(0);
  result.set_imaginary(2 * M_PI * freq * value / 1e6);
  return result;
}
