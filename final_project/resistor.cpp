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

// default constructor
Resistor::Resistor() : Component(0, 0, "R"), resistance{0} {
  resistor_count++;
  // add resistor number to label
  stringstream comp_label;
  comp_label << label << resistor_count;
  label = comp_label.str();
}

// parametrised constructor (resistance)
Resistor::Resistor(const double &R) : Component(0, R, "R"), resistance{R} {
  resistor_count++;
  // add resistor number to label
  stringstream comp_label;
  comp_label << label << resistor_count;
  label = comp_label.str();
}

// destructor
Resistor::~Resistor() { // resistor_count--;
}

// return phase difference of component
double Resistor::get_phase_difference() const { return phase_difference; }

// calculate impedence of component
Complex Resistor::get_impedance(const double &freq) const {
  Complex result; // use complex class
  // Z = R
  result.set_real(resistance);
  result.set_imaginary(0);
  return result;
}

// calculate the magnitude of the impedence
double Resistor::get_mag_impedance(const double &freq) const {
  return (get_impedance(freq)).modulus();
}

// get resistance of component
double Resistor::get_value() const { return resistance; }

// get label
string Resistor::get_label() const { return label; }
