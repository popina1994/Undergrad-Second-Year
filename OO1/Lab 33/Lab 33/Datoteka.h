#ifndef _DATOTEKA_H_
#define _DATOTEKA_H_

#include <string>
#include <iostream>

using namespace std;

class Imenik;

class Datoteka {
	string ime;
	int vel;
	Imenik* parent = nullptr;

protected:
	virtual void Pisi(ostream& out) const;

	
public:
	void SetName(const string&);
	string& GetName();
	const string& GetName() const;

	void SetSize(int size);
	int GetSize() const;

	Datoteka(const string& _ime = "", int _vel = 0);

	virtual int Size() const;
	void SetParent(Imenik* _parent);
	virtual Datoteka* PolyCopy() const;
	
	friend ostream& operator<<(ostream&, const Datoteka&);
};

#endif 