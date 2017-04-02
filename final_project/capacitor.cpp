/* capacitor.cpp
 * Implementation of Capacitor class to store and manipulate capacitors
 *  Interface:      capacitor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "capacitor.h" // capacitor class interface
#include "component.h" // component base class

// default constructor
Capacitor::Capacitor() : Component(-90, 0) {}

// not in circuit (no frequency)
Capacitor::Capacitor(const double &C) : Component(-90, C) {}

// in circuit (freq specified)
Capacitor::Capacitor(const double &C, const double &freq)
    : Component(-90, C, freq) {}
