#include <iostream>
#include <typeinfo>

#include "Vektor.h"
#include "Izlomljena.h"
#include "Mnogougao.h"

using namespace std;

int main() {
    Izlomljena* i;
    i = new Mnogougao;
    *i += Vektor(0, 0, 0);
    *i += Vektor(1, 1, 1);
    *i += Vektor(2, 2, 2);
    if (typeid(*i) == typeid(Mnogougao)) {
        cout << *(static_cast<Mnogougao*>(i));
    }

    return 0;
}
