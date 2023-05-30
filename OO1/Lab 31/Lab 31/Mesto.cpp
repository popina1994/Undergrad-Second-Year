#include "Mesto.h"
#include "Tacka.h"

#include <iostream>
#include <string>

using namespace std;

Mesto::Mesto(string _ime, double x, double y) : ime(_ime), centar(x, y) {}

Mesto* Mesto::PolyCopy() const {
	return new Mesto(*this);
}
const Tacka<double>& Mesto::GetCentar() const {
	return centar;
}

void Mesto::Pisi(ostream& out) const {
	Simbol::Pisi(out);
	out << ":" << ime << "[" << centar << "]";
}