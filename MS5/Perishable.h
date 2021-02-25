/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 5
Section: OOP244SCC
Date: Apr.3rd.2019
*/
#ifndef PERISHABLE_H_INCLUDED
#define PERISHABLE_H_INCLUDED

#include <iostream>
#include "Date.h"
#include "Product.h"

namespace ama {
    class Perishable : public Product {
        Date expiryDate;
    public:
        Perishable();
        std::ostream& write(std::ostream&, int) const;
        std::istream& read(std::istream&, bool);
    };
}



#endif // PERISHABLE_H_INCLUDED
