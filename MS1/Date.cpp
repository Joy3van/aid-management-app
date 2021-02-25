/*
Name: Yifan Zhao
Student number: 138736186
Email: yzhao227@myseneca.ca
Milestone: 1
Section: OOP244SCC
Date: Mar.13th.2019
*/

#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include "Date.h"

using namespace std;

namespace ama {
    //---------------------------------------Private---------------------------------------------------
    // status function
    void Date::status(int newStatus) {
        dstatus = newStatus;
    }
    // mdays function
    int Date::mdays(int year, int mon) const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = mon >= 1 && mon <= 12 ? mon : 13;
        month--;
        return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    // validYear function
    bool Date::validYear(int yr) const {
        if(yr >= min_year && yr <= max_year)
            return true;
        return false;
    }
    // validMon function
    bool Date::validMon(int mon) const {
        if(mon >= 1 && mon <= 12)
            return true;
        return false;
    }
    // valid function
    bool Date::valid(int yr, int mon, int dy) const {
        if(validYear(yr) && validMon(mon)) {
               if(dy >= 1 && dy <= mdays(yr, mon)) {
                   return true;
               }
        }
        return false;
    }
    // isEmpty function
    bool Date::isEmpty() const {
        if(dstatus == no_error && year == 0 && month == 0 && day == 0)
            return true;
        return false;
    }
    // isError function
    bool Date::isError() const {
        if(dstatus == error_year || dstatus == error_mon || dstatus == error_day ||
           dstatus == error_invalid_operation || dstatus == error_input)
            return true;
        return false;
    }
    //---------------------------------------Public------------------------------------------------------
    // Default constructor
    Date::Date() {
        status(no_error);
        year = 0;
        month = 0;
        day = 0;
    }
    // Custom constructor
    Date::Date(int yr, int mon, int dy) {
        if (valid(yr, mon, dy)) {
            year = yr;
            month = mon;
            day = dy;
            status(no_error);
        }
        else {
            int err = no_error;
            if(!validYear(yr))
                err = error_year;
            else {
                if(!validMon(mon))
                    err = error_mon;
                else {
                    if(dy < 1 || dy > mdays(yr, mon)) {
                        err = error_day;
                    }
                }
            }
            year = 0;
            month = 0;
            day = 0;
            status(err);
        }
    }
    // status query(overloaded)
    int Date::status() {
        return dstatus;
    }
    // cleanError modifier
    void Date::clearError() {
        status(no_error);
    }
    // isGood query
    bool Date::isGood() {
        if(status() == no_error && valid(year, month, day))
            return true;
        return false;
    }
    // += operator
    Date& Date::operator+=(int days) {
        if((*this).isEmpty() || (*this).isError())
            (*this).status(error_invalid_operation);
        else {
            int temp = (*this).day + days;
            if(temp >= 1 && temp <= mdays((*this).year, (*this).month))
                (*this).day = temp;
            else
                (*this).status(error_invalid_operation);
        }
        return *this;
    }
    // ++prefix operator
    Date& Date::operator++() {
        *this += 1;
        return *this;
    }
    //++postfix operator
    Date Date::operator++(int) {
        Date postInc = *this;
        ++(*this);
        return postInc;
    }
    // + operator
    Date Date::operator+(int days) {
        Date plusDate = *this;
        if(plusDate.isEmpty() || plusDate.isError())
            plusDate.status(error_invalid_operation);
        else {
            int temp = plusDate.day + days;
            if(temp >= 1 && temp <= mdays(plusDate.year, plusDate.month))
                plusDate.day = temp;
            else
                plusDate.status(error_invalid_operation);
        }
        return plusDate;
    }
    // == operator
    bool Date::operator==(const Date& rhs) {
        if(year == rhs.year && month == rhs.month && day == rhs.day)
            return true;
        return false;
    }
    // != operator
    bool Date::operator!=(const Date& rhs) {
        if(year != rhs.year || month != rhs.month || day != rhs.day)
            return true;
        return false;
    }
    // < operator
    bool Date::operator<(const Date& rhs) {
        if (year != rhs.year) {
            if (year < rhs.year)
                return true;
            else // year > rhs.year
                return false;
        }
        else { // year == rhs.year
            if (month != rhs.month) { // year == rhs.year && month != rhs.month
                if (month < rhs.month)
                    return true;
                else // month > rhs.month
                    return false;
            }
            else { //year == rhs.year && month == rhs.month
                if(day < rhs.day)
                    return true;
                else
                    return false;
            }
        }
    }
    // > operator
    bool Date::operator>(const Date& rhs) {
        if (*this != rhs)
            return !(*this < rhs);
        return false;
    }
    // <= operator
    bool Date::operator<=(const Date& rhs) {
        return (*this == rhs || *this < rhs);
    }
    // >= operator
    bool Date::operator>=(const Date& rhs) {
        return (*this == rhs || *this > rhs);
    }
    // read function
    istream& Date::read(istream& is) {
        int year;
        int month;
        int day;
        char character;
        is >> year >> character >> month >> character >> day;
        if(!is.fail()) {
            *this = Date(year, month, day);
        }
        /*string input;
        regex formatted("[0-9]{4}.[0-9]{1,2}.[0-9]{1,2}");
        is >> input;
        if (!is.fail()) {
            if(regex_match(input, formatted)) {
                // Convert the corresponding part to integer and assign it
                year = stoi(input.substr(0, 4));
                month = stoi(input.substr(5, 2));
                day = stoi(input.substr(8, 2));
            }
            Date temp(year, month, day);
            if(!regex_match(input.substr(5, 2), regex("[0-9]{2}")))
                temp.status(error_mon);
            *this = temp;
        }*/
        else {
            *this = Date();
            status(error_input);
        }
        return is;
    }
    // write function
    ostream& Date::write(ostream& os) const{
        os << setw(4) << setfill('0') << year;
        os << right;
        os << "/" << setw(2)  << month << "/" << setw(2)  << day;
        os << setfill(' ');
        return os;
    }
    // << operator
    std::ostream& operator<<(ostream& os, const Date& date) {
        return date.write(os);
    }
    // >> operator
    std::istream& operator>>(istream& is,Date& date) {
        return date.read(is);
    }
}
