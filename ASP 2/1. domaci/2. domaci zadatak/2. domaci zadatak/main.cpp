#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include "BinarySearchTree.h"

using namespace std;

void OutputMenu(int& choice) {
    cout << "Unesite: " << endl;
    cout << "0) ako hocete da prekinete program" << endl;
    cout << "1) ako hocete da promenite parametar T" << endl;
    cout << "2) ako hocete da ucitate stablo" << endl;
    cout << "3) ako hocete ispis stabla" << endl;
    cin >> choice;
    cout << endl;
}

void ReadBSTTest(BinarySearchTree& bst) {
    int choice;

    cout << "Unesite 1 ako cete sa standardnog" << endl;
    cout << "Unesite 2 ako cete iz datoteke" << endl;
    cin >> choice;
    cout << endl;

    if (choice == 1)
        cin >> bst;
    else if (choice == 2) {
        string name;
        ifstream ifs;

        cout << "Unesite ime datoteke" << endl;
        cin >> name;

        ifs.open(name, iostream::in);
        if (ifs.is_open()) {
            ifs >> bst;
        } else cout << "Unesite ispravno ime datoteke" << endl;
    }
}

int main() {
    BinarySearchTree bst;
    int choice;

    OutputMenu(choice);
    while (choice != 0) {
        double dVal;
        string name;
                ofstream ofs;
        try {
            switch(choice) {
            case 1:
                cout << "Unesite parametar t" << endl;
                cin >> dVal;
                cout << endl;
                bst.SetT(dVal);
                break;
            case 2:
                ReadBSTTest(bst);
                break;
            case 3:
                cout << bst;
                break;
            }
        } catch (BinarySearchTree::Error& e) {
            cout << "Ne smeju dva ista elementa u stablu" << endl;
        } catch (bad_alloc& e) {
            cout << "Nema dovoljno memorije" << endl;
        }
        OutputMenu(choice);
    }
    return 0;
}
