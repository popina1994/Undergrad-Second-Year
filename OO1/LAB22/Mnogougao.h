#ifndef _Mnogougao_h_
#define _Mnogougao_h_

#include "Izlomljena.h"
#include <iostream>

using namespace std;

class Mnogougao : public Izlomljena {
public:
    double Duzina() const;
    friend ostream& operator<<(ostream&, const Izlomljena&);
};

#endif // _Mnogougao_h_
