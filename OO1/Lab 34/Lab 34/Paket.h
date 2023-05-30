#ifndef _PAKET_H_
#define _PAKET_H_

#include "Roba.h"
#include "Zbirka.h"

class Paket : public Roba {
	Zbirka <Roba*> z;
	void Copy(const Paket&);
	void Delete();
protected:
	void Write(ostream&) const;
public:
	Paket() = default;
	Paket(const Paket&);
	~Paket();

	Paket& operator=(const Paket& z);

	Paket* PolyCopy() const override;
	double Vrednost() const override;


	Paket& operator+=(const Roba&);
};

#endif