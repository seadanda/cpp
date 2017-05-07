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

// not in circuit (no frequency)
Resistor::Resistor(const double &R) : Component(0, R, "R"), resistance{R} {
  resistor_count++;
  // add resistor number to label
  stringstream comp_label;
  comp_label << label << resistor_count;
  label = comp_label.str();
}

// in circuit (freq specified)
Resistor::Resistor(const double &R, const double &freq)
    : Component(0, R, freq, "R") {
  resistor_count++;
  // add resistor number to label
  stringstream comp_label;
  comp_label << label << resistor_count;
  label = comp_label.str();
}

// destructor
Resistor::~Resistor() { resistor_count--; }

// set frequency of component (frequency)
void Resistor::set_frequency(const double &freq) { frequency = freq; }

// return frequency of component
double Resistor::get_frequency() const { return frequency; }

// return phase difference of component
double Resistor::get_phase_difference() const { return phase_difference; }

// calculate impedence of component
Complex Resistor::get_impedance() const {
  // TODO
  Complex result;
  result.set_real(1);
  result.set_imaginary(2);
  return result;
}

// calculate the magnitude of the impedence
double Resistor::get_mag_impedance() const {
  return (get_impedance()).modulus();
}

// get resistance of component
double Resistor::get_value() const { return resistance; }
