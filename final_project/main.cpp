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
#include "main.h"      // libs namespace
#include "resistor.h"  // resistor class

using namespace std;
using namespace libs;

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
    os << "Capacitor  " << comp.get_value() << " \u00B5F";
  } else if (comp.label[0] == 'L') {
    os << "Inductor   " << comp.get_value() << " \u00B5H";
  } else {
    os << "Undefined  N/A";
  }
  return os;
}

// function to iterate through component library and and print the components
void print_comp_library();

// function to create a circuit
void create_circuit(const vector<Component *> &lib) {
  cout << "--------Circuit Creator--------\n"
       << "function to create a circuit\n";
}

int main() {
  // draw main menu
  bool quit_main{false};
  while (!quit_main) {
    cout << "-----------Main Menu-----------\n"
         << "Select an option:\n"
         << "1     Component menu\n"
         << "2     Circuit menu\n"
         << "3     Calculations menu\n"
         << "0     Quit\n"
         << "-------------------------------\n"
         << "Option: ";
    int main_choice;
    cin >> main_choice;
    switch (main_choice) {
    case 0:
      cout << "Exit\n";
      quit_main = true;
      break;
    case 1:
      print_comp_library();
      break;
    /*while (!quit_comp) {
      cout << "--------Component menu--------\n"
           << "Select an option:\n"
           << "1     Add a component to library\n"
           << "2     Edit a component\n"
           << "0     Quit\n"
           << "-------------------------------\n"
           << "Option: ";
      int comp_choice;
      cin >> comp_choice;
      switch (comp_choice) {
      case 0:
        cout << "Exit\n";
        quit_comp = true;
        break;
      }*/
    case 2:
      cout << "--------Circuit menu--------\n"
           << "Select an option:\n"
           << "1     Component menu\n"
           << "2     Circuit menu\n"
           << "0     Quit\n"
           << "-------------------------------\n"
           << "Option: ";
      cout << "Add components\n";
      // add a few sample components to library
      component_library.push_back(new Resistor{200});
      component_library.push_back(new Resistor{100, 10});
      component_library.push_back(new Inductor{100});
      component_library.push_back(new Inductor{100, 159.15});
      component_library.push_back(new Capacitor{100});
      component_library.push_back(new Capacitor{10e-6, 300});
      break;
    case 3:
      cout << "Edit component\n";
      break;
    case 4:
      cout << "Delete component\n";
      break;
    case 5:
      cout << "Create circuit\n";
      circuit_library.push_back(new Circuit{159.15});
      (*(circuit_library.begin()))->add_component(new Resistor{100});
      (*(circuit_library.begin()))->add_component(new Capacitor{10e-6});

      break;
    default:
      cout << "Please choose a valid option\n";
      break;
    }
  }

  // iterate through vectors and free up memory
  for (auto comp_it = component_library.begin();
       comp_it != component_library.end(); comp_it++) {
    delete *comp_it;
  }

  for (auto circ_it = circuit_library.begin(); circ_it != circuit_library.end();
       circ_it++) {
    delete *circ_it;
  }

  // clear vectors
  component_library.clear();
  circuit_library.clear();

  // exit
  return 0;
}

// function to iterate through component library and and print the components
void print_comp_library() {
  cout << "-------Component Library-------\n"
       << "| Label   Component   Value   |\n"
       << "-------------------------------\n";
  for (auto it = component_library.begin(); it != component_library.end();
       it++) {
    // print out each component's label, type and value
    cout << **it << endl;
  }
  cout << "-------------------------------\n";
}
