// week6.cpp : Matrix manipulator
// A class to store and manipulate matrices
// Author:  Dónal Murray
// Date:	17/03/2017

#include <cmath>    // pow, sqrt
#include <fstream>  // read in matrices from file
#include <iomanip>  // setprecision
#include <iostream> // std io
#include <stdlib.h> // c style exit

using namespace std;

// matrix class which defines addition, subtraction, multiplication and iostream
// behaviour
class matrix // matrix class
{
  // friend functions to overload input and output operator
  friend ostream &operator<<(ostream &os, const matrix &mat1); // ostreams
  friend istream &operator>>(istream &ins, matrix &mat1);      // istreams

private:
  // member data
  int row_ct;      // number of rows
  int col_ct;      // number of columns
  double *data{0}; // pointer to array where matrix elements are stored

public:
  // default constructor
  matrix();
  // parametrised constructor
  matrix(const int row, const int col);
  // destructor - free up memory
  ~matrix() { delete[] data; }
  // copy constructor for deep copy
  matrix(const matrix &mat1);
  // move constructor
  matrix(matrix &&mat1);
  // assignment operator for deep copy
  matrix &operator=(const matrix &mat2);
  // move assignment operator
  matrix &operator=(matrix &&mat2);

  // accessors
  int get_row_ct() const { return row_ct; }
  int get_col_ct() const { return col_ct; }
  int get_size() const { return col_ct * row_ct; } // return length of array
  double get_element(const int &i, const int &j) const;
  double get_det() const; // determinant
  matrix get_submatrix(const int &i, const int &j)
      const; // return submatrix when i row and j col removed

  // modifiers
  void set_element(const int &i, const int &j, const double &value);

  // overloaded operators
  matrix operator+(const matrix &mat2) const; // addition
  matrix operator-(const matrix &mat2) const; // subtraction
  matrix operator*(const matrix &mat2) const; // multiplication
};
// end of class

// default constructor
matrix::matrix() : row_ct{3}, col_ct{3} {
  // create 3x3 matrix and fill with zeroes
  data = new double[(row_ct * col_ct)];
  for (int i = 0; i < row_ct; i++) {
    for (int j = 0; j < col_ct; j++) {
      data[(j + i * col_ct)] = 0;
    }
  }
}

// parametrised constructor
matrix::matrix(const int row, const int col) : row_ct{row}, col_ct{col} {
  // create matrix of the specified size and fill with zeroes
  if (row_ct + col_ct < 2) {
    cerr << "Fatal error: cannot initialise a 0 dimensional matrix\n";
    exit(1);
  }
  data = new double[(row_ct * col_ct)];
  for (int i = 0; i < row_ct; i++) {
    for (int j = 0; j < col_ct; j++) {
      data[(j + i * col_ct)] = 0;
    }
  }
}

// copy constructor for deep copy
matrix::matrix(const matrix &mat1) : row_ct{mat1.row_ct}, col_ct{mat1.col_ct} {
  if (row_ct + col_ct < 2) {
    cerr << "Fatal error: cannot initialise a 0 dimensional matrix\n";
    exit(1);
  }
  // create matrix of the same size and copy other array over
  data = new double[mat1.get_size()];
  for (int i = 0; i < (row_ct * col_ct); i++) {
    data[i] = mat1.data[i];
  }
}

// move constructor
matrix::matrix(matrix &&mat1)
    : data{mat1.data}, row_ct{mat1.row_ct}, col_ct{mat1.col_ct} {
  if (row_ct + col_ct < 2) {
    cerr << "Fatal error: cannot initialise a 0 dimensional matrix\n";
    exit(1);
  }
  // reset mat1
  mat1.data = 0;
  mat1.row_ct = 0;
  mat1.col_ct = 0;
}

// assignment operator for deep copy
matrix &matrix::operator=(const matrix &mat2) {
  // no self assignment
  if (&mat2 == this)
    return *this;

  // delete old array and change member data
  delete[] data;
  row_ct = mat2.row_ct;
  col_ct = mat2.col_ct;

  // make and fill new array
  data = new double[mat2.get_size()];
  for (int i = 0; i < (row_ct * col_ct); i++) {
    data[i] = mat2.data[i];
  }
  return *this;
}

// move assignment operator
matrix &matrix::operator=(matrix &&mat2) {
  // no self assignment
  if (&mat2 == this)
    return *this;

  // delete old array and change member data
  delete[] data;
  row_ct = mat2.row_ct;
  col_ct = mat2.col_ct;

  // make and fill new array
  data = new double[mat2.get_size()];
  for (int i = 0; i < (row_ct * col_ct); i++) {
    data[i] = mat2.data[i];
  }

  // reset rvalue matrix
  mat2.row_ct = 0;
  mat2.col_ct = 0;
  mat2.data = 0;

  return *this;
}

// access an element in the matrix
double matrix::get_element(const int &i, const int &j) const {
  return data[j + i * col_ct];
}

