#include <iostream>
#include <cstdio>
#include <cstring>
#include "Error.h"
#include "Parser.h"
#include "LinearEquation.h"

using namespace std;

void OutputMenu(int& choice) {
    string s[] = {
        "da prekinete program",
        "da unesete sistem linearnih jednacina iz zadate datoteke",
        "da ispisete sistem",
        "da ispisete resenja sistema (ili oblik ako ima beskonacno)",
        "da ispisete recenje sistema korak po korak"
    };
    cout << "Unesite" << endl;

    for (unsigned int i = 0; i < sizeof(s) / sizeof(s[0]); i ++)
        cout << i << ") ako hocete " << s[i] << endl;
    cin >> choice;

}

int main() {
    int choice;
    SystemOfLinearEquations* ptSystem = nullptr;
    ReadFile* ptReadFile = nullptr;
    bool read = false;
    string fileName;

    cout << "Copyright Ђорђе Живановић" << endl;

    OutputMenu(choice);

    while (choice != 0) {
        if ((choice <=4) && (choice >= 2) && (ptSystem == nullptr) )
            cout << "Molim vas, unesite sistem!!!" << endl;
        else {
            try {
                switch (choice) {
                case 1:
                    cout << "Unesite ime datoteke" << endl;
                    cin  >> fileName;
                    cout << endl;

                    delete ptReadFile;
                    ptReadFile = nullptr; // if exception is thrown
                    delete ptSystem;
                    ptSystem = nullptr;

                    ptReadFile = new ReadFile(fileName);
                    ptSystem = ptReadFile->ReadSystem();
                    read = false;
                    cout << "Uspesno ucitan sistem jednacina!" << endl;
                    break;
                case 2:
                    cout << *ptSystem;
                    break;
                case 3:
                    if (!read) {
                        cout << "Prvo resite" << endl;

                    } else {
                        ptSystem->SolutionOutput(cout);

                    }
                    break;

                case 4:
                    if (!read) {
                        ptSystem->StepByStep();
                        read = true;
                    } else {
                        cout << "Vec je resen" << endl;
                    }
                    break;
                default:
                    cout << "Pogresan izbor, molimo vas unesite ponovo" << endl;

                }
            } catch (ErrorReading& e) {
                e.WritePosition();
                cout << e.what() << endl;
            } catch (Bad_File_Name& bfe) {
                cout << bfe.what() <<  bfe.GetFileName()  <<  endl;
            }
        }
        OutputMenu(choice);
    }
    delete ptReadFile;
    delete ptSystem;

    return 0;
}
