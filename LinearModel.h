#ifndef LINEARMODEL_H
#define LINEARMODEL_H

#include "Matrix.h"
#include "SalesList.h"

struct Point {
  double x, y;
};

class LinearModel {

  private:
    Matrix mMatrixA;
    Matrix mMatrixB;
    Matrix mMatrixX;
    vector<Point> mPoints;
    string mGraphURL;

  public:
    LinearModel(SalesList& salesList);

    Point getPoint(int index) { return mPoints.at(index); }

    string getGraphURL() { return mGraphURL; }

    double getFutureSalesEstimate(int year) { return mMatrixX.getElement(1, 1) + (mMatrixX.getElement(2, 1) * year); }

    bool operator==(const LinearModel& other) { return mMatrixA == other.mMatrixA && mMatrixB == other.mMatrixB && mMatrixX == other.mMatrixX && mGraphURL == other.mGraphURL; }

    friend ostream& operator<<(ostream& os, const LinearModel& lm);
};

#endif