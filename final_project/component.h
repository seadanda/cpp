/* component.h
 * Interface for Component abstract base class
 *  Implementation:  component.cpp
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef COMPONENT_H
#define COMPONENT_H

#include "complex.h"
#include <string>

class Component {
  friend ostream &operator<<(ostream &, Component &);

protected:
  double phase_difference; // phase difference
  double value;            // resistance/capacitance/inductance
  double frequency;        // frequency of circuit
  Complex impedence;       // impedence of component
  string label;

public:
  // default constructor
  Component();
  // parametrised constructor (phase)
  Component(const double &); // never use this one TODO
  // parametrised constructor (phase, value)
  Component(const double &, const double &, const string &);
  // parametrised constructor (phase, value, frequency)
  Component(const double &, const double &, const double &, const string &);
  // destructor
  virtual ~Component() {}

  virtual double get_resistance() const = 0;
  // set frequency of component (frequency)
  virtual void set_frequency(const double &) = 0;
  // return frequency of component
  virtual double get_frequency() const = 0;
  // return phase difference of component
  virtual double get_phase_difference() const = 0;
  // calculate impedence of component
  virtual Complex get_impedance() const = 0;
  // calculate the magnitude of the impedence
  virtual double get_mag_impedance() const = 0;
};

#endif
