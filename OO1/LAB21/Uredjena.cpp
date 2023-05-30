#include "Zbirka.h"
#include "Uredjena.h"

Uredjena& Uredjena::operator+=(int d) {
    if (zauzet == kap) {
        kap += 4;
        int* y = x;
        x = new int[kap];
        for (int idx = 0; idx < zauzet; idx ++)
            x[idx] = y[idx];
        delete [] y;
    }

    int idx;
    for (idx = zauzet - 1; idx >= 0; idx--) {
        if (x[idx] < d) {
            x[idx + 1] = d;
            break;
        }
        x[idx + 1] = x[idx];
    }
    zauzet++;
    if (idx == -1)
        x[0] = d;

    return *this;
}
