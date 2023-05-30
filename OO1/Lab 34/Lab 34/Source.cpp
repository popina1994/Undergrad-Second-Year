#include "Greska.h"
#include "Zbirka.h"
#include "Roba.h"
#include "Artikal.h"
#include "Paket.h"
#include <iostream>

using namespace std;

Roba* procitajRobu() {
	Roba* r = 0;
	cout << "1. Artikal" << endl
		<< "2. Paket" << endl
		<< "3. Kraj" << endl;
	int izbor; cin >> izbor;
	char oznaka;
	double vrednost;
	Roba* t;
	switch (izbor) {
	case 1: cout << "Unesite oznaku : "; cin >> oznaka;
		cout << "Unesite vrednost: "; cin >> vrednost;
		r = new Artikal(oznaka, vrednost);
		break;
	case 2:
		r = new Paket();
		cout << "Sastavljanje paketa: " << endl;
		while (t = procitajRobu())
			*dynamic_cast<Paket *>(r) += *t;
		break;
	case 3: return 0;
	}
	return r;
}
int main() {
	Roba* roba;
	try {
		while (roba = procitajRobu()) {
			cout << *roba << endl;
			delete roba;
		}
	}
	catch (const OutOfRange& g) { cout << g.what() << endl; }
}