/* circuit.h
 * Interface for Circuit class to store and manipulate circuits
 *  Implementation:  circuit.cpp
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>

#include "capacitor.h" // capacitor class
#include "component.h" // component base class
#include "inductor.h"  // inductor class
#include "resistor.h"  // resistor class

class Circuit {
  friend ostream &operator<<(ostream &, const Circuit &);

protected:
  double frequency;               // frequency of AC circuit
  double impedence;               // impedence of whole circuit
  string label;                   // circuit label
  vector<Component *> components; // polymorphic vector to add components
  vector<Circuit *> subcircuits;  // for nesting series/parallel circuits
  static int circuit_count;       // to make sure circuit IDs are unique

public:
  // default constructor
  Circuit();
  // parametrised constructor (frequency, label)
  Circuit(const double &, const string &);
  // destructor
  ~Circuit();

  // shared functions
  // set frequency of component (frequency)
  void set_frequency(const double &);
  // return frequency of component
  double get_frequency() const;
  // add component (component)
  void add_component(Component *);
  // add subcircuit (subcircuit)
  void add_subcircuit(Circuit *);
  // get label
  string get_label() const;
  // rename circuit
  void set_label(const string &);
  // get total number of components and subcircuits
  int get_no_components() const;
  // calculate the magnitude of the impedance of the circuit
  double get_mag_impedance() const;
  // calculate the total phase difference
  double get_phase_difference() const;

  // subclass specific functions
  // calculate the impedence of the whole circuit
  virtual Complex get_impedance() const = 0;
  // print circuit graphically
  virtual void print_circuit() = 0;
};

// subclass series inherits from circuit
class Series : public Circuit {
public:
  // constructor
  Series(const double &);
  // calculate the impedence of the whole circuit
  Complex get_impedance() const;
  // print circuits graphically
  void print_circuit();
};

// subclass series inherits from circuit
class Parallel : public Circuit {
public:
  // constructor
  Parallel(const double &);
  // calculate the impedence of the whole circuit
  Complex get_impedance() const;
  // print circuits graphically
  void print_circuit();
};

#endif
