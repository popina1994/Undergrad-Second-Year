#ifndef _KARTA_H_
#define _KARTA_H_

#include "Simbol.h"
#include "Mesto.h"
#include <iostream>
#include <exception>

using namespace std;

class GreskaPrazna : public exception{
	const char* what() const;
};



class Karta {
	struct Element {
		Simbol* info;
		Element* next = nullptr;
		Element(const Simbol&);
		Element(const Element&);
		~Element();
	};

	Element* begin,* end;
	
	void Copy(const Karta&);
	void Move(Karta&);
	void Delete();
public:
	Karta();
	Karta(const Karta&);
	Karta(Karta&&);
	~Karta();

	Karta& operator=(const Karta&);
	Karta& operator=(Karta&&);

	Karta& operator+=(const Simbol&);
	Simbol* Najblizi(const Tacka<double>&);
	friend ostream& operator<<(ostream&, const Karta&);
};

#endif