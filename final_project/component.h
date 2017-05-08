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
  Complex impedence;       // impedence of component
  string label;

public:
  // default constructor
  Component();
  // parametrised constructor (phase)
  Component(const double &); // never use this one TODO
  // parametrised constructor (phase, value)
  Component(const double &, const double &, const string &);
  // parametrised constructor (phase, value, label)
  Component(const double &, const double &, const double &, const string &);
  // destructor
  virtual ~Component() {}

  // get resistance/capacitance/inductance
  virtual double get_value() const = 0;
  // return phase difference of component
  virtual double get_phase_difference() const = 0;
  // calculate impedence of component
  virtual Complex get_impedance(const double &) const = 0;
  // calculate the magnitude of the impedence
  virtual double get_mag_impedance(const double &) const = 0;
  // get label
  virtual string get_label() const = 0;
};

#endif
