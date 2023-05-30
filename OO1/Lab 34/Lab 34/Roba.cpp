#include "Roba.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, const Roba& r) {
	r.Write(out);
	return out;
}

Roba::~Roba() {}