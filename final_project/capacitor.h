/* capacitor.h
 * Interface for Capacitor class (derived from Component class) to store and
 * manipulate capacitors
 *  Implementation:  capacitor.cpp
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "complex.h"
#include "component.h"

class Capacitor : public Component {
private:
  double capacitance;

public:
  // default constructor
  Capacitor();
  // not in circuit (no frequency)
  Capacitor(const double &);
  // in circuit (freq specified)
  Capacitor(const double &, const double &);

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

  double get_value() const;
};

#endif
