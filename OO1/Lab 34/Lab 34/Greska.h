#ifndef _GRESKA_H_
#define _GRESKA_H_

#include <exception>

using namespace std;

class OutOfRange : public exception {
public:
	const char* what() const;
};

#endif