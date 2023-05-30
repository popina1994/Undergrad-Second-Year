#ifndef _Translation_hpp_
#define _Translation_hpp_


#include <string>

using namespace std;

// returns next quantificator if exists, else returns 0
char NextQuant(string& , int);

// do transformation
void Transform(string&, ostream& );

// reads from file text to load, here user will input file name, and everything else
void FileLoading();



#endif // _Translation_hpp_
