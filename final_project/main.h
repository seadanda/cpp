/* main.h: AC Circuit Manipulator main file header containing function
 * prototypes and the libs namespace for the libraries of components and
 * circuits
 *
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

//-----------------------------------------------------------------------------
//---function prototypes
//-----------------------------------------------------------------------------
#ifndef MAIN_H
#define MAIN_H

#include "circuit.h"
#include <vector>

//---housekeeping
// exception handling
void error(const int &);
// template function to clean up memory at end of program
template <class T> void clean_up(vector<T *> &);
// template function to take input
template <class T> T take_input(initializer_list<T>);

//---main menu
void main_menu();

//---component menu
// draw menu
void comp_menu();
// template function to add component
template <class T> void add_component();
// function to iterate through component library and and print the components
void print_component_lib();

//---circuit menu
// draw menu
void circ_menu();
// function to create a circuit
template <class T> void create_circuit();
// function to iterate through circuit library and and print the impedance of
// each circuit
void print_circuit_lib();

//-----------------------------------------------------------------------------
//---libs namespace to allow access to libraries from any function
//-----------------------------------------------------------------------------

namespace libs {
// create polymorphic vector of base class pointers for component library
vector<Component *> component_lib;
// create vector of circuits for circuit library
vector<Circuit *> circuit_lib;
} // namespace libs

#endif
