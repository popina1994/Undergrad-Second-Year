#include "Karta.h"
#include "Tacka.h"
#include "Simbol.h"
#include <iostream>

using namespace std;

const char* GreskaPrazna::what() const { return "Prazna"; }

Karta::Element::Element(const Simbol& s) {
	info = s.PolyCopy();
	next = nullptr;
}

Karta::Element::Element(const Element& e) {
	info = e.info->PolyCopy();
	next = nullptr;
}

Karta::Element::~Element() {
	next = nullptr;
	delete info;
}

void Karta::Copy(const Karta& k) {
	for (Element* it = k.begin; it != nullptr; it = it->next) {
		Element* tmpElem = new Element(*it);
		if (begin == nullptr)
			begin = tmpElem;
		else
			end->next = tmpElem;
		end = tmpElem;
	}
}

void Karta::Move(Karta& k) {
	begin = k.begin; k.begin = nullptr;
	end = k.end; k.end = nullptr;
}

void Karta::Delete() {
	Element* it = begin;
	while (it != nullptr) {
		Element* tmpPt = it;
		it = it->next;
		delete tmpPt;
	}
}

Karta::Karta() : begin(nullptr), end(nullptr) {}

Karta::Karta(const Karta& k) {
	Copy(k);
}

Karta::Karta(Karta&& k) {
	Move(k);
}

Karta::~Karta() {
	Delete();
}

Karta& Karta::operator=(const Karta& k) {
	if (this != &k) {
		Delete();
		Copy(k);
	}
	return *this;
}

Karta& Karta::operator=(Karta&& k) {
	if (this != &k) {
		Delete();
		Move(k);
	}
	return *this;
}

Karta& Karta::operator+=(const Simbol& s){
	Element* tmpPt = new Element(s);

	if (begin == nullptr) 
		begin = tmpPt;
	else 
		end->next = tmpPt;
	end = tmpPt;
	
	return *this;
}

Simbol* Karta::Najblizi(const Tacka<double>& t) {
	double minDist = DBL_MAX;
	Simbol* minSimb = nullptr;

	for (auto it = begin; it != nullptr; it = it->next) {
		if (it->info->GetCentar().Distance(t) <= minDist) {
			minSimb = it->info;
			minDist = it->info->GetCentar().Distance(t);
		}
	}

	if (minSimb == nullptr)
		throw GreskaPrazna();
	return minSimb;
}

ostream& operator<<(ostream& out, const Karta& k) {
	for (auto it = k.begin; it != nullptr; it = it->next) {
		out << *it->info << endl;
	}
	return out;
}