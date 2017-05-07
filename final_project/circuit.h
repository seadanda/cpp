/* circuit.h
 * Interface for Circuit class to store and manipulate circuits
 *  Implementation:  circuit.cpp
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "capacitor.h" // capacitor class
#include "component.h" // component base class
#include "inductor.h"  // inductor class
#include "resistor.h"  // resistor class

class Circuit {
  friend ostream &operator<<(ostream &, Circuit &);

private:
  double frequency;               // frequency of AC circuit
  double impedence;               // impedence of whole circuit
  char connection_type;           // series or parallel
  vector<Component *> components; // polymorphic vector to add components
  vector<Circuit *> subcircuits;  // for nesting series/parallel circuits

public:
  // default constructor
  Circuit();
  // parametrised constructor (frequency)
  Circuit(const double &);
  // destructor
  ~Circuit();

  // set frequency of component (frequency)
  void set_frequency(const double &);
  // return frequency of component
  double get_frequency() const;
  // add component (component)
  void add_component(Component *);
  // connect components in series (s) or parallel (p)
  void connect(const char &);
  // calculate the impedence of the whole circuit
};

#endif
