/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 5
Section: OOP244SCC
Date: Apr.3rd.2019
*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>
#include <iomanip>
#include "AmaApp.h"
#include "Utilities.h"
using namespace std;

namespace ama{
    //AmaApp constructor
    AmaApp::AmaApp(const char* fname){

        strcpy(m_filename, fname);
        for(int i = 0; i < 100; i++){
            m_products[i] = nullptr;
        }
        m_noOfProducts = 0;
        loadProductRecords();
    }
    //Pause function asking user to press enter in order to continue
    void AmaApp::pause()const{
        cout  <<  "Press Enter to continue...";
        cin.ignore();
        cout  <<  endl;
    }
    //Destructor of AmaApp object
    AmaApp::~AmaApp(){
        for (int i = 0; i < 100; i++){
            delete m_products[i];
            m_products[i] = nullptr;
        }
    }
    //Function to display menu interface for the program
    int AmaApp::menu()const{
        int select;
        cout << "Disaster Aid Supply Management Program" << endl;
        cout << "--------------------------------------" << endl;
        cout << "1- List products" << endl;
        cout << "2- Search product" << endl;
        cout << "3- Add non-perishable product" << endl;
        cout << "4- Add perishable product" << endl;
        cout << "5- Add to product quantity" << endl;
        cout << "6- Delete product" << endl;
        cout << "7- Sort products" << endl;
        cout << "0- Exit program" << endl;
        cout << "> ";
        cin >> select;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return (select >= 0 && select <= 7) ? select : -1;
    }
    //Function to read from the file and initialize array of iProducts
    void AmaApp::loadProductRecords(){
        for (int i = 0; i < 100; i++){
            delete m_products[i];
            m_products[i] = nullptr;
        }
        int index = 0;
        ifstream inventory;
        inventory.open(m_filename, ios::in);
        if(!inventory.fail()){
        char type;
            for(index=0; !inventory.eof(); index++){
                inventory>>type;
                if(inventory.eof()){break;}
                iProduct* temp=createInstance(type);
                if(temp!=nullptr){
                    m_products[index]=temp;
                    inventory.ignore();
                    m_products[index]->read(inventory, false);
                }
            }
        }
        /*if(!inventory.fail()){
            do {
                char type;
                inventory >> type;
                iProduct* temp = createInstance(type);
                if(temp != nullptr) {
                    m_products[index] = temp;
                    inventory.ignore();
                    m_products[index]->read(inventory, false);
                    index++;
                }
            } while (!inventory.eof());
        }*/
        else {
            cerr << "Read error!";
            inventory.clear();
        }
        m_noOfProducts = index;
        inventory.close();
    }
    //Function to save the changes made to iProduct array members into the file
    void AmaApp::saveProductRecords()const{
        ofstream records;
        records.open(m_filename);
        if(!records.fail()) {
            for(int i = 0; i < m_noOfProducts; i++){
                m_products[i]->write(records, write_condensed);
                records << '\n';
            }
        }
        else {
            cerr << "Files is not open" << endl;
        }
        records.close();
    }
    //Function to list the array of iProducts
    void AmaApp::listProducts()const{
        double totalCost = 0;
        cout.setf(ios::fixed);
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
        cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;
        for(int i = 0; i < m_noOfProducts; i++){
            cout << "|";
            cout << setw(4) << right << i+1 << " |";
            m_products[i]->write(cout, write_table);
            cout << endl;
            totalCost += *m_products[i];
        }
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "|                                                      Total cost of support ($): | " << setw(10) << right << setprecision(2) << totalCost << " |" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl << endl;
        pause();

    }
    //Function used to find iProduct by SKU
    iProduct* AmaApp::find(const char* sku)const{
        iProduct* temp = nullptr;
        for(int i = 0; i < m_noOfProducts; i++){
            if(*m_products[i] == sku){
                    temp = m_products[i];
                    break;
            }
        }
        return temp;
    }
    //Function used to add quantity to available iProducts
    void AmaApp::addQty(iProduct* product){
        int number;
        product->write(cout, write_human);
        cout << endl << endl;
        cout << "Please enter the number of purchased items: ";
        cin >> number;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid quantity value!" << endl << endl;
        }
        else{
            if(number <= (product->qtyNeeded()-product->qtyAvailable())){
                *product += number;

            }
            else{
                int enough = product->qtyNeeded()-product->qtyAvailable();
                int extra = number+product->qtyAvailable()-product->qtyNeeded();
                *product += enough;
                cout.clear();
                cout << "Too many items; only " << enough << " is needed. Please return the extra " << extra << " items." << endl;
            }
            saveProductRecords();
            cout << endl << "Updated!" << endl << endl;
        }
    }
    //Function to add a new product to the end of the iProduct array
    void AmaApp::addProduct(char tag){
        iProduct* newProduct = createInstance(tag);
        if(newProduct != nullptr){
            cin >> *newProduct;
            if (cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << *newProduct << endl << endl;
            }
            else{
                m_products[m_noOfProducts] = newProduct;
                m_noOfProducts++;
                saveProductRecords();
                cout << endl << "Success!" << endl << endl;
            }
        }
    }
    //Function used to interact with user
    int AmaApp::run(){
        int select;
        char* SKU;
        while(select != 0){
        select = menu();
            switch(select){
                case 1:{
                    listProducts();
                }
                    break;

                case 2:{
                    cout << "Please enter the product SKU: ";
                    SKU = new char[max_length_sku];
                    cin >> SKU;
                    cout << endl;
                    iProduct* temp = find(SKU);
                    if (temp != nullptr){
                        temp->write(cout, write_human);
                        cout << endl;
                    }
                    else{
                        cout << "No such product!" << endl;
                    }
                    delete SKU;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pause();
                }
                    break;

                case 3:{
                    addProduct('N');
                    loadProductRecords();
                }
                    break;

                case 4:{
                    addProduct('P');
                    loadProductRecords();
                }
                    break;

                case 5:{
                    cout << "Please enter the product SKU: ";
                    SKU = new char[max_length_sku];
                    cin >> SKU;
                    cout << endl;
                    iProduct* temp2 = find(SKU);
                    if(temp2 != nullptr){
                        for(int i = 0; i < m_noOfProducts; i++){
                            if(*m_products[i] == SKU){
                                addQty(m_products[i]);
                                break;
                            }
                        }
                    }
                    else{
                        cout << "No such product!" << endl << endl;
                    }
                }
                    delete SKU;
                    break;

                case 0:{
                    cout << "Goodbye!" << endl;
                }
                    break;

                default:{
                    cout << "~~~Invalid selection, try again!~~~" << endl;
                    pause();
                }

            }
        }

        return 0;
    }
}
