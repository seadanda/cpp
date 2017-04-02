/* component.h
 * Interface for Component abstract base class
 *  Implementation:  component.cpp
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef COMPONENT_H
#define COMPONENT_H

#include "complex.h"

class Component {
protected:
  double frequency;        // frequency of circuit
  Complex impedence;       // impedence of component
  double phase_difference; // phase difference of impedence

public:
  // constructors and virtual destructor
  Component();
  Component(const double &, const Complex &, const double &);
  // destructor
  virtual ~Component() {}

  // modifiers
  // set frequency of component
  virtual void set_frequency(const double &) = 0;
  // set impedence of component
  virtual void set_impedence(const Complex &) = 0;
  // set phase difference of component
  virtual void set_phase_difference(const double &) = 0;

  // accessors
  // return frequency of component
  virtual double get_frequency() const = 0;
  // return impedence of component
  virtual Complex get_impedance() const = 0;
  // return phase difference of component
  virtual double get_phase_difference() const = 0;

  // calculate the magnitude of the components impedence
  virtual double get_mag_impedance() const = 0;
};

#endif
