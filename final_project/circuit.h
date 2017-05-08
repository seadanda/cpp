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
  static int circuit_count;

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
  // calculate the impedence of the whole circuit
  virtual Complex get_impedance() = 0;
  // calculate the magnitude of the impedance of the circuit
  virtual double get_mag_impedance() = 0;
  // get label
  virtual string get_label() = 0;
};

class Series : public Circuit {
  friend class Parallel;

public:
  Series(const double &);
  // set frequency of component (frequency)
  void set_frequency(const double &);
  // return frequency of component
  double get_frequency() const;
  // add component (component)
  void add_component(Component *);
  // calculate the magnitude of the impedance of the circuit
  double get_mag_impedance();
  // get label
  string get_label();

  // calculate the impedence of the whole circuit
  Complex get_impedance();
};

class Parallel : public Circuit {
  friend class Series;

public:
  Parallel(const double &);
  // set frequency of component (frequency)
  void set_frequency(const double &);
  // return frequency of component
  double get_frequency() const;
  // add component (component)
  void add_component(Component *);
  // calculate the magnitude of the impedance of the circuit
  double get_mag_impedance();
  // get label
  string get_label();
  // calculate the impedence of the whole circuit
  Complex get_impedance();
};

#endif