// get the i,j submatrix of the matrix ie the matrix with the ith row and jth
// column deleted
matrix matrix::get_submatrix(const int &i, const int &j) const {
  if ((row_ct == col_ct) && (row_ct > 2)) {
    // matrix is bigger than 2x2 and square - minor is possible
    matrix temp(row_ct - 1, col_ct - 1);
    int kdiff{0}, ldiff; // set to one when i or j encountered to decrement k,l
    for (int k{0}; k < row_ct; k++) {
      ldiff = 0; // reset ldiff value for each row
      if (k == i) {
        // ignore this row, decrement k
        kdiff = 1;
      } else {
        for (int l{0}; l < col_ct; l++) {
          if (l == j) {
            // ignore this element, decrement l
            ldiff = 1;
          } else {
            temp.set_element(k - kdiff, l - ldiff, data[l + k * col_ct]);
          }
        }
      }
    }
    return temp;
  } else {
    cerr << "Error: cannot find submatrix for this matrix.\n";
    return *this;
  }
}

// find the determinant of a matrix or submatrix
double matrix::get_det() const {
  double det{0};
  if ((row_ct == col_ct) && (row_ct + col_ct > 2)) {
    // matrix is square
    if (row_ct == 2) {
      // matrix is 2x2, get determinant
      det += get_element(0, 0) * get_element(1, 1);
      det -= get_element(0, 1) * get_element(1, 0);
    } else {
      int i = 0; // select ith row
      for (int j{0}; j < col_ct; j++) {
        // calculate sum of minors of all elements in ith row
        // det(A) = sum((-1)^(i+j) * a_ij * det(M)) where M is the i,j submatrix
        det += pow(-1, i + j) * get_element(i, j) *
               (get_submatrix(i, j)).get_det();
      }
    }
  }
  return det;
}

// modify an element in the matrix
void matrix::set_element(const int &i, const int &j, const double &value) {
  // put value into the i,j element of matrix array
  data[(j + i * col_ct)] = value;
}

