#include "Simbol.h"

int Simbol::globalIDX = 0;

Simbol::Simbol() {
	idx = globalIDX++;
}

Simbol::Simbol(const Simbol& s) {
	idx = globalIDX++;
}

Simbol::~Simbol() {}

void Simbol::Pisi(ostream& out) const {
	out << idx;
}

ostream& operator<<(ostream& out, const Simbol& s) {
	s.Pisi(out);
	return out;
}



