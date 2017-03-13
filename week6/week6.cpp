// Matrix manipulator
// Write a class to store and manipulate matrices

#include <cmath>    // pow, sqrt
#include <iomanip>  // setprecision
#include <iostream> // std io

using namespace std;

class matrix // matrix class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, const matrix &mat1); // ostreams
  friend istream &operator>>(istream &ins, matrix &mat1);      // istreams

private:
  // member data
  int m;        // number of rows
  int n;        // number of columns
  double *data; // pointer to array where matrix elements are stored

public:
  // parametrised constructor
  matrix(const int row, const int col) : m{row}, n{col} {
    // create matrix of the specified size and fill with zeroes
    data = new double[(n + m * n)];
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        data[(j + i * n)] = 0;
      }
    }
  }

  // destructor - free up memory
  //~matrix() { delete[] data; }

  // accessors
  int get_m() const { return m; }
  int get_n() const { return n; }
  double get_element(const int &i, const int &j) const {
    return data[j + i * n];
  }

  // modifiers
  void set_element(const int &i, const int &j, const double &value);

  // overloaded operators
  matrix operator+(const matrix &mat2) const; // addition
  matrix operator-(const matrix &mat2) const; // subtraction
  matrix operator*(const matrix &mat2) const; // multiplication
};

// set an element in the matrix
void matrix::set_element(const int &i, const int &j, const double &value) {
  // put value into the i,j element of matrix array
  data[(j + i * n)] = value;
}

// overload + operator to define matrix addition
matrix matrix::operator+(const matrix &mat2) const // return sum
{
  if ((m == mat2.m) && (n == mat2.n)) {
    // same dimensions - perform addition
    matrix temp{m, n};
    double sum;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        sum = get_element(i, j) + mat2.get_element(i, j);
        temp.set_element(i, j, sum);
        cout << sum << endl;
      }
    }
    return temp;
  } else {
    cerr << "Matrix addition not possible with these two matrices.\n";
  }
}

// overload - operator to define matrix subtraction
matrix matrix::operator-(const matrix &mat2) const // return difference
{
  if ((m == mat2.m) && (n == mat2.n)) {
    // same dimensions - perform subtraction
    matrix temp{m, n};
    double diff;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        diff = get_element(i, j) - mat2.get_element(i, j);
        temp.set_element(i, j, diff);
        cout << diff << endl;
      }
    }
    return temp;
  } else {
    cerr << "Matrix subtraction not possible with these two matrices.\n";
  }
}

// overload * operator to define matrix multiplication
matrix matrix::operator*(const matrix &mat2) const // return product
{
  if (n == mat2.m) {
    // matrix multiplication is possible
    matrix temp{m, mat2.n}; // creat mat1.row x mat2.col matrix
    return temp;
  } else {
    cerr << "Matrix multiplication not possible with these two matrices.\n";
  }
}

// overload << operator to define how a matrix is written
ostream &operator<<(ostream &os, const matrix &mat1) {
  // loop through the array and dump the matrix elements to the stream
  for (int i = 0; i < mat1.m; i++) {
    for (int j = 0; j < mat1.n; j++) {
      if (mat1.m == 1) {
        // only one row, use normal brackets
        if (j == 0) {
          // insert left bracket
          os << "( " << setprecision(3) << mat1.data[j + i * mat1.n] << " ";
        } else if (j == (mat1.n - 1)) {
          // insert right bracket
          os << " " << setprecision(3) << mat1.data[j + i * mat1.n] << " )";
        } else {
          // no brackets
          os << " " << setprecision(3) << mat1.data[j + i * mat1.n] << " ";
        }
      } else {
        // more than one row, make big brackets around the whole matrix
        if ((i == 0) && (j == 0)) {
          // insert top left bracket
          os << " / " << setprecision(3) << mat1.data[j + i * mat1.n] << " ";
        } else if ((i == 0) && (j == (mat1.n - 1))) {
          // insert top right bracket
          os << " " << setprecision(3) << mat1.data[j + i * mat1.n] << " \\";
        } else if ((i == (mat1.m - 1)) && (j == 0)) {
          // insert bottom left bracket
          os << " \\ " << setprecision(3) << mat1.data[j + i * mat1.n] << " ";
        } else if ((i == (mat1.m - 1)) && (j == (mat1.n - 1))) {
          // insert bottom right bracket
          os << " " << setprecision(3) << mat1.data[j + i * mat1.n] << " /";
        } else if (j == 0) {
          // insert left bracket
          os << "|  " << setprecision(3) << mat1.data[j + i * mat1.n] << " ";
        } else if (j == (mat1.n - 1)) {
          // insert right bracket
          os << " " << setprecision(3) << mat1.data[j + i * mat1.n] << "  |";
        } else {
          // no brackets
          os << " " << setprecision(3) << mat1.data[j + i * mat1.n] << " ";
        }
      }
    }
    os << endl;
  }
  return os;
}

// overload << operator to define how a matrix is read
istream &operator>>(istream &ins, matrix &mat1) {
  double element; // temporary variable to store the element

  // loop through the array and fill the matrix from the stream
  for (int i = 0; i < mat1.m; i++) {
    for (int j = 0; j < mat1.n; j++) {
      cin >> element;                  // read in the first element
      mat1.set_element(i, j, element); // put the element in the array
      cin.ignore();                    // ignore the space
    }
  }
  return ins;
}

int main() {
  // define two matrices and add them, subtract them and then multiply them
  matrix a1{2, 2};
  matrix a2{2, 2};
  cout << "enter 4 values for A1: ";
  cin >> a1;
  cout << "enter 4 values for A2: ";
  cin >> a2;
  cout << "A1 =\n"
       << a1 << endl
       << "A2 =\n"
       << a2 << endl
       << "A1 + A2 =\n"
       << (a1 + a2) << endl
       << "A1 - A2 =\n"
       << a1 - a2 << endl
       << "A1 * A2 =\n"
       << a1 * a2 << endl;

  // use parametrised constructor and print out its default values
  matrix m1{3, 3};
  cout << "Default values of parametrised constructor:\n" << m1;

  // create matrix
  int row, col; // for reading in rows and columns
  cout << "Enter the dimensions of the matrix in the form RxC: ";
  cin >> row;
  cin.ignore(); // ignore the x
  cin >> col;
  matrix m2{row, col};

  // fill matrix and print it out
  cout << "Enter the " << row << "x" << col
       << " matrix as a space-separated list.\n";
  cin >> m2;
  cout << "The matrix A2:\n" << m2;
  return 0;
}
