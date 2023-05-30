#include "Artikal.h"
#include "Roba.h"

using namespace std;

Artikal::Artikal(char _oznaka, double _vrednost) : oznaka(_oznaka), vrednost(_vrednost){}

Artikal* Artikal::PolyCopy() const {
	return new Artikal(*this);
}

char Artikal::GetOznaka() const {
	return oznaka;
}

double Artikal::Vrednost() const {
	return vrednost;
}

void Artikal::Write(ostream&out) const {
	out << oznaka;
}