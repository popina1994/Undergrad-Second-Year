#include "Parser.h"
#include "LinearEquation.h"
#include "Error.h"
#include <string>
#include <cctype>

using namespace std;

LinearEquation* ReadFile::ptLe = nullptr;
SystemOfLinearEquations* ReadFile::ptSystem = nullptr;


bool ReadFile::IsAritmetic(int c) {
    return ( (c == '=') || (c == '+') || (c == '-'));
}

ReadFile::ReadFile(const string& s) : fileName(s) {
    f.open(s);
    if (!f.is_open())
        throw Bad_File_Name(s);
}

int ReadFile::ReadChar() {
    pos++;
    return f.get();
}

void ReadFile::ReadSpaces() {
    while(isspace(f.peek()) && (f.peek() != '\n')) { // remove spaces before sign
        ReadChar();
    }
}

double ReadFile::ReadNumber(bool first) {
    int sign = 1;
    bool noSign = true, noNum = true;
    double num = 0, power = 1;

    ReadSpaces();
    if ( (f.peek() == '+') || (f.peek() == '-') ) { // remove sign
        sign = 1 - 2 * (ReadChar() == '-');
        noSign = false;
    }
    ReadSpaces();

    if ( (islower(f.peek()) || isupper(f.peek()) ) && (!noSign || (noSign && first) ) )// there is no number
        return sign;
    ReadSpaces();

    if (!first && noSign) { // there is no sign, not first
        FreeMemory();
        throw Bad_Sign(line, pos, fileName);
    }

    while (isdigit(f.peek())) { // before '.'
        num = num * 10 + ReadChar() - '0';
        noNum = false;
    }

    if (f.peek() == '.') { // real number
        ReadChar();
        noNum = false;
    } else if (islower(f.peek()) || isupper(f.peek()) || (IsAritmetic(f.peek()) && !noNum)) // there is variable
        return sign * num;
    else if ( (isspace(f.peek()) || (f.peek() == '=')) && !noNum)
        return sign * num;
    else {
        FreeMemory();

        throw Bad_Number(line, pos, fileName);
    }

    while (f.peek() <= '9' && f.peek() >= '0') { //after '.'
        power /= 10;
        num += power * (ReadChar() - '0');
    }

    return sign * num;
}

string* ReadFile::ReadVariable() {
    string* sol = new string;

    ReadSpaces();
    while (!isspace(f.peek()) && !IsAritmetic(f.peek()) && !isdigit(f.peek()) && (f.peek() != '='))
        sol->push_back(ReadChar());
    ReadSpaces();

    return sol;
}

void ReadFile::AddVariable(bool leftSide, bool first) {
    double num;
    string* var;
    int sign = 1;

    if (!leftSide)
        sign = -1;

    num = sign * ReadNumber(first);
    var = ReadVariable();
    (*ptLe)[*var] += num;
    delete var;
}

LinearEquation* ReadFile::ReadLine() {
    if ( (f.peek() == EOF))
        return nullptr;

    line++;
    pos = 1;
    ptLe = new LinearEquation;

    (*ptLe)[""] = 0;
    AddVariable(true, true);
    while (f.peek() != '=' && f.peek() != '\n')  // do assignment
        AddVariable();

    int assignNumber = ('=' ==ReadChar()); // read '='
    if (assignNumber == 0) {
        FreeMemory();
        throw Bad_Assigment(line, pos, fileName);
    }

    AddVariable(false, true);
    while (f.peek() != '\n' && f.peek() != '=')
        AddVariable(false);

    assignNumber += ('=' == ReadChar()); // read \n
    if (assignNumber != 1) {
        FreeMemory();
        throw Bad_Assigment(line, pos, fileName);
    }

    return ptLe;
}

SystemOfLinearEquations* ReadFile::ReadSystem() {
    ptSystem = new SystemOfLinearEquations;

    while (ptLe = ReadLine()) {
        ptSystem->PushBack(ptLe);
        delete ptLe;
        ptLe = nullptr;
    }

    SystemOfLinearEquations* ptCopy = ptSystem;
    ptSystem = nullptr;
    return ptCopy;
}
