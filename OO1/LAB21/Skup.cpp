#include "Zbirka.h"
#include "Skup.h"

Skup& Skup::operator+=(int d) {
    for (int idx = 0; idx < zauzet; idx++)
        if (x[idx] == d)
            return *this;;

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
