#ifndef _GRESKA_H_
#define _GRESKA_H_

#include <exception>

using namespace std;

class GreskaPuna {
public:
	const char* what() const;
};

class GreskaNepostojeci {
public:
	const char* what() const;
};

#endif _GRESKA_H_