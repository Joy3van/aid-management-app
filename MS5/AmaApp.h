/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 5
Section: OOP244SCC
Date: Apr.3rd.2019
*/
#ifndef AMAAPP_H_INCLUDED
#define AMAAPP_H_INCLUDED

#include <iostream>
#include <iomanip>
#include "iProduct.h"

namespace ama {
    class AmaApp {
        char m_filename[256];
        iProduct* m_products[100];
        int m_noOfProducts;
        //void unik() const;
        void pause() const;
        int menu() const;
        void loadProductRecords();
        void saveProductRecords() const;
        void listProducts() const;
        void deleteProductRecord(iProduct*);
        //void sort();
        iProduct* find(const char*) const;
        void addQty(iProduct*);
        void addProduct(char);
    public:
        AmaApp(const char*);
        ~AmaApp();
        int run();
    };
    // A function to help print the lines
    /*void printBar(int size = 64, std::ostream& out = std::cout) {
	out << std::setfill('-') << std::setw(size) << "" << std::setfill(' ') << std::endl;
    }*/
}


#endif // AMAAPP_H_INCLUDED
