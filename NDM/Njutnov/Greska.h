#ifndef GRESKA_H
#define GRESKA_H

#include <exception>

using namespace std;

class NoData : public exception {
public:
    int row, col;
    NoData(int _row, int _col);
    const char* what() const noexcept;
};

#endif // GRESKA_H
