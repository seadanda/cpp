/* inductor.h
 * Interface for Inductor class (derived from component class) to store and
 * manipulate inductors
 *  Implementation:  inductor.cpp
 *  Author:          Dónal Murray
 *  Date:            29/03/17
 */

#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "complex.h"
#include "component.h"

class Inductor : public Component {
private:
  double inductance;
  static int inductor_count;

public:
  // default constructor
  Inductor();
  // parametrised constructor (inductance)
  Inductor(const double &);
  // destructor
  ~Inductor();

  // return phase difference of component
  double get_phase_difference() const;
  // calculate impedence of component
  Complex get_impedance(const double &) const;
  // calculate the magnitude of the impedence
  double get_mag_impedance(const double &) const;
  // get inductance
  double get_value() const;
  // get label
  string get_label() const;
};

#endif
