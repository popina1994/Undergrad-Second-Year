#include "Paket.h"
#include "Roba.h"

void Paket::Copy(const Paket& p) {
	z = p.z;
	for (int i = 0; i < p.z.Size(); i++)
		z[i] = p.z[i]->PolyCopy();
}

void Paket::Delete() {
	for (int i = 0; i < z.Size(); i++)
		delete z[i];
}

Paket::Paket(const Paket& p) {
	Copy(p);
}

Paket& Paket::operator=(const Paket& p) {
	if (this != &p) {
		Delete();
		Copy(p);
	}
	return *this;
}

Paket::~Paket() {
	Delete();
}

Paket* Paket::PolyCopy() const {
	return new Paket(*this);
}

double Paket::Vrednost() const {
	double sum = 0;
	for (int i = 0; i < z.Size(); i++)
		sum += z[i]->Vrednost();
	return sum;
}

void Paket::Write(ostream& out) const{
	for (int i = 0; i < z.Size(); i++)
		out << "[" << *z[i] << "]";
}

Paket& Paket::operator+=(const Roba& r) {
	z += r.PolyCopy();
	return *this;
}