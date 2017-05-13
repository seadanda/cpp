/* main.h: AC Circuit Manipulator main file header containing function
 * prototypes and the libs namespace for the libraries of components and
 * circuits
 *
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef MAIN_H
#define MAIN_H

#include <vector>

#include "circuit.h"
#include "component.h"

//-----------------------------------------------------------------------------
//---function prototypes
//-----------------------------------------------------------------------------
//---housekeeping
// exception handling
void error(const int &);
// template function to clean up memory at end of program
template <class T> void clean_up(vector<T *> &);
// template function to take input
template <class T> T take_input(initializer_list<T>);

//---menu
void main_menu();

//---add functions
// template function to add component
template <class T> void add_component();
// function to create a circuit
template <class T> void add_circuit();

//---print functions
// function to iterate through component library and and print the components
void print_component_lib();
// function to iterate through circuit library and and print the impedance of
// each circuit
void print_circuit_lib();

//---load and save
void save_project();
void load_project();

//-----------------------------------------------------------------------------
//---libs namespace to allow access to libraries from any function
//-----------------------------------------------------------------------------
namespace libs {
// create polymorphic vector of base class pointers for component library
vector<Component *> component_lib;
// create polymorphic vector of base class pointers for circuit library
vector<Circuit *> circuit_lib;
} // namespace libs

#endif
