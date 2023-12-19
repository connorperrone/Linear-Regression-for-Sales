#include "LinearModel.h"
#include "SalesList.h"
#include <iostream>

/*

Graph Rendering using https://quickchart.io/

API Endpoint: https://quickchart.io/chart/render/zm-481c5861-e2e3-4357-b09d-3d7665a4554d

Link to edit format: https://quickchart.io/chart-maker/edit/zm-481c5861-e2e3-4357-b09d-3d7665a4554d

Note: This endpoint might expire in the future

Also note that sales' years must be spaced apart by the same number of years

*/

int main() {
  int choice;
  SalesList salesList = SalesList();
  LinearModel lm = LinearModel(salesList);
  do {
    cout << "\n==================================================\n"
         << "||                Sales Analysis                ||\n"
         << "||            with Linear Regression            ||\n"
         << "==================================================\n"
         << "||  Options:                                    ||\n"
         << "||  (1) Add data for a sale                     ||\n"
         << "||  (2) Remove data for a sale                  ||\n"
         << "||  (3) List existing sales data                ||\n"
         << "||  (4) Calculate linear model                  ||\n"
         << "||  (5) Get line of best fit graph URL          ||\n"
         << "||  (6) Estimate sales for future year          ||\n"
         << "||  (7) Exit                                    ||\n"
         << "==================================================\n";
    cout << "Select an option (1, 2, 3, 4, 5, 6, or 7): ";
    cin >> choice;
    double year, amount;
    int saleID;
    switch (choice) {
      case 1: {
        cout << "Enter year of sale: ";
        cin >> year;
        cout << "Enter amount of sale: $";
        cin >> amount;
        Sale sale = Sale(year, amount);
        salesList.addSale(sale);
        cout << "Added: " << sale << endl;
        break;
      }
      case 2: {
        cout << "Enter sale ID: ";
        cin >> saleID;
        if (salesList.removeSale(saleID))
          cout << "Removed: Sale with ID = " << saleID << endl;
        else
          cout << "Unable to find a sale with that ID." << endl;
        break;
      }
      case 3: {
        cout << salesList;
        break;
      }
      case 4: {
        if (salesList.getSales().size() <= 1) {
          cout << "Unable to calculate linear model. Try adding sales from at least 3 different years." << endl;
          break;
        }
        lm = LinearModel(salesList);
        if (lm.getGraphURL() == "") {
          cout << "Unable to calculate linear model. Try adding sales from at least 3 different years." << endl;
          break;
        }
        cout << lm << endl;
        break;
      }
      case 5: {
        if (lm.getGraphURL() == "") {
          cout << "Calculate the linear model before viewing the graph." << endl;
          break;
        }
        cout << "\nGraph URL:\n" << lm.getGraphURL() << endl;
        break;
      }
      case 6: {
        if (lm.getGraphURL() == "") {
          cout << "Calculate the linear model before estimating future sales." << endl;
          break;
        }
        cout << "Enter year: ";
        cin >> year;
        cout << "\nEstimated sales in " << (int) year << ": $" << lm.getFutureSalesEstimate(year) << endl;
        break;
      }
      case 7: {
        exit(0);
        break;
      }
      default: {
        cout << "Invalid choice. Please choose 1, 2, 3, 4, 5, 6, or 7.\n";
      }
    }
  } while (choice != 7);
}