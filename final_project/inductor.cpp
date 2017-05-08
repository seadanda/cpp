/* inductor.cpp
 * Implementation of Inductor class to store and manipulate inductors
 *  Interface:      Inductor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "inductor.h"  // Inductor class interface
#include "component.h" // component base class
#include <sstream>     // stringstream
#include <string>      // label

int Inductor::inductor_count{0}; // initialise static data member

// default constructor
Inductor::Inductor() : Component(90, 0, "L"), inductance{0} {
  inductor_count++;
  // add inductor number to label
  stringstream comp_label;
  comp_label << label << inductor_count;
  label = comp_label.str();
}

// parametrised constructor
Inductor::Inductor(const double &L) : Component(90, L, "L"), inductance{L} {
  inductor_count++;
  // add inductor number to label
  stringstream comp_label;
  comp_label << label << inductor_count;
  label = comp_label.str();
}

// destructor
Inductor::~Inductor() {}

// return phase difference of component
double Inductor::get_phase_difference() const { return phase_difference; }

// calculate impedance of inductor
Complex Inductor::get_impedance(const double &freq) const {
  Complex result; // use complex class
  // Z = jwL
  result.set_real(0);
  result.set_imaginary(freq * inductance / 1e6);
  return result;
}

// calculate the magnitude of the impedance
double Inductor::get_mag_impedance(const double &freq) const {
  return (get_impedance(freq)).modulus();
}

// return inductance of inductor
double Inductor::get_value() const { return inductance; }

// return label
string Inductor::get_label() const { return label; }
