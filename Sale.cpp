#include "Sale.h"

int Sale::sNextSaleID = 1;

Sale::Sale(int year, double amount) {
  mYear = year;
  mAmount = amount;
  mSaleID = sNextSaleID++;
}

ostream& operator<<(ostream& os, const Sale& s) {
  os << "Sale [Year = " << s.mYear << ", Amount = $" << s.mAmount << ", Sale ID = " << s.mSaleID << "]";
  return os;
}