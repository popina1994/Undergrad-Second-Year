#include "Vektor.h"
#include <iostream>
#include <cmath>

using namespace std;

void Vektor::Kopiraj(const Vektor& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

Vektor::Vektor(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

Vektor::Vektor(const Vektor& v) {
    Kopiraj(v);
}

Vektor& Vektor::operator=(const Vektor& v) {
    if (this != &v)
        Kopiraj(v);
    return *this;
}

double Vektor::operator~() const {
    return sqrt(x * x + y * y + z * z);
}

Vektor operator-(const Vektor& v1, const Vektor& v2) {
    return Vektor(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vektor operator+(const Vektor& v1, const Vektor& v2) {
    return Vektor(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

ostream& operator<<(ostream& out, const Vektor& v) {
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
}


