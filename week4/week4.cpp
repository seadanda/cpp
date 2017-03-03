// Assignment 4
// Program to describe galaxies
// Dónal Murray 22 Feb 2017

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Galaxy // define class
{
private:
  // properties {} discrete, [] continuous
  string hubble_type;          // hubbletype {E{0-7},S0,S{a,b,c},SB{a,b,c},Irr}
  double redshift;             // redshift [0, 10]
  double total_mass;           // total mass [10^7, 10^12]M_s
  double stellar_mass_frac;    // stellar mass fraction [0, 0.05]
  vector<Galaxy *> satellites; // vector of satellites

public:
  // default constructor
  Galaxy()
      : hubble_type{"Irr"}, redshift{0}, total_mass{0}, stellar_mass_frac{0} {}
  // parametrised constructor
  Galaxy(string htype, double rshift, double tmass, double smf)
      : hubble_type{htype}, redshift{rshift}, total_mass{tmass},
        stellar_mass_frac{smf} {}
  // destructor
  ~Galaxy() {}

  // modifiers
  void set_hubble_type(string htype) { hubble_type = htype; }
  void set_redshift(double rshift) { redshift = rshift; }
  void set_total_mass(double tmass) { total_mass = tmass; }
  void set_stellar_mass_fraction(double smf) { stellar_mass_frac = smf; }

  // accessors
  string get_hubble_type() { return hubble_type; }
  double get_redshift() { return redshift; }
  double get_total_mass() { return total_mass; }
  double get_stellar_mass_fraction() { return stellar_mass_frac; }
  double get_stellar_mass() { return (stellar_mass_frac * total_mass); }
  int get_num_satellites() { return satellites.size(); }

  // other member functions -- prototype longer functions
  void add_satellite(Galaxy &sat); // add a satellite to the galaxy
  void print_data(); // print out all data associated with a galaxy
};

void Galaxy::add_satellite(Galaxy &sat) { satellites.push_back(&sat); }

// define member functions
void Galaxy::print_data() // print out all attributes of the galaxy
{
  cout << "  The hubble type is \"" << hubble_type << "\", the redshift is "
       << redshift << ", the stellar mass is " << get_stellar_mass()
       << " solar mass units.\n";

  if (satellites.size() != 0) {
    cout << "  The galaxy has " << satellites.size() << " satellite(s):\n";
    int j{1}; // to label the satellites when printing
    for (auto it_s = satellites.begin(); it_s != satellites.end(); it_s++) {
      cout << "  Satellite " << j++ << " properties:\n  ";
      (*it_s)->print_data();
    }
  }
}

int main() // main
{
  // vector of galaxies (reference to keep changes up to date)
  vector<Galaxy *> galaxies;

  // construct galaxies
  Galaxy milky_way;
  Galaxy NGC1300("SBb", 0.005260, 1e11, 0.04);

  // push galaxies onto a vector
  galaxies.push_back(&milky_way);
  galaxies.push_back(&NGC1300);

  // print out milky way (default) values
  cout << "Default constructor values:\n";
  milky_way.print_data();

  // change Milky Way's properties
  milky_way.set_hubble_type("SBa");
  milky_way.set_redshift(0);
  milky_way.set_total_mass(7e11);
  milky_way.set_stellar_mass_fraction(0.05);

  // create Milky Way's satellite galaxies
  Galaxy small_mag_cloud("Irr", 0.000486, 2.4e9, 0.03);
  Galaxy large_mag_cloud("Irr", 0.000875, 1e10, 0.01);

  // add these satellites to the milky way galaxy
  milky_way.add_satellite(small_mag_cloud);
  milky_way.add_satellite(large_mag_cloud);

  // iterate through the vector of galaxies and print each galaxy's attributes
  // note that the properties of the milky way have also changed in this vector
  int i{1}; // to label galaxies when printing
  for (auto it = galaxies.begin(); it != galaxies.end(); it++) {
    cout << "\nGalaxy " << i++ << " properties:\n";
    (*it)->print_data();
  }

  // exit
  return 0;
}
