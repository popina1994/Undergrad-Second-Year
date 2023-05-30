#include "Imenik.h"
#include "Greska.h"
#include "Datoteka.h"
#include <iostream>

using namespace std; 

void Imenik::Copy(const Imenik& i) {
	int size = i.x.Size();
	x.Clear();
	for (int idx = 0; idx < size; idx++)
		x += i.x[idx]->PolyCopy();
	SetName(i.GetName());
	SetSize(i.x.Size());
	SetParent(nullptr);
}

void Imenik::Move(Imenik& i) {
	x = move(i.x);
	SetSize(i.GetSize());
	SetName(i.GetName()); // it's very hard to do this move, without making members protected.
						// and that's bad thing to do
	SetParent(nullptr); // we don't know where will it be moved
}

Imenik::~Imenik() {
	Delete();
}

void Imenik::Delete() {
	for (int i = 0; i < x.Size(); i++)
		delete x[i];
}

Imenik::Imenik(const Imenik& i)  {
	Copy(i);
}

Imenik::Imenik(Imenik&& i) {
	Move(i);
}

Imenik& Imenik::operator=(const Imenik& i) {
	if (this != &i) {
		Delete();
		Copy(i);
	}
	return *this;
}

Imenik& Imenik::operator=(Imenik&& i) {
	if (this != &i) {
		Delete();
		Move(i);
	}
	return *this;
}

Imenik::Imenik(const string& _ime) : Datoteka(_ime, 100){}

Imenik* Imenik::PolyCopy() const {
	return new Imenik(*this);
}

int Imenik::DataNum() const {
	return x.Size();
}

int Imenik::DataSize() const {
	int size = 0;

	for (int i = 0; i < x.Size(); i++)
		size += x[i]->Size();
	
	return size;
}

int Imenik::Size() const {
	return Datoteka::GetSize();
}

Imenik& Imenik::operator+=(const Datoteka& d) {
	for (int i = 0; i < x.Size(); i++)
		if (d.GetName() == x[i]->GetName())
			throw Name_Exists();

	x += d.PolyCopy();
	x[x.Size() - 1]->SetParent(this);
	Datoteka::SetSize(Datoteka::GetSize() + 10);

	return *this;
}

Datoteka* Imenik::operator[](int idx) {
	return x[idx];
}
