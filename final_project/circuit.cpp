/* circuit.cpp
 * Implementation of Circuit class to store and manipulate circuits
 *  Interface:      circuit.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include <iostream>
#include <sstream>
#include <vector>

#include "circuit.h" // class interface

#include "capacitor.h" // capacitor class
#include "complex.h"   // complex class
#include "component.h" // component base class
#include "inductor.h"  // inductor class
#include "resistor.h"  // resistor class

int Circuit::circuit_count{0}; // initialise static data member

// default constructor
Circuit::Circuit() : frequency{0} {
  circuit_count++;
  // add circuit number to label
  stringstream comp_label;
  comp_label << label << circuit_count;
  label = comp_label.str();
}

// parametrised constructor (frequency)
Circuit::Circuit(const double &freq, const string &lab)
    : frequency{freq}, label(lab) {
  circuit_count++;
  // add circuit number to label
  stringstream comp_label;
  comp_label << label << circuit_count;
  label = comp_label.str();
}

// destructor
Circuit::~Circuit() {
  // delete the components container - memory for components will be freed when
  // the component library is freed up
  components.clear();
  // delete the subcircuits container - memory for the subcircuits will be freed
  // when the circuit library is freed up
  subcircuits.clear();
}

double Series::get_frequency() const { return frequency; }
double Parallel::get_frequency() const { return frequency; }

// change the frequency
void Series::set_frequency(const double &freq) {
  // change frequency of circuit
  frequency = freq;
  // change frequency of all subcircuits
  for (auto it = subcircuits.begin(); it != subcircuits.end(); it++) {
    (*it)->set_frequency(freq);
  }
}

// change the frequency
void Parallel::set_frequency(const double &freq) {
  // change frequency of circuit
  frequency = freq;
  // change frequency of all subcircuits
  for (auto it = subcircuits.begin(); it != subcircuits.end(); it++) {
    (*it)->set_frequency(freq);
  }
}

// add component (component)
void Series::add_component(Component *new_comp) {
  components.push_back(new_comp);
}

void Parallel::add_component(Component *new_comp) {
  components.push_back(new_comp);
}

// calculate the magnitude of the impedance of the circuit
double Series::get_mag_impedance() { return 0; }
double Parallel::get_mag_impedance() { return 0; }

// overload ostream operator for circuits
ostream &operator<<(ostream &os, const Circuit &circ) {
  os << circ.label << "(" << circ.frequency << "Hz)   ( ";
  for (auto it : circ.components) {
    os << it->get_label() << " ";
  }
  for (auto it : circ.subcircuits) {
    os << it << " ";
  }
  os << ")\n";
  return os;
}

// get label
string Series::get_label() { return label; }
string Parallel::get_label() { return label; }

//---Series
Series::Series(const double &freq) : Circuit(freq, "S") {}
// calculate the impedence of the whole circuit
Complex Series::get_impedance() {
  Complex temp{0};
  for (auto it = components.begin(); it != components.end(); it++) {
    temp = temp + (*it)->get_impedance(frequency);
  }
  for (auto it = subcircuits.begin(); it != subcircuits.end(); it++) {
    temp = temp + (*it)->get_impedance();
  }
  return temp;
}

//---Parallel
Parallel::Parallel(const double &freq) : Circuit(freq, "P") {}
// calculate the impedence of the whole circuit
Complex Parallel::get_impedance() {
  Complex temp{0, 0};
  for (auto it = components.begin(); it != components.end(); it++) {
    temp = temp + ((*it)->get_impedance(frequency)).conjugate() /
                      ((*it)->get_impedance(frequency)).modulus();
  }
  for (auto it = subcircuits.begin(); it != subcircuits.end(); it++) {
    temp = temp + ((*it)->get_impedance()).conjugate() /
                      ((*it)->get_impedance()).modulus();
  }
  return temp;
}
