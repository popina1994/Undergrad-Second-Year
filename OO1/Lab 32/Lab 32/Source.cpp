#include <iostream>
#include "Zbirka.h"
#include "Greska.h"
#include "Element.h"
#include "Stavka.h"
#include "Racun.h"

Stavka s1("Milka", 1, 2), s2("Domacica", 2, 3), s3("Frckavac", 2, 4);

int main() {
	string name, prodName;
	int date, kap, kol, cena;
	Racun* r = nullptr;

	int choice = 1;
	
	while (true) {
		cout << "Unesite 1 ako cete da nastavite" << endl;
		cin >> choice; cout << endl;

		if (choice != 1)
			break;

		cout << "Unesite ime" << endl;
		cin >> name; cout << endl;

		cout << "Unesite datum" << endl;
		cin >> date; cout << endl;

		cout << "Unesite kapacitet" << endl;
		cin >> kap; cout << endl;

		delete r;
		r = new Racun(name, date, kap);

		cout << "Unesite KRAJ za kraj" << endl;

		cout << "Unesite ime proizvoda" << endl;
		cin >> name; cout << endl;

		try {
			while (name != "KRAJ") {
				cout << "Unesite kolicinu" << endl;
				cin >> kol; cout << endl;

				cout << "Unesite cenu" << endl;
				cin >> cena; cout << endl;
				*r += Stavka(name, kol, cena);

				cout << "Unesite KRAJ za kraj" << endl;

				cout << "Unesite ime proizvoda" << endl;
				cin >> name; cout << endl;

			}
		} 
		catch (const GreskaPuna& gp) {
			cout << gp.what();
		}
		cout << "Vrednost robe je" << *r;

	}
	delete r;

	return 0;
}