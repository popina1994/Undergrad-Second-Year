#include <iostream>
#include "Dokument.h"
#include "Autorizovani.h"
#include "Zbirka.h"

using namespace std;

int main() {
	Zbirka z;
	Autorizovani a("Marko", 2);
	Dokument b;
	z += a;
	z += b;
	cout << z;
	system("pause");
	return 0;
}