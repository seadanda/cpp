/* component.cpp
 * Implementation of Component abstract base class to serve as a common
 * interface for all components (resistor/capacitor/inductor)
 *  Interface:      component.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "component.h"
#include "complex.h"
#include <iostream>
#include <string>

// parametrised constructor (phase, value, label)
Component::Component(const double &phase, const double &val, const string &lab)
    : phase_difference{phase}, value{val}, label{lab} {}

// return phase difference of component
double Component::get_phase_difference() const { return phase_difference; }

// calculate the magnitude of the impedance
double Component::get_mag_impedance(const double &freq) const {
  return (get_impedance(freq)).modulus();
}
// return label
string Component::get_label() const { return label; }

// rename component
void Component::set_label(const string &lab) { label = lab; }

// overload ostream operator for components
ostream &operator<<(ostream &os, const Component &comp) {
  os << "  " << comp.label << "  ";
  if (comp.label[0] == 'R') {
    os << "Resistor   " << comp.get_value() << "\u03A9";
  } else if (comp.label[0] == 'C') {
    os << "Capacitor  " << comp.get_value() << "\u00B5F";
  } else if (comp.label[0] == 'L') {
    os << "Inductor   " << comp.get_value() << "\u00B5H";
  } else {
    os << "Undefined  N/A";
  }
  return os;
}
