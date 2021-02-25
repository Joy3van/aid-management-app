/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 2
Section: OOP244SCC
Date: Mar.17th.2019
*/
#include <iostream>
#include <cstring>
#include "ErrorState.h"

using namespace std;

namespace ama {
    //--------------------------------------Private--------------------------------------------
    void ErrorState::setMsg(const char* errorMessage) {
        if (errorMessage == nullptr || errorMessage[0] == '\0')
            errMsg = nullptr;
        else {
            errMsg = new char[strlen(errorMessage) + 1];
            strncpy(errMsg, errorMessage, strlen(errorMessage) + 1);
        }
    }
    //--------------------------------------Public---------------------------------------------
    // Explicit constructor
    /*explicit*/ ErrorState::ErrorState(const char* errorMessage /*= nullptr*/) {
        setMsg(errorMessage);
    }
    // Destructor
    ErrorState::~ErrorState() {
        delete [] errMsg;
    }
    // bool operator
    ErrorState::operator bool() const {
        return errMsg != nullptr;
    }
    // = operator overloading
    ErrorState& ErrorState::operator=(const char* pText) {
        delete [] errMsg;// In case of memory leak
        setMsg(pText);
        return *this;
    }
    // message function
    void ErrorState::message(const char* pText) {
        delete [] errMsg; // Avoid memory leak
        setMsg(pText);
    }
    // overload message function
    const char* ErrorState::message() const {
        return errMsg;
    }
    // << operator
    std::ostream& operator<<(ostream& os, const ErrorState& err) {
        if (err.message() != nullptr)
            os << err.message();
        return os;
    }
}
