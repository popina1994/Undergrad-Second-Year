#include "Error.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

ErrorReading::ErrorReading(int _line, int _pos, const string& s) : line(_line), pos(_pos), fileName(s) {}

void ErrorReading::WritePosition() const {

    cout << "Greska pri citanju sistema linearnih jednacina iz fajla" << endl;
    cout << "Linija: " << line << endl << "Pozicija: " << pos << endl;
}

Bad_Number::Bad_Number(int _line, int _pos, const string& _fileName) : ErrorReading(_line, _pos, _fileName) {}

const char* Bad_Number::what() const  {
    return "Nedozvoljeni oblik broja";
}
Bad_Sign::Bad_Sign(int _line, int _pos, const string& _fileName) : ErrorReading(_line, _pos, _fileName) {}

const char* Bad_Sign::what() const  {
    return "Fali znak ili je pogresan";
}

Bad_Assigment::Bad_Assigment(int _line, int _pos, const string& _fileName) : ErrorReading(_line, _pos, _fileName) {}

const char* Bad_Assigment::what() const  {
    return "Los broj znakova = u redu";
}


Bad_File_Name::Bad_File_Name(const string& s) : fileName(s) {}

const char* Bad_File_Name::what() const  {
    return "Ne postoji ulazni fajl ";
}

const string& Bad_File_Name::GetFileName() const {
    return fileName;
}
