#ifndef _Vektor_h_
#define _Vektor_h_

#include <iostream>

using namespace std;

class Vektor {
    double x, y, z;

    void Kopiraj(const Vektor&);
public:
    Vektor(double _x = 0, double _y = 0, double _z = 0);
    Vektor(const Vektor&);

    Vektor& operator=(const Vektor&);

    double operator~() const;

    friend Vektor operator+(const Vektor&, const Vektor&);
    friend Vektor operator-(const Vektor&, const Vektor&);
    friend ostream& operator<<(ostream& out, const Vektor&);
};

#endif // _Vektor_h_
