/* component.cpp
 * Implementation of Component abstract base class to serve as a common
 * interface for all components (resistor/capacitor/inductor)
 *  Interface:      component.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "component.h"
#include "complex.h"
#include <string>

// default constructor
Component::Component() : phase_difference{0}, value{0}, frequency{0} {}

// parametrised constructor (phase, value) - not in circuit
Component::Component(const double &phase, const double &val, const string &lab)
    : phase_difference{phase}, value{val}, frequency{0}, label{lab} {}

// parametrised constructor (phase, value, frequency) - in circuit
Component::Component(const double &phase, const double &val, const double &freq,
                     const string &lab)
    : phase_difference{phase}, value{val}, frequency{freq}, label{lab} {}
