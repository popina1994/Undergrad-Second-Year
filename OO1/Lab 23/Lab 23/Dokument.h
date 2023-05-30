#ifndef _Dokument_h_
#define _Dokument_h_

#include <iostream>


using namespace std;

class Dokument {
	int IDDok;
	int kap;
	int n = 0;
	char** x; // niz niski

	void Premesti(Dokument&);
	void Kopiraj(const Dokument&);
	void Obrisi();
protected:
	void Pisi(ostream& out) const;
	friend ostream& operator<<(ostream& out, const Dokument&);
public:
	static int Primarni;
	Dokument(int _kap = 5);
	Dokument(const Dokument&);
	Dokument(Dokument&&);
	~Dokument();

	Dokument& operator=(const Dokument&);
	Dokument& operator=(Dokument&&);

	
	int BrojPasusa() const;
	int Duzina() const;
	Dokument& operator+=(const char* ubaci);
	const char* operator[](int idx) const;
};
#endif