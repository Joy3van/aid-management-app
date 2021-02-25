/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 2
Section: OOP244SCC
Date: Mar.17th.2019
*/
#ifndef ERRORSTATE_H_INCLUDED
#define ERRORSTATE_H_INCLUDED

#include <iostream>

namespace ama {
    class ErrorState {
        char* errMsg;
        void setMsg(const char*);
    public:
        explicit ErrorState(const char* errorMessage = nullptr);
        ErrorState(const ErrorState& other) = delete;
        ErrorState& operator=(const ErrorState& other) = delete;
        ~ErrorState();
        operator bool() const;
        ErrorState& operator=(const char* pText);
        void message(const char* pText);
        const char* message() const;
    };
    std::ostream& operator<<(std::ostream& os, const ErrorState&);
}



#endif // ERRORSTATE_H_INCLUDED
