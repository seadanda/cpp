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

// not in circuit (no frequency)
Inductor::Inductor(const double &L) : Component(90, L, "L"), inductance{L} {
  inductor_count++;
  // add inductor number to label
  stringstream comp_label;
  comp_label << label << inductor_count;
  label = comp_label.str();
}

// in circuit (freq specified)
Inductor::Inductor(const double &L, const double &freq)
    : Component(90, L, freq, "L"), inductance{L} {
  inductor_count++;
  // add inductor number to label
  stringstream comp_label;
  comp_label << label << inductor_count;
  label = comp_label.str();
}

// destructor
Inductor::~Inductor() { inductor_count--; }

// set frequency of component (frequency)
void Inductor::set_frequency(const double &freq) { frequency = freq; }

// return frequency of component
double Inductor::get_frequency() const { return frequency; }

// return phase difference of component
double Inductor::get_phase_difference() const { return phase_difference; }

// calculate impedence of component
Complex Inductor::get_impedance() const {
  // TODO
  Complex result;
  result.set_real(1);
  result.set_imaginary(2);
  return result;
}

// calculate the magnitude of the impedence
double Inductor::get_mag_impedance() const {
  return (get_impedance()).modulus();
}

double Inductor::get_value() const { return inductance; }
