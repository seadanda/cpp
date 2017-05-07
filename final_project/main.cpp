/* main.cpp: AC Circuit Manipulator main file and function definitions
 *
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#include <initializer_list> // initializer_list
#include <iostream>         // std io
#include <limits>           // streamsize
#include <type_traits>      // for is_same - function templates
#include <vector>           // vector container

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
  clean_up(libs::component_lib);
  clean_up(libs::circuit_lib);
  // exit
  return 0;
}

//---functions---
// main menu
void main_menu() {
  int main_choice;
  bool quit_main{false};
  while (!quit_main) {
    cout << "-----------Main Menu-----------\n"
         << "Select an option:\n"
         << "1     Component menu\n"
         << "2     Circuit menu\n"
         << "0     Quit\n"
         << "-------------------------------\n"
         << "Option: ";
    cin >> main_choice;
    while (cin.fail() ||
           !((main_choice == 0) || (main_choice == 1) || (main_choice == 2))) {
      cerr << "Please choose a valid option: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> main_choice;
    }
    switch (main_choice) {
    case 0:
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Exit\n";
      quit_main = true;
      break;
    case 1:
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      comp_menu();
      break;
    case 2:
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      circ_menu();
      break;
    }
  }
}

// function to add a component to the component library
template <class T> void add_component() {
  double temp_val;
  // check the type of the component and ask for value
  if (is_same<T, Resistor>::value) {
    // type is resistor
    cout << "Enter the resistance in \u03A9: ";
  } else if (is_same<T, Capacitor>::value) {
    // type is capacitor
    cout << "Enter the capacitance in \u00B5F: ";
  } else if (is_same<T, Inductor>::value) {
    // type is inductor
    cout << "Enter the inductance in \u00B5H: ";
  }
  cin >> temp_val;
  libs::component_lib.push_back(new T{temp_val});
}

template <class T> void clean_up(vector<T *> &lib) {
  for (auto it = lib.begin(); it != lib.end(); it++) {
    delete *it;
  }
  lib.clear();
}

// function to take input and make sure it is an allowed value (in parameters)
template <class T> T take_input(initializer_list<T> allowed) {
  T temp;
  cin >> temp; // take input
  while (cin.fail() || [&]() {
    // lambda to check for disallowed inputs not caught by a fail flag
    bool valid_input{true};
    for (auto it : allowed) {
      // iterate through input parameters and check that the input is allowed
      if (temp == it) {
        // if the input is in the list, return false
        valid_input = false;
      }
    }
    return valid_input;
  }()) {
    // clear fail bit and flush stream buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // take input again
    cerr << "Please choose a valid option: ";
    cin >> temp;
  }
  // clear rest of stream, in case there is anything else there
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return temp;
}

void comp_menu() {
  using namespace libs;

  bool quit_comp{false};
  int comp_choice;
  while (!quit_comp) {
    bool quit_add{false};
    cout << "--------Component menu--------\n"
         << "Select an option:\n"
         << "1     Add components to library\n"
         << "2     Edit a component\n"
         << "3     Print component library\n"
         << "0     Back to main menu\n"
         << "-------------------------------\n"
         << "Option: ";
    comp_choice = take_input({0, 1, 2, 3});
    switch (comp_choice) {
    case 0:
      quit_comp = true;
      break;
    case 1:
      cout << "Press q to stop adding components.\n";
      while (!quit_add) {
        cout << "Add resistor(r), capacitor(c) or inductor(i)?: ";
        char add_choice;
        add_choice = take_input({'q', 'r', 'c', 'i'});
        switch (add_choice) {
        case 'q':
          // sort library by component label

          // go back to component menu
          quit_add = true;
          break;
        case 'r':
          add_component<Resistor>();
          break;
        case 'c':
          add_component<Capacitor>();
          break;
        case 'i':
          add_component<Inductor>();
          break;
        }
      }
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

  bool quit_circ{false};
  int circ_choice;
  while (!quit_circ) {
    cout << "--------Circuit menu--------\n"
         << "Select an option:\n"
         << "1     Create new circuit\n"
         << "2     Edit a circuit\n"
         << "3     Print a circuit\n"
         << "4     Print circuit library\n"
         << "0     Back to main menu\n"
         << "-------------------------------\n"
         << "Option: ";
    circ_choice = take_input({0, 1, 2, 3, 4});
    switch (circ_choice) {
    case 0:
      quit_circ = true;
      break;
    case 1:
      cout << "Create circuit\n";
      circuit_lib.push_back(new Circuit{159.15});
      (*(circuit_lib.begin()))->add_component(new Resistor{100});
      (*(circuit_lib.begin()))->add_component(new Capacitor{10});
      break;
    case 2:
      print_component_lib();
      break;
    case 3:
      cout << "print_circuit()\n";
      break;
    case 4:
      print_circuit_lib();
      break;
    }
  }
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

void print_circuit_lib() {
  using namespace libs;
  cout << "--------Circuit Library--------\n"
       << "| Label   Impedence           |\n"
       << "-------------------------------\n";
  for (auto it = circuit_lib.begin(); it != circuit_lib.end(); it++) {
    // print out each component's label, type and value
    cout << **it << endl;
  }
}

// function to iterate through component library and and print the components
void print_component_lib() {
  using namespace libs;
  cout << "-------Component Library-------\n"
       << "| Label   Component  Value    |\n"
       << "-------------------------------\n";
  for (auto it = component_lib.begin(); it != component_lib.end(); it++) {
    // print out each component's label, type and value
    cout << **it << endl;
  }
}

// function to create a circuit
void create_circuit() { cout << "--------Circuit Creator--------\n"; }
