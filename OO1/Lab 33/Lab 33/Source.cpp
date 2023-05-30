#include <iostream>
#include "Niz.h"
#include "Greska.h"
#include "Datoteka.h"
#include "Imenik.h"
#include "Disk.h"

using namespace std;

Disk d;

Imenik i1("C"), i2("D");
Datoteka c1("C1", 10), c2("C2", 20), d1("D1", 100), d2("D2", 200);

int main() {
	Imenik* root = d.GetImenik();
	i1 += c1; i1 += c2;
	i2 += d1; i2 += d2;
	*root += i1;
	*root += i2;
	Imenik* ptI = dynamic_cast<Imenik*>((*root)[0]);
	cout << *(*ptI)[1];
	Imenik* ptI2 = dynamic_cast<Imenik*>((*root)[1]);
	cout << *(*ptI2)[0] << endl;
	cout << *(*ptI2)[0];
	return 0;
}