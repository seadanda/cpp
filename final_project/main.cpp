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

// main function
int main() {
  // call main menu function
  main_menu();
  // free up memory and clear vectors
  clean_up();
  // exit
  return 0;
}

//---functions---
void main_menu() {
  // draw main menu
  bool quit_main{false};
  int menu_choice;
  while (!quit_main) {
    cout << "-----------Main Menu-----------\n"
         << "Select an option:\n"
         << "1     Component menu\n"
         << "2     Circuit menu\n"
         << "0     Quit\n"
         << "-------------------------------\n"
         << "Option: ";
    cin >> menu_choice;
    switch (menu_choice) {
    case 0:
      cout << "Exit\n";
      quit_main = true;
      break;
    case 1:
      comp_menu();
      break;
    case 2:
      circ_menu();
      break;
    default:
      cout << "Please choose a valid option\n";
      break;
    }
  }
}

void comp_menu() {
  using namespace libs;
  bool quit_comp{false};
  int comp_choice;
  while (!quit_comp) {
    cout << "--------Component menu--------\n"
         << "Select an option:\n"
         << "1     Add a component to library\n"
         << "2     Edit a component\n"
         << "3     Print component library\n"
         << "0     Back to main menu\n"
         << "-------------------------------\n"
         << "Option: ";
    cin >> comp_choice;
    switch (comp_choice) {
    case 0:
      cout << "Exit\n";
      quit_comp = true;
      break;
    case 1:
      cout << "Added default components\n";
      // add a few sample components to library
      component_lib.push_back(new Resistor{200});
      component_lib.push_back(new Resistor{100, 10});
      component_lib.push_back(new Inductor{100});
      component_lib.push_back(new Inductor{100, 159.15});
      component_lib.push_back(new Capacitor{100});
      component_lib.push_back(new Capacitor{10, 300});
      break;
    case 2:
      print_component_lib();
      break;
    case 3:
      print_component_lib();
      break;
    }
  }
}

void circ_menu() {
  using namespace libs;
  cout << "--------Circuit menu--------\n"
       << "Select an option:\n"
       << "1     Component menu\n"
       << "2     Circuit menu\n"
       << "0     Back to main menu\n"
       << "-------------------------------\n"
       << "Option: ";
  cout << "Create circuit\n";
  circuit_lib.push_back(new Circuit{159.15});
  (*(circuit_lib.begin()))->add_component(new Resistor{100});
  (*(circuit_lib.begin()))->add_component(new Capacitor{10});
}

void clean_up() {
  using namespace libs;
  // iterate through vectors and free up memory
  for (auto it = component_lib.begin(); it != component_lib.end(); it++) {
    delete *it;
  }
  for (auto it = circuit_lib.begin(); it != circuit_lib.end(); it++) {
    delete *it;
  }

  // clear vectors
  component_lib.clear();
  circuit_lib.clear();
}

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

// function to iterate through component library and and print the components
void print_component_lib() {
  using namespace libs;
  cout << "-------Component Library-------\n"
       << "| Label   Component   Value   |\n"
       << "-------------------------------\n";
  for (auto it = component_lib.begin(); it != component_lib.end(); it++) {
    // print out each component's label, type and value
    cout << **it << endl;
  }
}

// function to create a circuit
void create_circuit(const vector<Component *> &lib) {
  cout << "--------Circuit Creator--------\n"
       << "function to create a circuit\n";
}
