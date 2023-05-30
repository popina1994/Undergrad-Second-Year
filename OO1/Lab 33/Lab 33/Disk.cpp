#include "Disk.h"

Disk::Disk() : koren(new Imenik("")){}

void Disk::Copy(const Disk& d) {
	koren = d.koren->PolyCopy();
}

void Disk::Move(Disk& d) {
	koren = d.koren; d.koren = nullptr;
}

void Disk::Delete() {
	delete koren;
}

Disk::Disk(const Disk& d) {
	Copy(d);
}

Disk::Disk(Disk&& d) {
	Move(d);
}

Disk::~Disk() {
	Delete();
}

Disk& Disk::operator=(const Disk& d) {
	if (this != &d) {
		Delete();
		Copy(d);
	}
	return *this;
}

Disk& Disk::operator = (Disk&& d) {
	if (this != &d) {
		Delete();
		Move(d);
	}
	return *this;
}


const Imenik* Disk::GetImenik() const {
	return koren;
}

Imenik* Disk::GetImenik() {
	return koren;
}

