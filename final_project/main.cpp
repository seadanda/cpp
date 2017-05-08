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
#include "main.h"      // functions and libs namespace
#include "resistor.h"  // resistor class

using namespace std;

//-----------------------------------------------------------------------------
//---main function
//-----------------------------------------------------------------------------
int main() {
  cout << "AC Circuit Manipulator\n"
       << "  Author: Dónal Murray\n\n";
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
    bool invalid_input{true};
    for (auto it : allowed) {
      // iterate through input parameters and check that the input is allowed
      if (temp == it) {
        // if the input is in the list, return false
        invalid_input = false;
      }
    }
    if (allowed.size() == 0) {
      // no range specified, if cin doesn't throw a fail flag it's valid
      invalid_input = false;
    }
    return invalid_input;
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
  bool valid_print;
  while (!quit_main) {
    cout << "\nSelect an option:\n"
         << "1     Add components to library\n"
         << "2     Print component library\n"
         << "3     Create series circuit\n"
         << "4     Create parallel circuit\n"
         << "5     Print circuit library\n"
         << "6     Print a circuit\n"
         << "0     Quit\n"
         << endl
         << "Option: ";
    main_choice = take_input({0, 1, 2, 3, 4, 5, 6});
    bool quit_add{false};
    switch (main_choice) {
    case 0:
      cout << "Exit\n";
      quit_main = true;
      break;
    case 1:
      cout << "\nEnter q to stop adding components.\n";
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
      // print component library
      print_component_lib();
      break;
    case 3:
      // create series circuit
      add_circuit<Series>();
      break;
    case 4:
      // create parallel circuit
      add_circuit<Parallel>();
      break;
    case 5:
      // print circuit library
      print_circuit_lib();
      break;
    case 6:
      // print specific circuit
      print_circuit_lib();
      cout << "Select a circuit to print using its label: ";
      string print_choice;
      cin >> print_choice;
      valid_print = false;
      try {
        for (auto it : libs::circuit_lib) {
          if (it->get_label() == print_choice) {
            // print choice is a valid circuit
            valid_print = true;
            it->print_circuit();
          }
        }
        if (!valid_print) {
          throw(2);
        }
      } catch (int &err) {
        error(err);
      }
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

// function to create a circuit - type - series or parallel
template <class T> void add_circuit() {
  using namespace libs;
  cout << "Enter the frequency of the circuit: ";
  double freq_add;
  freq_add = take_input<double>({});
  if (is_same<T, Series>::value) {
    cout << "\nSeries circuit with frequency " << freq_add << "Hz created\n\n";
    circuit_lib.push_back(new Series{freq_add});
  } else {
    cout << "Parallel circuit with frequency " << freq_add << "Hz created\n\n";
    circuit_lib.push_back(new Parallel{freq_add});
  }
  print_component_lib();
  print_circuit_lib();
  bool quit_create{false};
  string s_comp_to_add;
  cout << "Enter q to create circuit and return to previous menu.\n"
       << "Add components/subcircuits by entering their labels separated by "
          "spaces\n";
  while (!quit_create) {
    try {
      cin >> s_comp_to_add;
      if (s_comp_to_add[0] == 'q') {
        // user wants to quit
        quit_create = true;
      } else {
        // iterate through component list to see if the label is a component
        bool found{false};
        for (auto it : component_lib) {
          if (it->get_label() == s_comp_to_add) {
            // add this component to the circuit
            auto last = circuit_lib.end() - 1;
            (*last)->add_component(it);
            found = true;
          }
        }
        // iterate through circuit list to see if the label is a circuit
        for (auto it : circuit_lib) {
          if (it->get_label() == s_comp_to_add) {
            // add this subcircuit to the circuit
            auto last = circuit_lib.end() - 1;
            (*last)->add_subcircuit(it);
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

// function to iterate through component library and and print the components
void print_component_lib() {
  using namespace libs;
  cout << "-------Component Library-------\n"
       << "| Label   Component  Value    |\n"
       << "-------------------------------\n";
  int i{0};
  for (auto it = component_lib.begin(); it != component_lib.end(); it++) {
    // print out each component's label, type and value
    i++;
    cout << **it << endl;
  }
  if (i < 1) {
    cout << "Empty.\n";
  }
  cout << endl;
}

void print_circuit_lib() {
  using namespace libs;
  cout << "--------Circuit Library-------------------\n"
       << "| Label  Freq  Impedence  Component list |\n"
       << "------------------------------------------\n";
  int i{0};
  for (auto it = circuit_lib.begin(); it != circuit_lib.end(); it++) {
    // print out each circuit's label, freq, impedence and components
    if ((*it)->get_no_components() == 0) {
    } else {
      i++;
      cout << **it << endl;
    }
  }
  if (i < 1) {
    cout << "Empty.\n";
  }
  cout << endl;
}
