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
};

#endif
