#ifndef _GRESKA_H_
#define _GRESKA_H_

#include <exception>

using namespace std;

class Out_Of_Bounds : public exception {
	const char* what() const;
};

class Name_Exists : public exception {
	const char* what() const;
};

#endif