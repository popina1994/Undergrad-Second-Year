#include <iostream>
#include <cstring>
#include "Dokument.h"

using namespace std;

int Dokument::Primarni = 0;

void Dokument::Premesti(Dokument& d) {
	kap = d.kap; 
	n = d.n; d.n = 0;
	x = d.x; d.x = nullptr;
	IDDok = Primarni++;
}

void Dokument::Kopiraj(const Dokument& d) {
	kap = d.kap;
	n = d.n;
	x = new char*[kap];
	for (int i = 0; i < n; i++) {
		x[i] = new char[strlen(d.x[i]) + 1];
		strcpy(x[i], d.x[i]);
	}
	IDDok = Primarni++;
}

void Dokument::Obrisi() {
	for (int i = 0; i < n; i++)
		delete[] x[i];
	delete[] x;
	n = 0;
	kap = 0;

}

Dokument::Dokument(int _kap) : IDDok(Primarni++), kap (_kap), x(new char*[kap]) {
}

Dokument::Dokument(const Dokument& d) {
	Kopiraj(d);
}

Dokument::Dokument(Dokument&& d) {
	Premesti(d);
}

Dokument::~Dokument() {
	Obrisi();
}


Dokument& Dokument::operator=(const Dokument& d) {
	if (this != &d) {
		Obrisi();
		Kopiraj(d);
	}
	return *this;
}

Dokument& Dokument::operator=(Dokument&& d) {
	if (this != &d){
		Obrisi();
		Premesti(d);
	}
	return *this;
}


void Dokument::Pisi(ostream& out) const {
	out << IDDok << endl;
	for (int i = 0; i < n; i++)
		out << x[i] << endl << endl;
}

ostream& operator<<(ostream& out, const Dokument& d) {
	d.Pisi(out);
	return out;
}

int Dokument::BrojPasusa() const {
	return n;
}

int Dokument::Duzina() const {
	int cnt = 0;
	for (int i = 0; i < n; i++)
		cnt += strlen(x[i]);
	return cnt;
}

Dokument& Dokument::operator+=(const char* ubaci) {
	if (n == kap) {
		Dokument d(*this);
		Obrisi();

		x = new char*[n + 1];
		for (int i = 0; i < n; i++) {
			x[i] = new char[strlen(d.x[i]) + 1];
			strcpy(x[i], d.x[i]);
		}
		n = d.n; // stara vrednost
		kap = d.kap + 10; // kapacitet povecan
	}
	x[n] = new char[strlen(ubaci) + 1];
	strcpy(x[n++], ubaci);
	return *this;
}

const char* Dokument::operator[](int idx) const {
	return x[idx];
}

