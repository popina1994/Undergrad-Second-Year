#include "Datoteka.h"
#include "Imenik.h"
#include <iostream>

using namespace std;

Datoteka::Datoteka(const string& _ime, int _vel) : ime(_ime), vel(_vel) {}

void Datoteka::SetName(const string& _name) {
	ime = _name;
}

string& Datoteka::GetName() {
	return ime;
}

const string& Datoteka::GetName() const{
	return ime;
}

void Datoteka::SetSize(int size) {
	vel = size;
}

int Datoteka::GetSize() const {
	return vel;
}

int Datoteka::Size() const {
	return vel;
}

void Datoteka::SetParent(Imenik* _parent) {
	parent = _parent;
}


Datoteka* Datoteka::PolyCopy() const {
	return new Datoteka(*this);
}

void Datoteka::Pisi(ostream& out) const {
	if (parent != nullptr)
		out << parent->ime;
	out << "/" << ime << "(" << Size() << ")";
}

ostream& operator<< (ostream& out, const Datoteka& d) {
	d.Pisi(out);
	return out;
}