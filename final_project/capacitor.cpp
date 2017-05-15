/* capacitor.cpp
 * Implementation of Capacitor class to store and manipulate capacitors
 *  Interface:      capacitor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include <sstream> // stringstream
#include <string>  // labels

#define _USE_MATH_DEFINES // M_PI
#include <math.h>         // M_PI

#include "capacitor.h" // capacitor class interface
#include "circuit.h"   // circuit class
#include "component.h" // component base class

int Capacitor::capacitor_count{0}; // define static data member

// constructor(freq,value,label)
Capacitor::Capacitor(const double &C) : Component(-90, C, "C") {
  // increment nr of capacitors
  capacitor_count++;
  // add capacitor number to label
  stringstream comp_label;
  comp_label << label << capacitor_count;
  label = comp_label.str();
}

// destructor
Capacitor::~Capacitor() { // capacitor_count--;
}

// calculate impedence of capacitor
Complex Capacitor::get_impedance(const double &freq) const {
  Complex result; // use complex class
  // Z = 1/jwC
  Complex one{1, 0};
  if ((freq == 0) || (value == 0)) {
    cerr << "Error: cannot divide by 0\n";
    result.set_real(0);
    result.set_imaginary(0);
  } else {
    result.set_real(0);
    result.set_imaginary(2 * M_PI * freq * value / 1e6);
    result = result;
  }
  return one / result;
}
