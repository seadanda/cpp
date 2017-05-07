/* capacitor.cpp
 * Implementation of Capacitor class to store and manipulate capacitors
 *  Interface:      capacitor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "capacitor.h" // capacitor class interface
#include "component.h" // component base class
#include <sstream>     // stringstream
#include <string>      // label

int Capacitor::capacitor_count{0}; // define static data member

// default constructor
Capacitor::Capacitor() : Component(-90, 0, "C"), capacitance{0} {
  capacitor_count++;
  // add capacitor number to label
  stringstream comp_label;
  comp_label << label << capacitor_count;
  label = comp_label.str();
}

// constructor
Capacitor::Capacitor(const double &C) : Component(-90, C, "C"), capacitance{C} {
  // increment nr of capacitors
  capacitor_count++;
  // add capacitor number to label
  stringstream comp_label;
  comp_label << label << capacitor_count;
  label = comp_label.str();
}

// destructor
Capacitor::~Capacitor() { capacitor_count--; }

// return phase difference of component
double Capacitor::get_phase_difference() const { return phase_difference; }

// calculate impedence of component
Complex Capacitor::get_impedance() const {
  // TODO
  Complex result;
  result.set_real(1);
  result.set_imaginary(2);
  return result;
}

// calculate the magnitude of the impedence
double Capacitor::get_mag_impedance() const {
  return (get_impedance()).modulus();
}

double Capacitor::get_value() const { return capacitance; }
