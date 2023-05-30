#include "Stavka.h"

Stavka::Stavka(const string& _naziv, double _cena, int _kol) : naziv(_naziv), cena(_cena), kol(_kol) {}

double Stavka::Velicina() const {
	return cena * kol;
}

Stavka* Stavka::PolyCopy() const {
	return new Stavka(*this);
}

void Stavka::Pisi(ostream& out) const {
	out << naziv << " " << cena << " " << kol << " " << Velicina();
}