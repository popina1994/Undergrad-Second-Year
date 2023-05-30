#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <iostream>

using namespace std;

class Element {
public:
	virtual double Velicina() const = 0;
	virtual Element* PolyCopy() const = 0;
	virtual void Pisi(ostream& out) const = 0;
	friend ostream& operator<<(ostream&, const Element&);

	virtual ~Element() = 0;
};

#endif