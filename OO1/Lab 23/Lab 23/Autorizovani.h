#ifndef _Autorizovani_h_
#define _Autorizovani_h_

#include <iostream>
#include "Dokument.h"

using namespace std;

class Autorizovani : public Dokument {
public:
	Autorizovani(const char* _autor, int kap = 5);
};

#endif