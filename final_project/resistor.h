/* resistor.h
 * Interface for Resistor class (derived from component class) to store and
 * manipulate resistors
 *  Implementation:  resistor.cpp
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef RESISTOR_H
#define RESISTOR_H

#include "complex.h"
#include "component.h"

class Resistor : public Component {
private:
  double resistance;

public:
  // default constructor
  Resistor();
  // not in circuit (no frequency)
  Resistor(const double &);
  // in circuit (freq specified)
  Resistor(const double &, const double &);

  // set frequency of component (frequency)
  void set_frequency(const double &);
  // return frequency of component
  double get_frequency() const;
  // return phase difference of component
  double get_phase_difference() const;
  // calculate impedence of component
  Complex get_impedance() const;
  // calculate the magnitude of the impedence
  double get_mag_impedance() const;
  // get resistance of component
  double get_value() const;
};

#endif
