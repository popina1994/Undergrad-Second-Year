#include <iostream>
#include <cstring>
#include "Autorizovani.h"


using namespace std;

Autorizovani::Autorizovani(const char* _autor, int kap) : Dokument(kap) {
	Dokument::operator+=(_autor);
}