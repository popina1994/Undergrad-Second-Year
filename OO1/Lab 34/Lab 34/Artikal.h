#include "Roba.h"

class Artikal : public Roba{
	char oznaka;
	double vrednost;
protected:
	void Write(ostream& out) const override;
public:
	Artikal(char _oznaka = '?', double _vrednost = 0);
	Artikal* PolyCopy() const override;
	double Vrednost() const override;
	char GetOznaka() const;

};