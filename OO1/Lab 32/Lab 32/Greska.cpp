#include "Greska.h"

using namespace std;

const char* GreskaPuna::what() const {
	return "Zbirka je puna!!!";
}

const char* GreskaNepostojeci::what() const {
	return "Indeks izvan opsega";
}