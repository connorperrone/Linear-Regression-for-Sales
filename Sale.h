#ifndef SALE_H
#define SALE_H

#include <iostream>

using namespace std;

class Sale {

  private:
    int mYear;
    double mAmount;
    int mSaleID;
    static int sNextSaleID;

  public:
    Sale(int year, double amount);

    int getYear() const { return mYear; }
    double getAmount() const { return mAmount; }
    int getSaleID() const { return mSaleID; }

    void setYear(int year) { mYear = year; }
    void setAmount(int amount) { mAmount = amount; }
    void setSaleID(int saleID) { mSaleID = saleID; }

    bool operator==(const Sale& other) {
      return mSaleID == other.mSaleID && mYear == other.mYear && mAmount == other.mAmount;
    }

    friend ostream& operator<<(ostream& os, const Sale& s);
};

#endif