// overload + operator to define matrix addition
matrix matrix::operator+(const matrix &mat2) const {
  if ((row_ct == mat2.row_ct) && (col_ct == mat2.col_ct)) {
    // same dimensions - perform addition
    matrix temp{row_ct, col_ct};
    double sum;
    for (int i = 0; i < row_ct; i++) {
      for (int j = 0; j < col_ct; j++) {
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
matrix matrix::operator-(const matrix &mat2) const {
  if ((row_ct == mat2.row_ct) && (col_ct == mat2.col_ct)) {
    // same dimensions - perform subtraction
    matrix temp{row_ct, col_ct};
    double diff;
    for (int i = 0; i < row_ct; i++) {
      for (int j = 0; j < col_ct; j++) {
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
matrix matrix::operator*(const matrix &mat2) const {
  if (col_ct == mat2.row_ct) {
    // matrix multiplication is possible
    matrix temp{row_ct, mat2.col_ct}; // creat mat1.row x mat2.col matrix
    double element;                   // total of products to make each element
    double product;                   // current product
    for (int i = 0; i < row_ct; i++) {
      for (int j = 0; j < col_ct; j++) {
        element = 0; // reset running total
        // multiply row by column and add to give the new element
        for (int k = 0; k < row_ct; k++) {
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

// overload << operator to define how a matrix is written
ostream &operator<<(ostream &os, const matrix &mat1) {
  // loop through the array and dump the matrix elements to the stream
  for (int i = 0; i < mat1.row_ct; i++) {
    for (int j = 0; j < mat1.col_ct; j++) {
      if (mat1.row_ct == 1) {
        // only one row, use normal brackets
        if (j == 0) {
          // insert left bracket
          os << "( " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " ";
        } else if (j == (mat1.col_ct - 1)) {
          // insert right bracket
          os << " " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " )";
        } else {
          // no brackets
          os << " " << setprecision(3) << mat1.data[j + i * mat1.col_ct] << " ";
        }
      } else if (mat1.col_ct == 1) {
        // only one column, each element has brackets on both sides
        if (i == 0) {
          // insert left bracket
          os << "/ " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " \\";
        } else if (i == (mat1.row_ct - 1)) {
          // insert right bracket
          os << "\\ " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " /";
        } else {
          // no brackets
          os << "|" << setprecision(3) << mat1.data[j + i * mat1.col_ct] << "|";
        }
      } else {
        // more than one row, make big brackets around the whole matrix
        if ((i == 0) && (j == 0)) {
          // insert top left bracket
          os << " / " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " ";
        } else if ((i == 0) && (j == (mat1.col_ct - 1))) {
          // insert top right bracket
          os << " " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " \\";
        } else if ((i == (mat1.row_ct - 1)) && (j == 0)) {
          // insert bottom left bracket
          os << " \\ " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " ";
        } else if ((i == (mat1.row_ct - 1)) && (j == (mat1.col_ct - 1))) {
          // insert bottom right bracket
          os << " " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " /";
        } else if (j == 0) {
          // insert left bracket
          os << "|  " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << " ";
        } else if (j == (mat1.col_ct - 1)) {
          // insert right bracket
          os << " " << setprecision(3) << mat1.data[j + i * mat1.col_ct]
             << "  |";
        } else {
          // no brackets
          os << " " << setprecision(3) << mat1.data[j + i * mat1.col_ct] << " ";
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
  for (int i = 0; i < mat1.row_ct; i++) {
    for (int j = 0; j < mat1.col_ct; j++) {
      cin >> element;                  // read in the first element
      mat1.set_element(i, j, element); // put the element in the array
      cin.ignore();                    // ignore the space
      if (cin.fail()) {
        cerr << "Error: invalid input.\n";
        exit(1);
      }
    }
  }
  return ins;
}

int main() {
  // default constructor
  matrix a1;
  cout << "default constructor a1:\n" << a1;

  // parametrised constructor
  int m{2}, n{2};
  matrix a2{m, n};
  cout << "Enter a 2x2 matrix as a space-separated list: ";
  cin >> a2;
  cout << "parametrised constructor a2:\n" << a2;

  // Deep copy by assignment
  cout << "Deep copy by assignment: define new matrix a3 then copy from a2 to "
          "a3\n";
  matrix a3{m, n};
  cout << "a3:\n" << a3 << endl;
  a3 = a2;
  cout << "a3(after copy):\n" << a3 << endl;
  cout << "a2(after copy):\n" << a2 << endl; // prove a2 is still there

  cout << "Modify contents of original matrix and show assigned matrix is "
          "unchanged\n";
  cout << "Enter a 2x2 matrix to change a2: ";
  cin >> a2;
  cout << "a2:\n" << a2 << endl;
  cout << "a3:\n" << a3 << endl;

  // Deep copy using copy constructor
  cout << "Deep copy using copy constructor, set a4 equal to a2\n";
  matrix a4{a2}; // construct a matrix using an existing matrix
  cout << "a4:\n" << a4;
  cout << "Modify contents of original matrix and show copied matrix is "
          "unchanged\n";
  cout << "Enter a 2x2 matrix to change a2: ";
  cin >> a2;
  cout << "a2:\n" << a2;
  cout << "a4:\n" << a4;

  // Move copy construction demonstration
  cout << "Move copy construction demonstration\n";
  cout << "a3 =\n" << a3 << endl;
  matrix a7(move(a3));
  cout << "a7 =\n" << a7 << endl; // show that a7 took a3's values
  cout << "a3 =\n"
       << a3 << endl; // show that a3 was moved (=0) and not just copied

  // Move assignment demonstration
  cout << "\nMove assignment demonstration\n";
  cout << "a4 =\n" << a4 << endl;
  matrix a8; // declare new matrix with default constructor
  cout << "a8 =\n" << a8 << endl;
  cout << "move a4 to a8\n";
  a8 = move(a4);                  // move a4 to a8
  cout << "a8 =\n" << a8 << endl; // show that a8 took a4's values
  cout << "a4 =\n"
       << a4 << endl; // show that a4 was moved (null) and not just copied

  //
  // matrix operations
  //

  // input two matrices then add, subtract and multiply them
  int row, col; // for reading in dimensions
  cout << "Enter the dimensions of the first matrix A5 (MxN): ";
  cin >> row;
  if (cin.fail()) {
    cerr << "Error: invalid input.\n";
    return 1;
  }
  cin.ignore(); // ignore the x
  cin >> col;
  if (cin.fail()) {
    cerr << "Error: invalid input.\n";
    return 1;
  }
  matrix a5{row, col};
  cout << "Enter A5 as a space-separated list (" << row << "x" << col << " so "
       << row * col << " values): ";
  cin >> a5; // fill matrix

  cout << "Enter the dimensions of the second matrix A6 (MxN): ";
  cin >> row;
  if (cin.fail()) {
    cerr << "Error: invalid input.\n";
    return 1;
  }
  cin.ignore(); // ignore the x
  cin >> col;
  if (cin.fail()) {
    cerr << "Error: invalid input.\n";
    return 1;
  }
  matrix a6{row, col};
  cout << "Enter A6 as a space-separated list (" << row << "x" << col << " so "
       << row * col << " values): ";
  cin >> a6; // fill matrix

  // print both matrices
  cout << "A5 =\n" << a5 << endl << "A6 =\n" << a6 << endl;

  // show off overloaded +-* functions
  if ((a5.get_row_ct() == a6.get_row_ct()) &&
      (a5.get_col_ct() == a6.get_col_ct())) {
    // matrices the same dimensions, do addition and subtraction first
    // multiplication might be impossible
    cout << "A5 + A6 =\n"
         << (a5 + a6) << endl // addition
         << "A5 - A6 =\n"
         << a5 - a6 << endl // subtraction
         << "A5 * A6 =\n"
         << a5 * a6 << endl; // multiplication
  } else {
    // not the same dimensions, addition and subtraction are impossible
    // therefore do multiplication first
    cout << "A5 * A6 =\n"
         << a5 * a6 << endl // multiplication
         << "A5 + A6 =\n"
         << (a5 + a6) << endl // addition
         << "A5 - A6 =\n"
         << a5 - a6 << endl; // subtraction
  }

  // get determinant of a5
  cout << "det(a5) = " << a5.get_det() << endl;

  // exit
  return 0;
}
