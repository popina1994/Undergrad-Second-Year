#ifndef _Stavka_h_
#define _Stavka_h_

#include <iostream>
#include <cstring>
#include "Apstraktan.h"

using namespace std;

class Stavka : public Predmet {
	char* naziv;
	double cena, kol;
	double Velicina() const;
	void Pisi(ostream& out) const;

public:
	Stavka(const char* _naziv, double _cena, double _kol);
	~Stavka();
};

#endif