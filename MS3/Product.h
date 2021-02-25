/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 3
Section: OOP244SCC
Date: Mar.26th.2019
*/
#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <iostream>
#include "ErrorState.h"

namespace ama {
    const int max_length_label = 30;
    const int max_length_sku = 7;
    const int max_length_name = 75;
    const int max_length_unit = 10;
    const int write_condensed = 0;
    const int write_table = 1;
    const int write_human = 2;
    const float tax_rate = 0.13;

    class Product {
        const char proType;
        char sku[max_length_sku + 1];
        char proUnit[max_length_unit + 1];
        char* proName;
        int quanHand;
        int quanNeed;
        double uniPrice;
        bool taxable;
        ErrorState err;
        bool valid(const char*) const;
        void setProName(const char*);
        void badInput(const char*);
    protected:
        void message(const char*);
        bool isClear() const;
    public:
        explicit Product(char pType = 'N');
        Product(const char* sku, const char* pName, const char* pUnit, double price = 0.0, int pQtyNeed = 0, int pQtyHand = 0, bool taxStat = true);
        Product(const Product&);
        ~Product();
        Product& operator=(const Product&);
        int operator+=(int);
        bool operator==(const char*) const;
        bool operator>(const char*) const;
        bool operator>(const Product&) const;
        int qtyAvailable() const { return quanHand; }
        int qtyNeeded() const { return quanNeed; }
        double total_cost() const { return uniPrice * quanHand * (taxable ? 1 + tax_rate : 1); }
        bool isEmpty() const;
        std::istream& read(std::istream&, bool);
        std::ostream& write(std::ostream&, int) const;
    };
}
#endif // PRODUCT_H_INCLUDED
