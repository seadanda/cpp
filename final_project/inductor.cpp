/* inductor.cpp
 * Implementation of Inductor class to store and manipulate inductors
 *  Interface:      Inductor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "inductor.h"  // Inductor class interface
#include "component.h" // component base class

Inductor::Inductor() : Component() {}

Inductor::Inductor(const double &freq, const Complex &Z, const double &phase)
    : Component(freq, Z, phase) {}
