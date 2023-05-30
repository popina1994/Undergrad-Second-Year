#include "Zbirka.h"
#include <iostream>

using namespace std;

Zbirka::~Zbirka() {
	for (int i = 0; i < n; i++)
		delete x[i];
	delete [] x;
}

Zbirka& Zbirka::operator+=(const Dokument& d) {
	if (n == kap)
		exit(2);
	x[n++] = new Dokument(d);
	return *this;
}

ostream& operator<<(ostream& out, const Zbirka& z) {
	int duz = 0;
	for (int i = 0; i < z.n; i++)
		duz += z.x[i]->Duzina();
	out << duz << endl;
	for (int i = 0; i < z.n; i++) {
		out << *z.x[i] << endl;
		if (i != z.n - 1)
			out << "*" << endl;
	}
	return out;
}