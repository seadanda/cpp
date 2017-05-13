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
  static int inductor_count;

public:
  // parametrised constructor (inductance)
  Inductor(const double &);
  // destructor
  ~Inductor();

  // calculate impedence of component
  Complex get_impedance(const double &) const;
};

#endif
