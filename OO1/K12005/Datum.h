#ifndef _Datum_h_
#define _Datum_h_

constexpr int MONTHS_NUM = 12;

class Datum {
    int year, month, day;

    static int days[MONTHS_NUM];

    static bool IsRegular(int year, int month, int day); // checks if date is regular
public:
    Datum(int _year = 2005, int _month = 11, int _day = 7);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    bool Read(); // reads date from standard input
    void Write() const; // writes date

    friend int Compare(const Datum& d1, const Datum& d2); // checks is first date before second

};

#endif // _Datum_h_
