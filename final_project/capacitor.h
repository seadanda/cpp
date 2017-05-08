/* capacitor.h
 * Interface for Capacitor class (derived from Component class) to store and
 * manipulate capacitors
 *  Implementation:  capacitor.cpp
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "circuit.h"
#include "complex.h"
#include "component.h"

class Capacitor : public Component {
private:
  double capacitance;
  static int capacitor_count;

public:
  // default constructor
  Capacitor();
  // parametrised constructor (capacitance in micro farads)
  Capacitor(const double &);
  // destructor
  ~Capacitor();

  // return phase difference of component
  double get_phase_difference() const;
  // calculate impedence of component
  Complex get_impedance(const double &) const;
  // calculate the magnitude of the impedence
  double get_mag_impedance(const double &) const;
  // get capacitance
  double get_value() const;
  // get label
  string get_label() const;
};

#endif
