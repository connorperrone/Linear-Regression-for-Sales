#include "SalesList.h"

bool SalesList::removeSale(int saleID) {
  for (auto it = mSales.begin(); it != mSales.end(); ++it) {
    if (it->getSaleID() == saleID) {
          mSales.erase(it);
      return true;
    }
  }
  return false;
}

bool SalesList::operator==(const SalesList& other) {
  if (mSales.size() != other.mSales.size()) return false;
  int index = 0;
  for (auto it = mSales.begin(); it != mSales.end(); ++it) {
    Sale otherSale = other.mSales.at(index++);
    if (it->getSaleID() != otherSale.getSaleID() || it->getYear() != otherSale.getYear() || it->getAmount() != otherSale.getAmount()) return false;
  }
  return true;
}

ostream& operator<<(ostream& os, const SalesList& sl) {
  os << "Sales List:\n";
  for (Sale s : sl.mSales) os << s << endl;
  return os;
}