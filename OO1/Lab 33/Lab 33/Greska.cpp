#include "Greska.h"

#include <exception>

using namespace std;

const char* Out_Of_Bounds::what() const {
	return "Izvan granica";
}

const char* Name_Exists::what() const {
	return "Ime vec postoji";
}