#ifndef _MESTO_H_
#define _MESTO_H_

#include "Simbol.h"
#include "Tacka.h"
#include <iostream>

using namespace std;

class Mesto : public Simbol {
	string ime;
	Tacka <double> centar;
public:
	Mesto(string ime, double x, double y);
	Mesto* PolyCopy() const;
	const Tacka<double>& GetCentar() const;

	void Pisi(ostream& out) const;
	
};

#endif