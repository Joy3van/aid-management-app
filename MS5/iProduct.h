/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 4
Section: OOP244SCC
Date: Mar.27th.2019
*/
#ifndef IPRODUCT_H_INCLUDED
#define IPRODUCT_H_INCLUDED

#include <iostream>

namespace ama {
    const int max_length_label = 30;
    const int max_length_sku = 7;
    const int max_length_name = 75;
    const int max_length_unit = 10;
    const int write_condensed = 0;
    const int write_table = 1;
    const int write_human = 2;
    const float tax_rate = 0.13;

    struct iProduct { // default public
        virtual ~iProduct() {};
        virtual std::ostream& write(std::ostream&, int) const = 0;
        virtual std::istream& read(std::istream&, bool) = 0;
        virtual bool operator==(const char*) const = 0;
        virtual double total_cost() const = 0;
        virtual int qtyNeeded() const = 0;
        virtual int qtyAvailable() const = 0;
        virtual const char* name() const = 0;
        virtual int operator+=(int) = 0;
        virtual bool operator>(const iProduct&) const = 0;
    };
}



#endif // IPRODUCT_H_INCLUDED
