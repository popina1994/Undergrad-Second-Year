#include <iostream>
#include "Izlomljena.h"

using namespace std;

Izlomljena::Izlomljena(int _kap) : kap(_kap), x(new Vektor[_kap]) {}

Izlomljena::~Izlomljena() {
    delete [] x; // nothing to worry about
}

bool Izlomljena::operator+=(const Vektor& v) {
    if (n == kap)
        return false;
    x[n++] = v;
    return true;
}

int Izlomljena::BrojTemena() const {
    return n;
}

double Izlomljena::Duzina() const {
    double duz = 0;
    for (int idx = 0; idx < n - 1; idx ++)
        duz += ~(x[idx] - x[idx + 1]);
    return duz;
}

/*ostream& operator<<(ostream& out, const Izlomljena& i) {
    out << "(";
    for (int idx = 0; idx < i.n; idx ++) {
        out << i.x[idx];
        if (idx != i.n - 1)
            out << "|";
    }

    out << ")";
    return out;
}*/


