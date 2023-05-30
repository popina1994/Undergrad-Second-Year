#ifndef _SIMBOL_H_
#define _SIMBOL_H_

#include <iostream>
#include "Tacka.h"

using namespace std;

class Simbol {
	static int globalIDX;
	int idx;
protected:
	virtual void Pisi(ostream& out) const;
public:
	Simbol();
	Simbol(const Simbol&);
	Simbol& operator=(const Simbol&) = default;
	virtual ~Simbol() = 0;
		
	virtual Simbol* PolyCopy() const = 0;

	virtual const Tacka<double>& GetCentar() const = 0;
	
	friend ostream& operator<<(ostream& out, const Simbol&);

	
};

#endif