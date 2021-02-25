/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 3
Section: OOP244SCC
Date: Mar.26th.2019
*/
#include <iostream>
#include "Product.h"
#include "Utilities.h"

using namespace std;

namespace ama {
    double& operator+=(double& total, const Product& prod) {
        return total+= prod.total_cost();
    }
    ostream& operator<<(std::ostream& os, const Product& prod) {
        prod.write(os, write_human);
        return os;
    }
    istream& operator>>(std::istream& is, Product& prod) {
        prod.read(is, true);
        return is;
    }
}
