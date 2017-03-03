#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

double get_mean(double charge[], int n) {
  // function to calculate the mean
  double charge_sum{0};
  for (int i{0}; i < n; i++) {
    charge_sum += charge[i];
  }
  return charge_sum / (double)n;
}

double get_sigma(double charge[], double average, int n) {
  // function to calculate the standard deviation
  double diff_sum{0};
  for (int i{0}; i < n; i++) {
    diff_sum += pow((charge[i] - average), 2);
  }
  return sqrt(diff_sum / ((double)n - 1));
}

double get_sigma_mean(double stddev, int n) {
  // function to calculate the standard error in the mean
  return stddev / sqrt((double)n);
}

int main() {

  string filename;
  cout << "Enter name of file to open: ";
  cin >> filename;

  // open file and check that it opened properly
  ifstream inputFile(filename.c_str());
  if (!inputFile.good()) {
    cout << "Error: could not open input file.\n";
    return 1;
  } else {
    cout << filename << " opened successfully.\n";
  }

  double N;
  int data_points;

  // Ask for user input
  cout << "Enter the number of data points in the file.\nIf you don't know, "
          "just type in 0 and I'll tell you.\nNumber of data points: ";
  cin >> N;
  // make sure there was valid input
  while (cin.fail() || (N < 0) || (fmod(N, 1) != 0)) {
    cout << "Invalid input, please enter the number of data points: ";
    cin.clear();
    // clear cin buffer until end of line character
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin >> N;
  }
  // cast N to an integer for array size
  data_points = (int)N;

  // create temp file, check it was created then close it
  ofstream newFile("temp.dat");
  if (!newFile.good()) {
    cout << "Error: could not create temp file.\n";
    return 1;
  }

  double temp;
  for (int i{0}; !inputFile.eof(); i++) {
    inputFile >> temp;
    while (inputFile.fail()) {
      inputFile.clear();
      // delete until the newline character \n
      inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (inputFile.eof()) {
        inputFile.clear();
        inputFile.ignore();
      } else {
        inputFile >> temp;
        cout << "Warning: bad data point. Skipping.\n";
      }
    }
    if (inputFile.eof()) {
      // end of file, clear the fail bit and ignore the eof, do not write to
      // newFile
      inputFile.clear();
      inputFile.ignore();
    } else {
      // not end of file, dump into new file followed by a newline
      newFile << temp << endl;
    }
    data_points = i;
  }

  if (N == 0) {
    // if they didn't know how many data points were in the file, tell them
    cout << "There are " << data_points << " data points in the file.\n";
  } else {
    // if they entered the wrong number of points, tell them that the correct
    // number was used
    if ((int)N != data_points) {
      cout << "You told me that there were " << (int)N
           << " data points in the file but there are actually " << data_points
           << " data points in the file.\nI have used N=" << data_points
           << " in the calculation.\n";
    }
  }

  // close input file input stream
  inputFile.close();
  // close temp file output stream
  newFile.close();

  // open temp file as input stream
  ifstream tempFile("temp.dat");
  if (!tempFile.good()) {
    cout << "Error: could not open temp file.\n";
    return 1;
  }

  // create dynamic sized array
  double *charge = new double[data_points];

  // read data into the array from the clean temp file
  for (int i{0}; i < data_points; i++) {
    tempFile >> charge[i];
  }

  // close temp file input stream
  tempFile.close();

  // calculate values
  double mean = get_mean(charge, data_points);
  double sigma = get_sigma(charge, mean, data_points);
  double sigma_mean = get_sigma_mean(sigma, data_points);

  // garbage collection
  delete[] charge;

  // output calculated values
  cout << "Mean is " << mean << endl;
  cout << "Standard deviation is " << sigma << endl;
  cout << "Standard error in mean is " << sigma_mean << endl;

  // exit
  return 0;
}
