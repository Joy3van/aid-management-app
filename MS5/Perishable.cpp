/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 5
Section: OOP244SCC
Date: Apr.3rd.2019
*/
#include <iostream>
#include <iomanip>
#include "Perishable.h"

using namespace std;

namespace ama {
    //--------------------------------------Public------------------------------
    // Default constructor
    Perishable::Perishable() : Product('P') {}
        //expiryDate = Date();
   // }
    // write function
    ostream& Perishable::write(std::ostream& os, int writeMode) const {
        Product::write(os, writeMode);
        if (expiryDate.isGood() && Product::isClear()) {
            if (writeMode == write_human) {
                os << setw(max_length_label) << "Expiry Date: " << expiryDate << endl;
            }
            else if (writeMode == write_table) {
                os << " " << expiryDate << " |";
            }
            else if (writeMode == write_condensed) {
                os << "," << expiryDate;
            }
        }
        return os;
    }
    // read function
    istream& Perishable::read(std::istream& is, bool interactive) {
        Date temp;
        if (interactive) {
            Product::read(is, interactive);
            if (is.good()) {
                cout << setw(max_length_label) << "Expiry date (YYYY/MM/DD): ";
                temp.read(is);
                if (is.fail()) {
                    is.setstate(ios::failbit);
                    message("Invalid Date Entry");
                    //is.setstate(ios::failbit);

                }
                else if (temp.status() == error_year) {
                    is.setstate(ios::failbit);
                    message("Invalid Year in Date Entry");
                    //is.setstate(ios::failbit);
                }
                else if (temp.status() == error_mon) {
                    is.setstate(ios::failbit);
                    message("Invalid Month in Date Entry");
                    //is.setstate(ios::failbit);
                }
                else if (temp.status() == error_day) {
                    is.setstate(ios::failbit);
                    message("Invalid Day in Date Entry");
                    //is.setstate(ios::failbit);
                }
                else {
                    expiryDate = temp;
                }
            }
        }
        else { // non-interactive
            Product::read(is, interactive);
            is.ignore();
            expiryDate.read(is);

        }
        return is;
    }
}
