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
  friend ostream &operator<<(ostream &, const Component &);

protected:
  double phase_difference; // phase difference
  double value;            // resistance/capacitance/inductance
  string label;

public:
  // parametrised constructor (phase, value, label)
  Component(const double &, const double &, const string &);
  // destructor
  virtual ~Component() {}

  // general functions
  // get resistance/capacitance/inductance
  double get_value() const;
  // return phase difference of component
  double get_phase_difference() const;
  // calculate the magnitude of the impedence
  double get_mag_impedance(const double &) const;
  // get label
  string get_label() const;
  // rename component
  void set_label(const string &);

  // subclass specific functions
  // calculate impedence of component
  virtual Complex get_impedance(const double &) const = 0;
};

#endif
