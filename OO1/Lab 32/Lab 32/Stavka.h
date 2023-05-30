#ifndef _STAVKA_H_
#define _STAVKA_H_

#include <string>
#include "Element.h"

using namespace std;

class Stavka : public Element {
	string naziv;
	double cena;
	int kol;
public:
	Stavka(const string& _naziv, double _cena, int _kol);
	double Velicina() const override;
	Stavka* PolyCopy() const override;
	void Pisi(ostream&) const override;
};

#endif