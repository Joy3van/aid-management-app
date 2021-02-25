/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 1
Section: OOP244SCC
Date: Mar.13th.2019
*/

#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <iostream>

namespace ama {
    // Constants
    const int min_year = 2019;
    const int max_year = 2028;
    const int no_error = 0;
    const int error_year = 1;
    const int error_mon = 2;
    const int error_day = 3;
    const int error_invalid_operation = 4;
    const int error_input = 5;
    // Class definition
    class Date {
        int year;
        int month;
        int day;
        int dstatus;
        void status(int);
        int mdays(int, int) const;
        bool validYear(int) const;
        bool validMon(int) const;
        bool valid(int, int, int) const;
        bool isEmpty() const;
        bool isError() const;
    public:
        Date();
        Date(int, int, int );
        int status() const;
        void clearError();
        bool isGood() const;
        Date& operator+=(int days);
        Date& operator++(); // Pre-fix
        Date operator++(int); // Post-fix
        Date operator+(int days);
        bool operator==(const Date& rhs);
        bool operator!=(const Date& rhs);
        bool operator<(const Date& rhs);
        bool operator>(const Date& rhs);
        bool operator<=(const Date& rhs);
        bool operator>=(const Date& rhs);
        std::istream& read(std::istream& is) ;
        std::ostream& write(std::ostream& os) const;
    };
    std::ostream& operator<<(std::ostream&, const Date&) ;
    std::istream& operator>>(std::istream&, Date&) ;
}


#endif // DATE_H_INCLUDED
