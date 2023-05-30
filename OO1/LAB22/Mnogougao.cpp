#include <iostream>
#include "Mnogougao.h"

using namespace std;

double Mnogougao::Duzina() const {
    double duz = Izlomljena::Duzina();
    if (n > 0)
        duz += ~(x[n - 1] - x[0]);
    return duz;
}

ostream& out(ostream& out, const Mnogougao& m) {
    cout << "Ovde" << endl;
    out << "M";
    out << m;
    return out;
}

