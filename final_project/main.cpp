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

  // exit
  return 0;
}
