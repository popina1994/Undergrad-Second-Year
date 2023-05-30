#ifndef _ROBA_H_
#define _ROBA_H_

#include <iostream>

using namespace std;

class Roba {
	
protected:
	virtual void Write(ostream& out) const = 0;
public:
	virtual double Vrednost() const = 0;
	virtual Roba* PolyCopy() const = 0;
	
	friend ostream& operator<<(ostream&, const Roba&);
	virtual ~Roba();
};

#endif