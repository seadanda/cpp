/* resistor.cpp
 * Implementation of Resistor class to store and manipulate resistors
 *  Interface:      resistor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "resistor.h"  // resistor class interface
#include "component.h" // component base class
#include <sstream>     // stringstream
#include <string>      // label

int Resistor::resistor_count{0}; // initialise static data member

// parametrised constructor (resistance)
Resistor::Resistor(const double &R) : Component(0, R, "R") {
  resistor_count++;
  // add resistor number to label
  stringstream comp_label;
  comp_label << label << resistor_count;
  label = comp_label.str();
}

// destructor
Resistor::~Resistor() {}

// calculate impedence of component
Complex Resistor::get_impedance(const double &freq) const {
  Complex result; // use complex class
  // Z = R
  result.set_real(value);
  result.set_imaginary(0);
  return result;
}
