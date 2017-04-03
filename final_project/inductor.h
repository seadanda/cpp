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
public:
  // default constructor
  Inductor();
  // not in circuit (no frequency)
  Inductor(const double &);
  // in circuit (freq specified)
  Inductor(const double &, const double &);

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
};

#endif
