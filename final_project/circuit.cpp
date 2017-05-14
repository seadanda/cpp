/* circuit.cpp
 * Implementation of Circuit class to store and manipulate circuits
 *  Interface:      circuit.h
 *  Author:         Dónal Murray
 *  Date:           29/03/17
 */

#include <iostream> // std io
#include <sstream>  // stringstream
#include <vector>   // vector type

#include "circuit.h" // class interface

#include "capacitor.h" // capacitor class
#include "complex.h"   // complex class
#include "component.h" // component base class
#include "inductor.h"  // inductor class
#include "resistor.h"  // resistor class

//-----------------------------------------------------------------------------
//---base class
//-----------------------------------------------------------------------------

int Circuit::circuit_count{0}; // initialise static data member

// default constructor
Circuit::Circuit() : frequency{0} {
  circuit_count++;
  // add circuit number to label
  stringstream comp_label;
  comp_label << label << circuit_count;
  label = comp_label.str();
}

// parametrised constructor (frequency)
Circuit::Circuit(const double &freq, const string &lab)
    : frequency{freq}, label(lab) {
  circuit_count++;
  // add circuit number to label
  stringstream comp_label;
  comp_label << label << circuit_count;
  label = comp_label.str();
}

// destructor
Circuit::~Circuit() {
  // delete the components container - memory for components will be freed when
  // the component library is freed up
  components.clear();
  // delete the subcircuits container - memory for the subcircuits will be freed
  // when the circuit library is freed up
  subcircuits.clear();
}

// get the frequency
double Circuit::get_frequency() const { return frequency; }

// change the frequency
void Circuit::set_frequency(const double &freq) {
  // change frequency of circuit
  frequency = freq;
  // change frequency of all subcircuits
  for (auto it = subcircuits.begin(); it != subcircuits.end(); it++) {
    (*it)->set_frequency(freq);
  }
}

// return label
string Circuit::get_label() const { return label; }

// rename circuit
void Circuit::set_label(const string &lab) { label = lab; }

// add component (component)
void Circuit::add_component(Component *new_comp) {
  components.push_back(new_comp);
}

// add subcircuit (subcircuit)
void Circuit::add_subcircuit(Circuit *new_circ) {
  subcircuits.push_back(new_circ);
}

// calculate the magnitude of the impedance of the circuit
double Circuit::get_mag_impedance() const {
  return (get_impedance()).modulus();
}

// get total number of components and subcircuits
int Circuit::get_no_components() const {
  return components.size() + subcircuits.size();
}

double Circuit::get_phase_difference() const {
  return (get_impedance()).argument();
}

//-----------------------------------------------------------------------------
//---friend functions
//-----------------------------------------------------------------------------
// overload ostream operator for circuits
ostream &operator<<(ostream &os, const Circuit &circ) {
  os << "  " << circ.label << "  " << circ.frequency << "Hz  "
     << circ.get_mag_impedance() << "   ( ";
  for (auto it : circ.components) {
    os << it->get_label() << " ";
  }
  for (auto it : circ.subcircuits) {
    os << it->label << " ";
  }
  os << ")";
  return os;
}

