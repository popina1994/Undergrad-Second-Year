#ifndef _Zbirka_h_
#define _Zbirka_h_

#include "Dokument.h"
#include "Autorizovani.h"
#include <iostream>

using namespace std;

class Zbirka {
	int kap;
	int n;
	Dokument** x;
public:
	Zbirka(int _kap = 5) : kap(_kap), x(new Dokument*[kap]), n(0){}
	Zbirka(const Zbirka&) = delete;
	Zbirka(Zbirka&&) = delete;
	~Zbirka();
	
	Zbirka& operator=(const Zbirka&) = delete;
	Zbirka& operator=(Zbirka&&) = delete;

	Zbirka& operator+=(const Dokument& d);

	friend ostream& operator<<(ostream& out, const Zbirka& z);
};
#endif