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
public:
  // default constructor
  Capacitor();
  // not in circuit (no frequency)
  Capacitor(const double &);
  // in circuit (freq specified)
  Capacitor(const double &, const double &);
};

#endif
