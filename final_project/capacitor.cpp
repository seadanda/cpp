/* capacitor.cpp
 * Implementation of Capacitor class to store and manipulate capacitors
 *  Interface:      capacitor.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include "capacitor.h" // capacitor class interface
#include "component.h" // component base class

Capacitor::Capacitor() : Component() {}

Capacitor::Capacitor(const double &freq, const Complex &Z, const double &phase)
    : Component(freq, Z, phase) {}
