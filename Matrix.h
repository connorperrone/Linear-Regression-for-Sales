#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Matrix {

private:
  int mRows, mColumns, mMostDigits;
  vector<vector<double>> mRowsColumns;
  static bool isWholeNumber(string valueString, int dotIndex);

public:
  Matrix() {}

  Matrix(int rows, int columns);

  int getRows() { return mRows; }

  int getColumns() { return mColumns; }

  double getElement(int rowNumber, int columnNumber) const { return mRowsColumns.at(rowNumber - 1).at(columnNumber - 1); }

  void setElement(int rowNumber, int columnNumber, double value);

  Matrix getTranspose();

  Matrix multiply(Matrix& other);

  double getDeterminant();

  Matrix getInverse();

  bool operator==(const Matrix& other);

  friend ostream& operator<<(ostream& os, const Matrix& m);

};

#endif