/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 3
Section: OOP244SCC
Date: Mar.27th.2019
*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Product.h"

using namespace std;

namespace ama {
    //----------------------------------------Private--------------------------------------------
    // valid function
    bool Product::valid(const char* pro) const {
        return pro != nullptr && pro[0] != '\0' && strlen(pro) <= max_length_name;
    }
    // setPro function
    void Product::setProName(const char* pro) {
        //if (!valid(pro))
        //    proName = nullptr;
       // else {
        proName = new char[strlen(pro) + 1];
        strncpy(proName, pro, strlen(pro) + 1);
        //}
    }
    // badInput function
    void Product::badInput(const char* msg) {
        cin.clear();
        message(msg);
    }
    //----------------------------------------Protected------------------------------------------
    // message function
    void Product::message(const char* pText) {
        err.message(pText);
    }
    bool Product::isClear() const {
        return !err; // calling operator bool() defined in ErrorState
    }
    //----------------------------------------Public---------------------------------------------
    // Zero/one argument constructor
    Product::Product(char pType) : proType(pType) {
        sku[0] = '\0';
        proUnit[0] = '\0';
        proName = nullptr;
        quanHand = 0;
        quanNeed = 0;
        uniPrice = 0.0;
        taxable = false;
    }
    // 7 arguments constructor
    Product::Product(const char* skUnit, const char* pName, const char* pUnit, double price /*= 0*/, int pQtyNeed /*= 0*/, int pQtyHand /*= 0*/, bool taxStat /*= true*/) : proType('N') {
        if(valid(pName)) {
            strncpy(sku, skUnit, max_length_sku);
            setProName(pName);
            strncpy(proUnit, pUnit, max_length_unit);
            uniPrice = price;
            quanNeed = pQtyNeed;
            quanHand = pQtyHand;
            taxable = taxStat;
        }
        else {
            proName = nullptr;
            *this = Product();
        }
    }
    // Copy constructor
    Product::Product(const Product& src) : proType(src.proType) {
        proName = nullptr;
        *this = src; // calling copy assignment operator
    }
    // Destructor
    Product::~Product() {
        delete [] proName;
    }
    // Copy assignment operator
    Product& Product::operator=(const Product& sauce) {
        if(this != &sauce) {// self-assignment checking
            // Shallow copy
            strncpy(sku, sauce.sku, max_length_sku);
            strncpy(proUnit, sauce.proUnit, max_length_unit);
            uniPrice = sauce.uniPrice;
            quanNeed = sauce.quanNeed;
            quanHand = sauce.quanHand;
            taxable = sauce.taxable;
            // Deallocate previous allocated dynamic memory
            delete [] proName;
            // Allocate new dynamic memory
            if (sauce.proName != nullptr) {
                setProName(sauce.proName);
            }
            else {
                proName = nullptr;
            }
        }
        return *this;
    }
    // += operator
    int Product::operator+=(int cnt) {
        cnt > 0 ? quanHand += cnt : 1;
        return quanHand;
    }
    // == operator
    bool Product::operator==(const char* skUni) const {
        return strcmp(sku, skUni) == 0;
    }
    // > operator
    bool Product::operator>(const char* skUni) const {
        return strcmp(sku, skUni) > 0;
    }
    // > operator overload for Product type parameter
    bool Product::operator>(const iProduct& broduct) const {
        if (!isEmpty())
            return strcmp(proName, broduct.name()) > 0;
        return false;
    }
    // isEmpty function
    bool Product::isEmpty() const {
        return sku[0] == '\0' &&
               proUnit[0] == '\0' &&
               proName == nullptr &&
               quanHand == 0 &&
               quanNeed == 0 &&
               uniPrice == 0.0 &&
               taxable == false;
    }
    // read function
    istream& Product::read(istream& is, bool interactive) {
        char tempName[max_length_name];
        if (!interactive) {
            is.getline(sku, max_length_sku + 1, ',');
            is.getline(tempName, max_length_name + 1, ',');
            setProName(tempName);
            is.getline(proUnit, max_length_unit + 1, ',');
            is >> uniPrice;
            is.ignore();
            is >> taxable;
            is.ignore();
            is >> quanHand;
            is.ignore();
            is >> quanNeed;
            is.ignore(2000, '\n');
        }
        else {
            char taxa;
            //Product forRead;
            //forRead.proName = new char[max_length_name + 1];
            cout << right;
            cout << setw(max_length_label) << "Sku: ";
            is >> /*forRead.*/sku;
            cout << setw(max_length_label) << "Name (no spaces): ";
            is >> /*forRead.*/tempName;
            /*forRead.*/setProName(tempName);
            cout << setw(max_length_label) << "Unit: ";
            is >> /*forRead.*/proUnit;
            cout << setw(max_length_label) << "Taxed? (y/n): ";
            is >> taxa;
            if (taxa == 'Y' || taxa == 'y') {
                /*forRead.*/taxable = true;
            }
            else if (taxa == 'N' || taxa == 'n') {
                /*forRead.*/taxable = false;
            }
            else {
                badInput("Only (Y)es or (N)o are acceptable!");
                is.setstate(ios::failbit);
            }
            if (is.good()) {
                cout << setw(max_length_label) <<  "Price: ";
                is >> /*forRead.*/uniPrice;
                if (is.fail()) {
                    badInput("Invalid Price Entry!");
                    is.setstate(ios::failbit);
                }
            }
            if (is.good()) {
                cout << setw(max_length_label) << "Quantity on hand: ";
                is >> /*forRead.*/quanHand;
                if (is.fail()) {
                    badInput("Invalid Quantity Available Entry!");
                    is.setstate(ios::failbit);
                }
            }
            if (is.good()) {
                cout << setw(max_length_label) << "Quantity needed: ";
                is >> /*forRead.*/quanNeed;
                if(is.fail()) {
                    badInput("Invalid Quantity Needed Entry!");
                    is.setstate(ios::failbit);
                }
            }
           // if (isClear())
               // *this = forRead;
            //delete [] /*forRead.*/proName;
        }
        return is;
    }
    // write function
    ostream& Product::write(ostream& os, int writeMode) const {
        if(!isClear()) {
            os << err.message();
            return os;
        }
        else if (isEmpty()) {}
        // condensed
        else if (writeMode == write_condensed) {
            os << proType << "," << sku << "," << proName << "," << proUnit << "," << uniPrice << "," <<
            taxable << "," << quanHand << "," << quanNeed;
        }
        // table
        else if (writeMode == write_table) {
            char tempName[max_length_name + 1];
            char tax[4];
            taxable ? strcpy(tax, "yes") : strcpy(tax, "no"); // Interpret taxable
            os << " " << setw(max_length_sku) << sku << " | ";
            os << left;
            strcpy(tempName, proName);
            if (strlen(proName) > 16) {
                tempName[13] = '\0';
            }
            os << setw(16) << strcat(tempName, "...") << " | " << setw(10) << proUnit << " | ";
            os << right;
            os << setw(7) << setprecision(2) << uniPrice << " | ";
            os << setw(3) << tax << " | ";
            os << setw(6) << quanHand << " | ";
            os << setw(6) << quanNeed << " |";
        }
        // human
        else if (writeMode == write_human) {
            os.setf(ios::fixed);
            os.precision(2);
            os << right;
            os << setw(max_length_label) << "Sku: " << sku << endl;
            os << setw(max_length_label) << "Name: " << proName << endl;
            os << setw(max_length_label) << "Price: " << uniPrice << endl;
            os << setw(max_length_label) << "Price after Tax: " << uniPrice * (taxable ? (1 + tax_rate) : 1 )<< endl;
            os << setw(max_length_label) << "Quantity Available: " << quanHand << " " << proUnit << endl;
            os << setw(max_length_label) << "Quantity Needed: " << quanNeed << " " << proUnit << endl;
        }
        return os;
    }
}
