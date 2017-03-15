// Matrix manipulator
// Write a class to store and manipulate matrices

#include <cmath>    // pow, sqrt
#include <iomanip>  // setprecision
#include <iostream> // std io
#include <stdlib.h> // c style exit

using namespace std;

class matrix // matrix class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, const matrix &mat1); // ostreams
  friend istream &operator>>(istream &ins, matrix &mat1);      // istreams

private:
  // member data
  int m;           // number of rows
  int n;           // number of columns
  double *data{0}; // pointer to array where matrix elements are stored

public:
  // parametrised constructor
  matrix(const int row, const int col);
  // copy constructor
  matrix(const matrix &mat1);
  // move constructor
  matrix(matrix &&mat1);
  // destructor - free up memory
  ~matrix() { delete[] data; }

  // accessors
  int get_m() const { return m; }
  int get_n() const { return n; }
  int get_size() const { return n + n * m; }
  double get_element(const int &i, const int &j) const;
  matrix get_minor(const int &i, const int &j) const;

  // modifiers
  void set_element(const int &i, const int &j, const double &value);

  // overloaded operators
  matrix operator+(const matrix &mat2) const; // addition
  matrix operator-(const matrix &mat2) const; // subtraction
  matrix operator*(const matrix &mat2) const; // multiplication

  // assignment operator
  matrix &operator=(const matrix &mat2);
};
// end of class

// parametrised constructor
matrix::matrix(const int row, const int col) : m{row}, n{col} {
  // create matrix of the specified size and fill with zeroes
  if (m + n < 2) {
    cerr << "Fatal error: cannot initialise a 0 dimensional matrix\n";
    exit(1);
  }
  data = new double[(n + m * n)];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      data[(j + i * n)] = 0;
    }
  }
}

// copy constructor
matrix::matrix(const matrix &mat1) : m{mat1.m}, n{mat1.n} {
  if (m + n < 2) {
    cerr << "Fatal error: cannot initialise a 0 dimensional matrix\n";
    exit(1);
  }
  // create matrix of the same size and copy other array over
  data = new double[mat1.get_size()];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      data[(j + i * n)] = mat1.data[(j + i * n)];
    }
  }
}

// move constructor
matrix::matrix(matrix &&mat1) : data{mat1.data}, m{mat1.m}, n{mat1.n} {
  if (m + n < 2) {
    cerr << "Fatal error: cannot initialise a 0 dimensional matrix\n";
    exit(1);
  }
  // reset mat1
  mat1.data = 0;
  mat1.m = 0;
  mat1.n = 0;
}

// access an element in the matrix
double matrix::get_element(const int &i, const int &j) const {
  return data[j + i * n];
}

// get the i,j th minor of the matrix
matrix matrix::get_minor(const int &i, const int &j) const {
  if ((m == n) && (m > 2)) {
    // matrix is bigger than 2x2 and square - minor is possible
    matrix temp(m - 1, n - 1);
    int kdiff{0}, ldiff; // set to one when i or j encountered to decrement k,l
    for (int k{0}; k < m; k++) {
      ldiff = 0; // reset ldiff value for each row
      if (k == i) {
        // ignore this row, decrement k
        kdiff = 1;
      } else {
        for (int l{0}; l < n; l++) {
          if (l == j) {
            // ignore this element, decrement l
            ldiff = 1;
          } else {
            temp.set_element(k - kdiff, l - ldiff, data[l + k * n]);
          }
        }
      }
    }
    return temp;
  } else {
    cerr << "Error: no minors exist for this matrix.\n";
    exit(1);
  }
}

// modify an element in the matrix
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
      }
    }
    return temp;
  } else {
    cerr << "Matrix addition and subtraction not possible with these two "
            "matrices.\n";
    exit(1);
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
      }
    }
    return temp;
  } else {
    cerr << "Matrix addition and subtraction not possible with these two "
            "matrices.\n";
    exit(1);
  }
}

