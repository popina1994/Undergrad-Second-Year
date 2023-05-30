#ifndef _Apstraktan_h_
#define _Apstraktan_h_

#include <iostream>

using namespace std;

class Predmet {
	virtual double Velicina() const = 0;
	virtual void Pisi(ostream& out) const = 0;
};

#endif