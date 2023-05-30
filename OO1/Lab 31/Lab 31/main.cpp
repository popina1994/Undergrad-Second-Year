#include <iostream>
#include <string>
#include "Tacka.h"
#include "Mesto.h"
#include "Karta.h"

using namespace std;

Karta k;

int main() {
	int n;

	cout << "Unesite broj mesta" << endl;
	cin >> n;
	
	string ime;
	double x, y;
	for (int i = 0; i < n; i++) {
		cout << "Unesite ime" << endl;
		cin >> ime;
		cout << endl;

		cout << "Unesite koordinate mesta" << endl;
		cin >> x >> y;
		cout << endl;
		Mesto m(ime, x, y);
		k += m;
	}

	cout << "Unesite koordinate tacke kojoj najblize mesto hocete da odredite" << endl;
	cin >> x >> y;
	cout << endl;
	cout << "Mesto najblize datoj tacki je" << endl;
	cout << *k.Najblizi(Tacka<double>(x, y)) << endl;
	cout << k << endl;
	return 0;
}