#ifndef _Izlomljena_h_
#define _Izlomljena_h_

#include "Vektor.h"


class Izlomljena {
protected:
    int kap;
    int n = 0;
    Vektor* x;


public:
    Izlomljena(int _kap = 3);
    Izlomljena(const Izlomljena&) = delete;
    Izlomljena(const Izlomljena&&) = delete;
    ~Izlomljena();

    Izlomljena& operator=(const Izlomljena&) = delete;
    Izlomljena& operator=(Izlomljena&&) = delete;

    bool operator+=(const Vektor&);

    int BrojTemena() const;
    virtual double Duzina() const;

    //friend ostream& operator<<(ostream& out, const Izlomljena&);
};

#endif // _Izlomljena_h_
