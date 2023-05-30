#ifndef _IMENIK_H_
#define _IMENIK_H_

#include "Datoteka.h"
#include "Niz.h"
#include <string>

using namespace std;

class Imenik : public Datoteka {
	Niz <Datoteka*> x;

	void Copy(const Imenik&);
	void Move(Imenik&);
	void Delete();
public:
	Imenik(const string&);
	Imenik(const Imenik&);
	Imenik(Imenik&&);
	~Imenik();

	Imenik& operator=(const Imenik&);
	Imenik& operator=(Imenik&&);


	Imenik* PolyCopy() const override;

	//int Size() const override; // size of namespace
	// there is two possible ways to do this assignment
	// one is to  size to be 100 + 10 * n
	// the other one is to return size 100 + 10 * n of each size (size of data won't store real size)
	// I chose first because it saves file size
	
	int DataSize() const; // size of all files
	int DataNum() const; // number of files
	int Size() const override;


	Imenik& operator+=(const Datoteka& d);
	
	Datoteka* operator[](int idx) ;
	

};

#endif