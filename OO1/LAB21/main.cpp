#include <iostream>
#include "Zbirka.h"
#include "Skup.h"
#include "Uredjena.h"

using namespace std;

void OutputMenu(int& choice) {
    const char* output[] = {
        "prekinete program",
        "odaberete zbirku",
        "odaberete uredjenu",
        "odaberete skup",
        "dodata element"
    };

    cout << "Unesite" << endl;

    for (int idx = 0; idx < sizeof(output) / sizeof(output[0]); idx ++)
        cout << idx << ") ako hocete da " << output[idx] << endl;
    cin >> choice;
}

int main() {
    Zbirka* ptZ = nullptr;
    int choice;

    OutputMenu(choice);
    while (choice != 0) {
        int val;
        switch (choice) {
        case 1:
            delete ptZ;
            ptZ = new Zbirka;
            break;

        case 2:
            delete ptZ;
            ptZ = new Uredjena;
            break;

        case 3:
            delete ptZ;
            ptZ = new Skup;
            break;
        case 4:
            cout << "Unesite element" << endl;
            cin >> val;
            cout << endl;
            *ptZ+=val;
            cout << *ptZ;
            break;
        default:
            cout << "Pogreasn izbor" << endl;

        }
        OutputMenu(choice);
    }

    return 0;
}
