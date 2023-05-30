#include "Greska.h"

NoData::NoData(int _row, int _col) : row(_row), col(_col) {}

const char* NoData::what() const noexcept {
    return "Nema vrednosti u tabeli";
}


