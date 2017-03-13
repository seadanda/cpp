// Matrix manipulator
// Write a class to store and manipulate matrices

#include <cmath>    // pow, sqrt
#include <iostream> // std io

using namespace std;

class matrix // matrix class
{
  // friends of the class
  friend ostream &operator<<(ostream &os, const matrix &mat1); // ostreams
  friend istream &operator>>(istream &ins, matrix &mat1);      // istreams

private:
  // member data
  int m;       // number of rows
  int n;       // number of columns
  double *mat; // pointer to array where matrix is stored

public:
  // default constructor
  matrix() : m{3}, n{3} {}

  // parametrised constructor
  matrix(const int row, const int col) : m{row}, n{col} {
    // create matrix of the specified size with a leading diagonal of 1s
    mat = new double[(m + m * n)];
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (j == i) {
          // element lies on leading diagonal
          mat[(j + i * n)] = 1;
        } else {
          // element is off-diagonal
          mat[(j + i * n)] = 0;
        }
      }
    }
  }

  // destructor - free up memory
  ~matrix() { delete[] mat; }

  // accessors
  int get_m() const { return m; }
  int get_n() const { return n; }
  int get_element(const int row, const int col) const;

  // modifiers
  void create(const int row, const int col) {
    mat = new double[(row + row * col)];
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (j == i) {
          // element lies on leading diagonal
          mat[(j + i * col)] = 1;
        } else {
          // element is off-diagonal
          mat[(j + i * col)] = 0;
        }
      }
    }
  }

  // overloaded operators
  matrix operator*(const matrix &mat2) const;
};

// get element of matrix
int matrix::get_element(const int i, const int j) const {
  return mat[j + i * n];
}

// overload << operator to define matrix multiplication
matrix matrix::operator*(const matrix &mat2) const {
  if (n == mat2.m) {
    // matrix multiplication is possible
    matrix temp{m, mat2.n}; // creat mat1.row x mat2.col matrix
  } else {
    cerr << "Matrix multiplication not possible with these two matrices.\n";
  }
}

// overload << operator to define how a matrix is output
ostream &operator<<(ostream &os, const matrix &mat1) {
  for (int i = 0; i < mat1.m; i++) {
    for (int j = 0; j < mat1.n; j++) {
      os << " " << mat1.get_element(i, j) << " ";
    }
    os << endl;
  }
  return os;
}

// overload << operator to define how a matrix is input
istream &operator>>(istream &ins, matrix &mat1) {
  int row, col; // for reading in rows and columns
  cout << "Please enter the dimensions of the matrix in the form MxN where M "
          "is the number of rows and N is the number of columns: ";
  cin >> row;
  cin.ignore();
  cin >> col;
  cout << "OK now enter your " << row << "x" << col
       << " matrix as a list of numbers separated by a space and starting at "
          "the element A_1,1 and ending at the element A_"
       << row << "," << col << ".\n";

  // todo create matrix

  // loop through the number of points specified and take input
  double element; // temporary variable to store the element
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      cin >> element;                    // read in the first element
      mat1.mat[(j + i * col)] = element; // put the element in the array
      cin.ignore();                      // ignore the space
    }
  }
  return ins;
}

int main() {
  matrix m1;
  m1.create(3, 3);
  cout << m1;
  matrix m2;
  cin >> m2;
  cout << m2;
  return 0;
}
