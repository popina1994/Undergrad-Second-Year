#include "Datum.h"
#include <iostream>

using namespace std;

int Datum::days[MONTHS_NUM] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool Datum::IsRegular(int year, int month, int day) {
    if (year > 0 && month > 0 && month <= 12 && day > 0 && (day <= ( days[month - 1] + ( (month == 2) && ( (year % 4) == 0) ) ) ) )
            return true;
    return false;
}

Datum::Datum(int _year, int _month, int _day) : year(_year), month(_month), day(_day) {}

int Datum::GetDay() const { return day; }

int Datum::GetMonth() const { return month; }

int Datum::GetYear() const { return year; }

bool Datum::Read() {
    int _day, _month, _year;

    cout << "Unesite datum" << endl;
    cin >> _day >> _month >> _year;
    cout << endl;
    if (IsRegular(_year, _month, _day)) {
        year = _year;
        month = _month;
        day = _day;
        return true; // everything went good
    }
    return false; // something went wrong
}

void Datum::Write() const {
    cout << day << "-" << month << "-" << year << " ";
}

int Compare(const Datum& d1, const Datum& d2) {
    if (d1.year != d2.year)
        return d1.year - d2.year;
    if (d1.month != d2.month)
        return d1.month - d2.month;
    return d1.day - d2.day;
}
