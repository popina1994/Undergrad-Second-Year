#include "Zbirka.h"
#include "Element.h"
#include "Stavka.h"

class Racun {
	string ime;
	int datum;
	Zbirka <Stavka> z;
public:
	Racun(const string& s, int datum, int kap);
	double Vrednost() const;
	Racun& operator+=(const Stavka& s);

	friend ostream& operator<<(ostream&, const Racun&);
};