//-----------------------------------------------------------------------------
//---Series derived class
//-----------------------------------------------------------------------------
// constructor
Series::Series(const double &freq) : Circuit(freq, "S") {}
// print series circuit
void Series::print_circuit() {
  // series circuit, just print in line
  cout << "\nPrinting circuit " << label << " which has a frequency "
       << frequency << "Hz\ntotal impedance Z=" << get_impedance()
       << "\nmagnitude of impedence |Z|=" << get_mag_impedance() << "\u03A9"
       << "\nphase difference " << get_phase_difference() << "\n\n"
       << "+--(~)--+\n";
  for (auto it : subcircuits) {
    // the component is a subcircuit
    cout << "|       |\n"
         << "|     .-+-.\n"
         << "|     |" << it->get_label() << " |\n"
         << "|     '-+-' |Z|=" << it->get_mag_impedance() << "\u03A9\n";
  }
  for (auto it : components) {
    if (!(dynamic_cast<Resistor *>(it) == nullptr)) {
      // the component is a resistor
      cout << "|       |\n"
           << "|      .+.\n"
           << "|      | | " << it->get_label() << endl
           << "|      '+' |Z|=" << it->get_mag_impedance(frequency)
           << "\u03A9\n";
    } else if (!(dynamic_cast<Capacitor *>(it) == nullptr)) {
      // the component is a resistor
      cout << "|       |\n"
           << "|       |\n"
           << "|      === " << it->get_label() << endl
           << "|       |  |Z|=" << it->get_mag_impedance(frequency)
           << "\u03A9\n";
    } else if (!(dynamic_cast<Inductor *>(it) == nullptr)) {
      // the component is an inductor
      cout << "|       |\n"
           << "|       $\n"
           << "|       $  " << it->get_label() << endl
           << "|       $  |Z|=" << it->get_mag_impedance(frequency)
           << "\u03A9\n";
    }
  }
  // draw end line
  cout << "|       |\n"
          "+-------+\n\n\n";
}

// calculate the impedence of the whole circuit
Complex Series::get_impedance() const {
  Complex temp{0};
  for (auto it = components.begin(); it != components.end(); it++) {
    temp = temp + (*it)->get_impedance(frequency);
  }
  for (auto it = subcircuits.begin(); it != subcircuits.end(); it++) {
    temp = temp + (*it)->get_impedance();
  }
  return temp;
}

//-----------------------------------------------------------------------------
//---Parallel derived class
//-----------------------------------------------------------------------------
// constructor;
Parallel::Parallel(const double &freq) : Circuit(freq, "P") {}
// print parallel circuit
void Parallel::print_circuit() {
  // parallel circuit
  cout << "\nPrinting circuit " << label << " which has a frequency "
       << frequency << "Hz\ntotal impedance Z=" << get_impedance()
       << "\nmagnitude of impedence |Z|=" << get_mag_impedance() << "\u03A9"
       << "\nphase difference " << get_phase_difference() << "\n\n"
       << "+--(~)---+\n";
  // draw placeholders for any subcircuits
  for (auto it : subcircuits) {
    // print subcircuits
    cout << "|        |\n"
         << "| +----+ |\n"
         << "| | " << it->get_label() << " | | |Z|=" << it->get_mag_impedance()
         << "\u03A9\n"
         << "+-+----+-+\n";
  }

  for (auto it : components) {
    if (!(dynamic_cast<Resistor *>(it) == nullptr)) {
      // the component is a resistor
      cout << "|        |\n"
           << "|        |\n"
           << "|  ____  | " << it->get_label() << endl
           << "+-+____+-+ |Z|=" << it->get_mag_impedance(frequency)
           << "\u03A9\n";
    } else if (!(dynamic_cast<Capacitor *>(it) == nullptr)) {
      // the component is a resistor
      cout << "|        |\n"
           << "|        |\n"
           << "|        | " << it->get_label() << endl
           << "+---||---+ |Z|=" << it->get_mag_impedance(frequency)
           << "\u03A9\n";
    } else if (!(dynamic_cast<Inductor *>(it) == nullptr)) {
      // the component is an inductor
      cout << "|        |\n"
           << "|        |\n"
           << "|        | " << it->get_label() << endl
           << "+-+/\\/\\+-+ |Z|=" << it->get_mag_impedance(frequency)
           << "\u03A9\n";
    }
  }
}

// calculate the impedence of the whole circuit
Complex Parallel::get_impedance() const {
  Complex temp{0, 0};
  Complex one{1, 0};
  for (auto it = components.begin(); it != components.end(); it++) {
    temp = temp + one / ((*it)->get_impedance(frequency));
  }
  for (auto it = subcircuits.begin(); it != subcircuits.end(); it++) {
    temp = temp + one / ((*it)->get_impedance());
  }
  return one / temp;
}
