/* component.cpp
 * Implementation of Component abstract base class to serve as a common
 * interface for all components (resistor/capacitor/inductor)
 *  Interface:      component.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "component.h"
#include "complex.h"

// default constructor
Component::Component() : frequency{0}, impedence{0}, phase_difference{0} {}

// parametrised constructor
Component::Component(const double &freq, const Complex &Z, const double &phase)
    : frequency{freq}, impedence{Z}, phase_difference{phase} {}
