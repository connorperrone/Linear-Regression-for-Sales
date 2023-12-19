#include "Matrix.h"
#include <iomanip>

Matrix::Matrix(int rows, int columns) {
  mRows = rows;
  mColumns = columns;
  mMostDigits = 1;
  
  mRowsColumns.resize(rows);
  for (auto rowIter = mRowsColumns.begin(); rowIter != mRowsColumns.end(); ++rowIter) {
    rowIter->resize(columns);
  }
}

bool Matrix::isWholeNumber(string valueString, int dotIndex) {
  bool wholeNumber = true;
  for (int i = dotIndex + 1; i < valueString.length(); i++) {
    if (valueString[i] != '0') {
      wholeNumber = false;
      break;
    }
  }
  return wholeNumber;
}

void Matrix::setElement(int rowNumber, int columnNumber, double value) {
  if (rowNumber < 1 || rowNumber > mRows || columnNumber < 1 || columnNumber > mColumns) return;
  mRowsColumns.at(rowNumber - 1).at(columnNumber - 1) = value;
  string valueString = to_string(value);
  int dotIndex = valueString.find_first_of('.');
  bool wholeNumber = isWholeNumber(valueString, dotIndex);
  int digits = wholeNumber ? dotIndex : dotIndex + 3;
  if (digits > mMostDigits) mMostDigits = digits;
  return;
}

Matrix Matrix::getTranspose() {
  /*
  ---            ---         ---            ---
  |  10   2    30  |         |  10   4    70  |
  |  4    50   6   |   -->   |  2    50   8   |
  |  70   8    90  |         |  30   6    90  |
  ---            ---         ---            ---

  1 2       1 3 5
  3 4  -->  2 4 6
  5 6
  */
  Matrix transpose = Matrix(mColumns, mRows);
  for (int row = 0; row < transpose.mRows; row++) {
    for (int column = 0; column < transpose.mColumns; column++) {
      transpose.setElement(row + 1, column + 1, mRowsColumns.at(column).at(row));
    }
  }
  return transpose;
}

Matrix Matrix::multiply(Matrix& other) {
  /*
  1 2     1 3 5       5  11 17
  3 4  *  2 4 6  -->  11 25 39
  5 6                 17 39 61

  c11 = m11 * o11 + m12 * o21
  c12 = m11 * o12 + m12 * o22
  c13 = m11 * o13 + m12 * o23
  c21 = m21 * o11 + m22 * o21
  c22 = m21 * o12 + m22 * o22
  c23 = m21 * o13 + m22 * o23
  c31 = m31 * o11 + m32 * o21
  c32 = m31 * o12 + m32 * o22
  c33 = m31 * o13 + m32 * o23
  */
  Matrix result = Matrix(mRows, other.mColumns);
  double value;
  for (int row = 0; row < result.mRows; row++) {
    for (int column = 0; column < result.mColumns; column++) {
      value = 0;
      for (int i = 0; i < mColumns; i++) {
        value += (mRowsColumns.at(row).at(i) * other.mRowsColumns.at(i).at(column));
      }
      result.setElement(row + 1, column + 1, value);
    }
  }
  return result;
}

// For 2x2 matrices
Matrix Matrix::getInverse() {
  double determinantReciprocal = 1 / ((mRowsColumns.at(0).at(0) * mRowsColumns.at(1).at(1)) - (mRowsColumns.at(0).at(1) * mRowsColumns.at(1).at(0)));
  Matrix inverse = Matrix(2, 2);
  inverse.setElement(1, 1, determinantReciprocal * mRowsColumns.at(1).at(1));
  inverse.setElement(1, 2, determinantReciprocal * -mRowsColumns.at(0).at(1));
  inverse.setElement(2, 1, determinantReciprocal * -mRowsColumns.at(1).at(0));
  inverse.setElement(2, 2, determinantReciprocal * mRowsColumns.at(0).at(0));
  return inverse;
}

bool Matrix::operator==(const Matrix& other) {
  if (mRows != other.mRows || mColumns != other.mColumns) return false;
  for (int row = 0; row < mRows; row++) {
    vector<double> rowVector = mRowsColumns.at(row);
    vector<double> otherRowVector = other.mRowsColumns.at(row);
    for (int column = 0; column < mColumns; column++) {
      if (rowVector.at(column) != otherRowVector.at(column)) return false;
    }
  }
  return true;
}

ostream& operator<<(ostream& os, const Matrix& m) {
  /*
  ---            ---
  |  10   2    30  |
  |  4    50   6   |
  |  70   8    90  |
  ---            ---
  */
  string topBottomLine = "---";
  for (int i = 0; i < ((m.mMostDigits * m.mColumns) + (3 * (m.mColumns - 1))); i++) {
    topBottomLine += " ";
  }
  topBottomLine += "---";
  os << topBottomLine;
  vector<double> rowVector;
  string valueString;
  int dotIndex;
  for (int row = 0; row < m.mRows; row++) {
    rowVector = m.mRowsColumns.at(row);
    os << "\n|  ";
    for (int column = 0; column < m.mColumns; column++) {
      valueString = to_string(rowVector.at(column));
      dotIndex = valueString.find_first_of('.');
      os << fixed << setprecision(m.isWholeNumber(valueString, dotIndex) ? 0 : 2) << left << setw(m.mMostDigits) << rowVector.at(column);
      if (column != (m.mColumns - 1)) os << "   ";
    }
    os << "  |";
  }
  os << endl << topBottomLine << endl;
  return os;
}