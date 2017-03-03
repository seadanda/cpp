// Transition energy calculator
// Program to calculate transition energy using the simple Bohr model
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

// Functions
double bohr_calc(int z, int n_i, int n_j) {
  // Compute energy of level in eV using the simple Bohr model
  // usage: bohr_calc(z,n_i,n_j)
  // where z is the atomic number, n_i and n_j are the initial and final quantum
  // numbers
  return 13.6 * pow(z, 2) * (1 / pow(n_j, 2) - 1 / pow(n_i, 2));
}

// Main
int main() {
  // Declare variables
  int atomic_number, init_state, final_state; // For z, n_i and n_j
  double transition_energy;                   // Value to output
  char repeat{'y'};                // Program repeats until user enters 'n'
  char energy_units;               // j or e for joules or electron volts
  const double e_charge{1.67e-19}; // For converting between eV and Joules

  // Loop until user enters n
  while (tolower(repeat) == 'y') {
    // Ask user to enter atomic number
    cout << "Please enter the atomic number: ";
    cin >> atomic_number;
    // loop until user enters valid input
    while (cin.fail() || (atomic_number < 1)) {
      cout << "Invalid input, please enter the atomic number: ";
      cin.clear();
      cin.ignore();
      cin >> atomic_number;
    }

    // Ask user to enter quantum numbers
    // Initial
    cout << "Please enter the quantum number of the initial state: ";
    cin >> init_state;
    // loop until user enters valid input
    while (cin.fail() || (init_state == 0)) {
      cout << "Invalid input, please enter the quantum number of the initial "
              "state: ";
      cin.clear();
      cin.ignore();
      cin >> init_state;
    }

    // Final
    cout << "Please enter the quantum number of the final state: ";
    cin >> final_state;
    // loop until user enters valid input
    while (cin.fail() || (final_state == 0)) {
      cout << "Invalid input, please enter the quantum number of the final "
              "state: ";
      cin.clear();
      cin.ignore();
      cin >> final_state;
    }

    // Make sure final quantum number is less than initial quantum number
    if (final_state > init_state) {
      cout << "This is unphysical, the quantum number of the initial energy "
              "level must be greater than the quantum number of the final "
              "energy level.\n";
    } else {
      // Ask user whether to display result in Joules or electron volts
      cout << "Would you like the transition energy in joules (j) or electron "
              "volts (e)? ";
      cin >> energy_units;
      while (
          cin.fail() ||
          !((tolower(energy_units) == 'j') || (tolower(energy_units == 'e')))) {
        cout << "Invalid input, please enter either j for joules or e for "
                "electron volts: ";
        cin.clear();
        cin.ignore();
        cin >> energy_units;
      }

      // call function to calculate the transition energy
      transition_energy = bohr_calc(atomic_number, init_state, final_state);
      if (tolower(energy_units) == 'e') {
        // Output answer
        cout << fixed; // Make sure trailing zeroes are displayed when setting
                       // precision
        cout << "A transition from state n=" << init_state
             << " to state n=" << final_state
             << " for an atom with atomic number Z=" << atomic_number
             << " produces a photon with energy E=" << setprecision(3)
             << transition_energy << " eV.\n";
      } else {
        // convert to Joules
        transition_energy *= e_charge;
        // Output answer
        cout << "A transition from state n=" << init_state
             << " to state n=" << final_state
             << " for an atom with atomic number Z=" << atomic_number
             << " produces a photon with energy E=" << setprecision(2)
             << transition_energy << " J.\n";
      }
    }
    cout << "Would you like to calculate another transition energy? (y/n): ";
    cin >> repeat;
    while (cin.fail() ||
           !((tolower(repeat) == 'y') || (tolower(repeat) == 'n'))) {
      cout << "Invalid input, please enter either y to make another "
              "calculation or n to exit the program: ";
      cin.clear();
      cin.ignore();
      cin >> repeat;
    }
  }
  return 0;
}
