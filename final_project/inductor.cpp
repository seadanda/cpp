/* inductor.cpp
 * Implementation of Inductor class to store and manipulate inductors
 *  Interface:      Inductor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "inductor.h"  // Inductor class interface
#include "component.h" // component base class

// default constructor
Inductor::Inductor() : Component(90, 0) {}

// not in circuit (no frequency)
Inductor::Inductor(const double &L) : Component(90, L) {}

// in circuit (freq specified)
Inductor::Inductor(const double &L, const double &freq)
    : Component(90, L, freq) {}
