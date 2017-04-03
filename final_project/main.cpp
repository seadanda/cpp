/* main.cpp: AC Circuit Manipulator main function
 *
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#include <iostream> // std io
#include <vector>   // vector container

#include "capacitor.h" // capacitor class
#include "circuit.h"   // circuit class
#include "component.h" // component base class
#include "inductor.h"  // inductor class
#include "resistor.h"  // resistor class

using namespace std;

void handle_error(const int &err) {
  cerr << "Error: ";
  switch (err) {
  case 1:
    cerr << "not a valid input.\n";
    break;
  default:
    cerr << "an error occurred\n";
    break;
  }
}

int main() {
  // create polymorphic vector of base class pointers
  vector<Component *> components;

  // push components on
  components.push_back(new Resistor{200});
  components.push_back(new Resistor{100, 10});
  components.push_back(new Inductor{100});
  components.push_back(new Inductor{100, 159.15});
  components.push_back(new Capacitor{100});
  components.push_back(new Capacitor{10e-6, 300});

  // go through and test each function
  for (auto it = components.begin(); it != components.end(); it++) {
    cout << (*it)->get_phase_difference() << endl
         << (*it)->get_frequency() << endl
         << (*it)->get_impedance() << endl
         << (*it)->get_mag_impedance() << endl;
  }

  Circuit rc_circuit{159.15};
  rc_circuit.add_component(new Resistor{100});
  rc_circuit.add_component(new Capacitor{10e-6});
  try {
    rc_circuit.connect('f');
  } catch (int &err) {
    handle_error(err);
  }
  rc_circuit.connect('s');

  // exit
  return 0;
}
