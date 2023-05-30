#ifndef _Parser_h_
#define _Parser_h_

#include <fstream>
#include <iostream>
#include "Error.h"
#include "LinearEquation.h"

using namespace std;

// reads file which name is
class ReadFile {
    int line = 0, pos = 0;
    string fileName;
    ifstream f;

    static LinearEquation* ptLe;
    static SystemOfLinearEquations* ptSystem;

    static bool IsAritmetic(int c);

    void FreeMemory() {
        delete ptLe; ptLe = nullptr;
        delete ptSystem; ptSystem = nullptr;
    }

    void ReadSpaces();
    int ReadChar();
    // reads number
    double ReadNumber(bool first = false);

    string* ReadVariable();

    LinearEquation* ReadLine();

    // adds variable in current linear equation
    void AddVariable(bool leftSide = true, bool first = false);

public:
    ReadFile(const string& fileName);
    SystemOfLinearEquations* ReadSystem();
};

#endif // _Parser_h_
