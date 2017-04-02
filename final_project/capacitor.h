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
  // constructors
  Capacitor();
  Capacitor(const double &, const Complex &, const double &);
};

#endif
