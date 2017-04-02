/* resistor.cpp
 * Implementation of Resistor class to store and manipulate resistors
 *  Interface:      resistor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "resistor.h"  // resistor class interface
#include "component.h" // component base class

Resistor::Resistor() : Component() {}

Resistor::Resistor(const double &freq, const Complex &Z, const double &phase)
    : Component(freq, Z, phase) {}
