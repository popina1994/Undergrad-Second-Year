#include "Element.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, const Element& e) {
	e.Pisi(out);
	return out;
}

Element::~Element() {}