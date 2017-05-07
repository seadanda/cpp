namespace libs {
// create polymorphic vector of base class pointers for component library
vector<Component *> component_lib;
// create vector of circuits for circuit library
vector<Circuit *> circuit_lib;
} // namespace libs

//---function prototypes---
// main menu
void main_menu();
// component menu
void comp_menu();
// circuit menu
void circ_menu();
// garbage collection
void clean_up();
// exception handling
void error(const int &err);
// overload ostream operator for components
ostream &operator<<(ostream &os, Component &comp);
// function to iterate through component library and and print the components
void print_component_lib();
// function to iterate through circuit library and and print the impedance of
// each circuit
void print_circuit_lib();
// function to create a circuit
void create_circuit(const vector<Component *> &lib);
