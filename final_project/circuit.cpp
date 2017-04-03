/* circuit.cpp
 * Implementation of Circuit class to store and manipulate circuits
 *  Interface:      circuit.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include <vector>

#include "circuit.h" // class interface

#include "capacitor.h" // capacitor class
#include "complex.h"   // complex class
#include "component.h" // component base class
#include "inductor.h"  // inductor class
#include "resistor.h"  // resistor class

// default constructor
Circuit::Circuit() : frequency{0} {}

// parametrised constructor (frequency)
Circuit::Circuit(const double &freq) : frequency(freq) {}

// destructor
Circuit::~Circuit() {
  // interate through components vector and free up memory
  for (auto c_it = components.begin(); c_it != components.end(); c_it++) {
    delete *c_it;
  }
  // delete the components container
  components.clear();
  // interate through subcircuits vector and free up memory
  for (auto s_it = subcircuits.begin(); s_it != subcircuits.end(); s_it++) {
    delete *s_it;
  }
  // delete the subcircuits container
  subcircuits.clear();
}

// change the frequency
void Circuit::set_frequency(const double &freq) {
  // change frequency of circuit
  frequency = freq;
  // change frequency of all components
  for (auto it = components.begin(); it != components.end(); it++) {
    (*it)->set_frequency(freq);
  }
  // change frequency of all subcircuits
  for (auto it = subcircuits.begin(); it != subcircuits.end(); it++) {
    (*it)->set_frequency(freq);
  }
}

// add component (component)
void Circuit::add_component(Component *new_comp) {
  components.push_back(new_comp);
}

// connect components in series (s) or parallel (p)
void Circuit::connect(const char &type) {
  connection_type = type;
  if (connection_type == 's') {
    // connect in series
    cout << "woo\n";
  } else if (connection_type == 'p') {
    // connect in parallel
  } else {
    throw(1);
  }
}
