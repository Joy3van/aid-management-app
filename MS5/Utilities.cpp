/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 3
Section: OOP244SCC
Date: Mar.26th.2019
*/
#include <iostream>
#include "iProduct.h"
#include "Product.h"
#include "Perishable.h"
#include "Utilities.h"

using namespace std;

namespace ama {
    double& operator+=(double& total, const iProduct& prod) {
        return total+= prod.total_cost();
    }
    ostream& operator<<(std::ostream& os, const iProduct& prod) {
        prod.write(os, write_human);
        return os;
    }
    istream& operator>>(std::istream& is, iProduct& prod) {
        prod.read(is, true);
        return is;
    }
    iProduct* createInstance(char tag) {
        iProduct* broduct = nullptr;
        if (tag == 'N' || tag == 'n') {
            broduct = new Product();
        }
        if (tag == 'P' || tag == 'p') {
            broduct = new Perishable();
        }
        return broduct;
    }
}
