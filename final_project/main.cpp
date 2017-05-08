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

//-----------------------------------------------------------------------------
//---main function
//-----------------------------------------------------------------------------
int main() {
  // call main menu function
  main_menu();
  // free up memory and clear vectors
  clean_up(libs::component_lib);
  clean_up(libs::circuit_lib);
  // exit
  return 0;
}

//-----------------------------------------------------------------------------
//---functions
//-----------------------------------------------------------------------------

//---housekeeping
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

// template function to clean up memory at end of program
template <class T> void clean_up(vector<T *> &lib) {
  for (auto it = lib.begin(); it != lib.end(); it++) {
    delete *it;
  }
  lib.clear();
}

//---menu screens
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
    main_choice = take_input({0, 1, 2});
    switch (main_choice) {
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
    }
  }
}

void comp_menu() {
  using namespace libs; // component and circuit libraries

  // bools for menu loops
  bool quit_comp{false};
  bool quit_add;

  int comp_choice;
  while (!quit_comp) {
    quit_add = false; // reset add component menu loop
    cout << "--------Component menu--------\n"
         << "Select an option:\n"
         << "1     Add components to library\n"
         << "2     Edit a component\n"
         << "3     Print component library\n"
         << "0     Back to main menu\n"
         << "-------------------------------\n"
         << "Option: ";
    comp_choice = take_input({0, 1, 2, 3}); // 0, 1, 2, 3 only valid inputs
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

// template function to add a component to the component library
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

void circ_menu() {
  bool quit_circ{false};
  int circ_choice;
  while (!quit_circ) {
    cout << "--------Circuit menu--------\n"
         << "Select an option:\n"
         << "1     Create series circuit\n"
         << "2     Create parallel circuit\n"
         << "3     Print circuit library\n"
         << "4     Print a circuit\n"
         << "0     Back to main menu\n"
         << "-------------------------------\n"
         << "Option: ";
    circ_choice = take_input({0, 1, 2, 3, 4});
    switch (circ_choice) {
    case 0:
      quit_circ = true;
      break;
    case 1:
      create_circuit<Series>();
      break;
    case 2:
      create_circuit<Parallel>();
      break;
    case 3:
      print_circuit_lib();
      break;
    case 4:
      print_circuit_lib();
      break;
    }
  }
}

// function to create a circuit - type - series or parallel
template <class T> void create_circuit() {
  using namespace libs;
  cout << "Enter the frequency of the circuit: ";
  double freq_add;
  cin >> freq_add;
  if (is_same<T, Series>::value) {
    circuit_lib.push_back(new Series{freq_add});
  } else {
    circuit_lib.push_back(new Parallel{freq_add});
  }
  print_component_lib();
  bool quit_create{false};
  string s_comp_to_add;
  cout << "Enter q to create circuit and return to previous menu.\n"
       << "Enter components to add by entering their labels separated by "
          "spaces\n";
  while (!quit_create) {
    try {
      cin >> s_comp_to_add;

      if (s_comp_to_add[0] == 'q') {
        quit_create = true;
      } else {
        // iterate through component list to find the component
        bool found{false};
        for (auto it : component_lib) {
          if (it->get_label() == s_comp_to_add) {
            // add this component to the circuit
            auto last = circuit_lib.end() - 1;
            (*last)->add_component(it);
            found = true;
          }
        }
        if (!found) {
          throw(1);
        }
      }
    } catch (int &err) {
      error(err);
    }
  }
}

void print_circuit_lib() {
  using namespace libs;
  cout << "--------Circuit Library--------\n"
       << "| Label   Impedence           |\n"
       << "-------------------------------\n";
  for (auto it = circuit_lib.begin(); it != circuit_lib.end(); it++) {
    cout << **it << endl;
  }
}