// overload * operator to define matrix multiplication
matrix matrix::operator*(const matrix &mat2) const // return product
{
  if (n == mat2.m) {
    // matrix multiplication is possible
    matrix temp{m, mat2.n}; // creat mat1.row x mat2.col matrix
    double element;         // total of products to make each element
    double product;         // current product
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        element = 0; // reset running total
        // multiply row by column and add to give the new element
        for (int k = 0; k < m; k++) {
          product = get_element(i, k) * mat2.get_element(k, j);
          element += product;
        }
        // push element to temp matrix
        temp.set_element(i, j, element);
      }
    }
    return temp;
  } else {
    cerr << "Matrix multiplication not possible with these two matrices.\n";
    exit(1);
  }
}

// overload = operator to define how matrices are assigned
matrix &matrix::operator=(const matrix &mat2) // assignment
{
  // no self assignment
  if (&mat2 == this)
    return *this;

  // delete old array and change member data
  delete[] data;
  m = mat2.m;
  n = mat2.n;

  // make and fill new array
  data = new double[mat2.get_size()];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      data[(j + i * n)] = mat2.data[(j + i * n)];
    }
  }
  return *this;
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
      } else if (mat1.n == 1) {
        // only one column, each element has brackets on both sides
        if (i == 0) {
          // insert left bracket
          os << "/ " << setprecision(3) << mat1.data[j + i * mat1.n] << " \\";
        } else if (i == (mat1.m - 1)) {
          // insert right bracket
          os << "\\ " << setprecision(3) << mat1.data[j + i * mat1.n] << " /";
        } else {
          // no brackets
          os << "|" << setprecision(3) << mat1.data[j + i * mat1.n] << "|";
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
  // use parametrised constructor and print out its default values
  matrix m_default{3, 3};
  cout << "3x3 default matrix - filled with zeroes:\n" << m_default;

  // input two matrices then add, subtract and multiply them
  int row, col; // for reading in dimensions
  cout << "Enter the dimensions of the first matrix A1 (MxN): ";
  cin >> row;
  cin.ignore(); // ignore the x
  cin >> col;
  matrix a1{row, col};
  cout << "Enter A2 as a space-separated list (" << row << "x" << col << " so "
       << row * col << " values): ";
  cin >> a1; // fill matrix

  cout << "Enter the dimensions of the second matrix A2 (MxN): ";
  cin >> row;
  cin.ignore(); // ignore the x
  cin >> col;
  matrix a2{row, col};
  cout << "Enter A2 as a space-separated list (" << row << "x" << col << " so "
       << row * col << " values): ";
  cin >> a2; // fill matrix

  // print both matrices
  cout << "A1 =\n" << a1 << endl << "A2 =\n" << a2 << endl;

  // show off overloaded +-* functions
  if ((a1.get_m() == a2.get_m()) && (a1.get_n() == a2.get_n())) {
    // matrices the same dimensions, do addition and subtraction first
    // multiplication might be impossible
    cout << "A1 + A2 =\n" << (a1 + a2) << endl; // addition
    cout << "A1 - A2 =\n" << a1 - a2 << endl;   // subtraction
    cout << "A1 * A2 =\n" << a1 * a2 << endl;   // multiplication
  } else {
    // not the same dimensions, addition and subtraction are impossible
    // therefore do multiplication first
    cout << "A1 * A2 =\n" << a1 * a2 << endl;   // multiplication
    cout << "A1 + A2 =\n" << (a1 + a2) << endl; // addition
    cout << "A1 - A2 =\n" << a1 - a2 << endl;   // subtraction
  }

  // get minors of A1
  for (int i{0}; i < a1.get_m(); i++) {
    for (int j{0}; j < a1.get_n(); j++) {
      cout << i + 1 << "," << j + 1 << " minor of A1 =" << endl
           << a1.get_minor(i, j) << endl;
    }
  }

  // exit
  return 0;
}
