#include <iostream>
#include "Zbirka.h"

using namespace std;

void Zbirka::Kopiraj(const Zbirka& z) {
    kap = z.kap;
    zauzet = z.zauzet;
    x = new int [z.kap];
    for (int idx = 0; idx < z.zauzet; idx ++)
        x[idx] = z.x[idx];
}

void Zbirka::Premesti(Zbirka& z) {
    kap = z.kap;
    zauzet = z.zauzet;
    x = z.x;
    z.x = nullptr;
}

void Zbirka::Obrisi() {
    delete [] x;
    zauzet = 0;
    kap = 0;
}

Zbirka::Zbirka(const Zbirka& z) {
    Kopiraj(z);
}

Zbirka::Zbirka(Zbirka&& z) {
    Premesti(z);
}

Zbirka::~Zbirka() {
    Obrisi();
}

Zbirka& Zbirka::operator=(Zbirka& z) {
    if (this != &z) {
        Kopiraj(z);
    }
    return *this;
}

Zbirka& Zbirka::operator=(Zbirka&& z) {
    Premesti(z);
    return *this;
}

Zbirka& Zbirka::operator+=(int d) {
    if (zauzet == kap) {
        kap += 4;
        int* y = x;
        x = new int[kap];
        for (int idx = 0; idx < zauzet; idx ++)
            x[idx] = y[idx];
        delete [] y;
    }
    x[zauzet++] = d;
    return *this;
}

int Zbirka::Zauzetost() const {
    return zauzet;
}

int Zbirka::operator[](int idx) const {
    return x[idx];
}

ostream& operator<<(ostream& out, const Zbirka& z) {
    out << "(";
    for (int idx = 0; idx < z.zauzet; idx ++) {
        out << z[idx];
        if (idx != z.zauzet - 1)
            out << " ,";
    }
    out << ")";
    return out;
}
