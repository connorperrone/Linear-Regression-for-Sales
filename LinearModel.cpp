#include "LinearModel.h"

using namespace std;

struct Entry {
  int year;
  double amount;
};

LinearModel::LinearModel(SalesList& salesList) {
  mGraphURL = "";
  vector<Entry> uniqueYearEntries;
  bool notInList;
  for (const Sale& sale : salesList.getSales()) {
    notInList = true;
    for (Entry& e : uniqueYearEntries) {
      if (e.year == sale.getYear()) {
        notInList = false;
        e.amount += sale.getAmount();
      }
    }
    if (notInList) {
      Entry newEntry;
      newEntry.year = sale.getYear();
      newEntry.amount = sale.getAmount();
      uniqueYearEntries.push_back(newEntry);
    }
  }
  if (uniqueYearEntries.size() <= 2) return;
  mMatrixA = Matrix(uniqueYearEntries.size(), 2);
  mMatrixB = Matrix(uniqueYearEntries.size(), 1);
  for (int i = 0; i < mMatrixA.getRows(); i++) {
    mMatrixA.setElement(i + 1, 1, 1);
    mMatrixA.setElement(i + 1, 2, uniqueYearEntries.at(i).year);
    mMatrixB.setElement(i + 1, 1, uniqueYearEntries.at(i).amount);
  }
  cout << "A:\n" << mMatrixA;
  cout << "b:\n" << mMatrixB;
  Matrix aTranspose = mMatrixA.getTranspose();
  cout << "A Transpose:\n" << aTranspose;
  Matrix aTransposeA = aTranspose.multiply(mMatrixA);
  cout << "(A Transpose) * A:\n" << aTransposeA;
  Matrix aTransposeAInverse = aTransposeA.getInverse();
  cout << "Inverse of (A Transpose * A):\n" << aTransposeAInverse;
  Matrix aTransposeB = aTranspose.multiply(mMatrixB);
  cout << "A Transpose * b:\n" << aTransposeB;
  mMatrixX = aTransposeAInverse.multiply(aTransposeB);
  cout << "X:\n" << mMatrixX;

  mPoints.resize(mMatrixB.getRows());
  double c0 = mMatrixX.getElement(1, 1);
  double c1 = mMatrixX.getElement(2, 1);
  double x, y;
  for (int i = 1; i <= mMatrixB.getRows(); i++) {
    x = mMatrixA.getElement(i, 2);
    y = c0 + (c1 * x);
    Point p;
    p.x = x;
    p.y = y;
    mPoints.at(i - 1) = p;
  }
  Point temp;
  bool swapped;
  for (int i = 0; i < mPoints.size() - 1; i++) {
    swapped = false;
    for (int j = 0; j < mPoints.size() - 1 - i; j++) {
      if (mPoints.at(j).x > mPoints.at(j + 1).x) {
        temp = mPoints.at(j);
        mPoints.at(j) = mPoints.at(j + 1);
        mPoints.at(j + 1) = temp;
        swapped = true;
      }
    }
    if (!swapped) break;
  }
  string xValuesString = "", yValuesString = "", linearModelYValuesString = "";
  for (int i = 0; i < mPoints.size(); i++) {
    xValuesString += to_string((int) mPoints.at(i).x);
    for (int j = 1; j <= mMatrixA.getRows(); j++) {
      if (mMatrixA.getElement(j, 2) == mPoints.at(i).x) {
        yValuesString += to_string(mMatrixB.getElement(j, 1));
        break;
      }
    }
    linearModelYValuesString += to_string(mPoints.at(i).y);
    if (i != mPoints.size() - 1) {
      xValuesString += ",";
      yValuesString += ",";
      linearModelYValuesString += ",";
    }
  }
  mGraphURL = "https://quickchart.io/chart/render/zm-481c5861-e2e3-4357-b09d-3d7665a4554d?data1=" + yValuesString + "&labels=" + xValuesString + "&data2=" + linearModelYValuesString;
}

ostream& operator<<(ostream& os, const LinearModel& lm) {
  os << "Line of Best Fit:\nEquation: y = "
     << lm.mMatrixX.getElement(1, 1) << " + ("
     << lm.mMatrixX.getElement(2, 1) << ") * x\n"
     << "Points: ";
  Point p;
  for (int i = 0; i < lm.mPoints.size(); i++) {
    p = lm.mPoints.at(i);
    os << "(" << (int) p.x << ", " << p.y << ")";
    if (i != lm.mPoints.size() - 1) os << " , ";
  }
  return os;
}