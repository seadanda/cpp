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

// exception handling
void error(const int &err) {
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

// outstream function template
ostream &operator<<(ostream &os, Component &comp) {
  os << "  " << comp.label << "      ";
  if (comp.label[0] == 'R') {
    os << "Resistor   " << comp.get_value() << " \u03A9";
  } else if (comp.label[0] == 'C') {
    os << "Capacitor  " << comp.get_value() << " F";
  } else if (comp.label[0] == 'L') {
    os << "Inductor   " << comp.get_value() << " H";
  } else {
    os << "Undefined  N/A";
  }
  return os;
}

// function to iterate through component library and and print the components
void print_library(const vector<Component *> &lib) {
  cout << "-------Component library-------\n";
  cout << "| Label   Component   Value   |\n-------------------------------\n";
  for (auto it = lib.begin(); it != lib.end(); it++) {
    cout << **it << endl;
  }
  cout << "-------------------------------\n";
}

int main() {
  // create polymorphic vector of base class pointers
  vector<Component *> component_library;

  // push component_library on
  component_library.push_back(new Resistor{200});
  component_library.push_back(new Resistor{100, 10});
  component_library.push_back(new Inductor{100});
  component_library.push_back(new Inductor{100, 159.15});
  component_library.push_back(new Capacitor{100});
  component_library.push_back(new Capacitor{10e-6, 300});

  // print out library
  print_library(component_library);

  Circuit rc_circuit{159.15};
  rc_circuit.add_component(new Resistor{100});
  rc_circuit.add_component(new Capacitor{10e-6});

  // incorrect input
  try {
    rc_circuit.connect('f');
  } catch (int &err) {
    error(err);
  }

  try {
    rc_circuit.connect('s');
  } catch (int &err) {
    error(err);
  }

  try {
    rc_circuit.connect('p');
  } catch (int &err) {
    error(err);
  }

  // iterate through vector and free up memory
  for (auto comp_it = component_library.begin();
       comp_it != component_library.end(); comp_it++) {
    delete *comp_it;
  }

  // reset vector
  component_library.clear();

  // exit
  return 0;
}
