/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 3
Section: OOP244SCC
Date: Mar.27th.2019
*/
#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include <iostream>
#include "Product.h"

namespace ama {
    double& operator+=(double&, const Product&);
    std::ostream& operator<<(std::ostream&, const Product&);
    std::istream& operator>>(std::istream&, Product&);
}



#endif // UTILITIES_H_INCLUDED
