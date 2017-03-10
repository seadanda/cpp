// Matrix manipulator
// Write a class to store and manipulate matrices

#include <cmath>    // pow, sqrt
#include <iostream> // std io

using namespace std;

class matrix // matrix class
{
  // friends of the class
  friend ostream &operator<<(ostream &os, const matrix &mat1); // ostreams
  friend matrix operator>>(istream &ins, matrix &mat1);        // istreams

private:
  // member data
  int row;     // number of rows
  int col;     // number of columns
  double *mat; // pointer to array where matrix is stored

public:
  // default constructor
  matrix() : row{3}, col{3} {
    mat = new double[(col + row * row)];
    // create 3x3 identity matrix
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (j == i) {
          mat[(j + i * row)] = 1;
        } else {
          mat[(j + i * row)] = 0;
        }
      }
    }
  }
  // parametrised constructor
  // matrix(int n, int m) : row{n}, col{m} {}
  // destructor
  ~matrix() { delete[] mat; }

  // accessors
  int get_col() const { return col; }
  int get_row() const { return row; }
  int get_element(const int m, const int n) const;

  // modifiers
  void set_col(const int m) { col = m; }
  void set_row(const int n) { row = n; }

  // overloaded operators
  matrix operator*(const matrix &mat2) const;
};

// get element of matrix
int matrix::get_element(const int m, const int n) const {
  return mat[m + n * row];
}

// overload << operator to define matrix multiplication
matrix matrix::operator*(const matrix &mat2) const {
  if
    row = mat2.get_col() {
      // matrix multiplication is possible
      matrix temp{col, mat2.get_row()};
    }
  else {
    cerr << "Matrix multiplication not possible with these two matrices.\n";
  }
}

// overload << operator to define how a matrix is output
ostream &operator<<(ostream &os, const matrix &mat1) {
  for (int k = 0; k < mat1.row; k++) {
    for (int l = 0; l < mat1.col; l++) {
      os << " " << mat1.get_element(l, k) << " ";
    }
    os << endl;
  }
  return os;
}

// overload << operator to define how a matrix is input
matrix operator>>(istream &ins, matrix &mat1) {
  stringstream buf; // buffer to store the
  char buf;         // buffer to store the separating character
  double element;   // the current element of the matrix
  cin >> element >> buf
}

int main() {
  matrix m1;
  cout << m1;
  return 0;
}
