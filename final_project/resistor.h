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
public:
  // constructors
  Resistor();
  Resistor(const double &, const Complex &, const double &);
};

#endif
