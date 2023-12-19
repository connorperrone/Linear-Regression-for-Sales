#ifndef SALESLIST_H
#define SALESLIST_H

#include "Sale.h"
#include <vector>

class SalesList {

  private:
    vector<Sale> mSales;

  public:
    void addSale(const Sale& sale) { mSales.push_back(sale); }
    bool removeSale(int saleID);

    vector<Sale> getSales() const { return mSales; }

    bool operator==(const SalesList& other);

    friend ostream& operator<<(ostream& os, const SalesList& sl);
};

#endif