#include <cstring>
#include <iostream>
#include "Stavka.h"


using namespace std;


Stavka::Stavka(const char* _naziv, double _cena, double _kol) {
	cena = _cena;
	kol = _kol;
	naziv = new char[strlen(_naziv) + 1];
	strcpy(naziv, _naziv);
}

double Stavka::Velicina() const {
	return cena * kol;
}

void Stavka::Pisi(ostream& out) const {
	out << naziv << " " << cena << " " << kol;
}

Stavka::~Stavka() {
	delete[] naziv;
}