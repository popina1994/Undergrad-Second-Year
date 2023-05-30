#include "Racun.h"
#include "Stavka.h"
#include <iostream>
#include <string>

using namespace std;

Racun::Racun(const string& _ime, int _datum, int kap) : ime(_ime), datum(_datum), z(kap) {}

double Racun::Vrednost() const {
	double curVre = 0;
	
	for (int i = 0; i < z.Size(); i++)
		curVre += z[i].Velicina();
	
	return curVre;
}

Racun& Racun::operator+=(const Stavka& s) {
	z += s;
	return *this;
}

ostream& operator<<(ostream& out, const Racun& r) {
	out << r.ime << " " <<  r.datum << endl;
	out << r.z;
	out << r.Vrednost() << endl;
	
	return out;
}