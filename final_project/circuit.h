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

  // set frequency of component (frequency)
  virtual void set_frequency(const double &) = 0;
  // return frequency of component
  virtual double get_frequency() const = 0;
  // add component (component)
  virtual void add_component(Component *) = 0;
  // add subcircuit (subcircuit)
  virtual void add_subcircuit(Circuit *) = 0;
  // calculate the impedence of the whole circuit
  virtual Complex get_impedance() const = 0;
  // calculate the magnitude of the impedance of the circuit
  virtual double get_mag_impedance() const = 0;
  // get label
  virtual string get_label() const = 0;
  // print circuit graphically
  virtual void print_circuit() = 0;
  // print subcircuits graphically
  virtual void print_subcircuit() = 0;
  // get total number of components and subcircuits
  virtual int get_no_components() const = 0;
};

class General_circ : public Circuit {
public:
  // constructor
  General_circ(const double &, const string &);
  // set frequency of component (frequency)
  void set_frequency(const double &);
  // return frequency of component
  double get_frequency() const;
  // add component (component)
  void add_component(Component *);
  // add subcircuit (subcircuit)
  void add_subcircuit(Circuit *);
  // calculate the magnitude of the impedance of the circuit
  double get_mag_impedance() const;
  // get label
  string get_label() const;
  // get total number of components and subcircuits
  int get_no_components() const;
};

class Series : public General_circ {
public:
  // constructor
  Series(const double &);
  // calculate the impedence of the whole circuit
  Complex get_impedance() const;
  // print circuits graphically
  void print_circuit();
  void print_subcircuit();
};

class Parallel : public General_circ {
public:
  // constructor
  Parallel(const double &);
  // calculate the impedence of the whole circuit
  Complex get_impedance() const;
  // print circuits graphically
  void print_circuit();
  void print_subcircuit();
};

#endif
