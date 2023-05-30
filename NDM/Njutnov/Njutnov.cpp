#include "Njutnov.h"
#include <cmath>

using namespace std;


bool IsZero(double d) {
    if (fabs(d) < EPSILON)
        return true;
    return false;
}

Newton::Newton(int _n, double* _x, double* _y) : n(_n) {
    x = new double[n];
    y = new double*[n];
    for (int idx = 0; idx < n; idx ++)
        y[idx] = new double[n];

    for (int idx = 0; idx < n; idx++)
        x[idx] = _x[idx];
    for (int idx = 0; idx < n; idx++)
        y[idx][0] = _y[idx];
}

void Newton::Copy(const Newton& nj) {
    n = nj.n;
    x = new double[n];
    for (int idx = 0; idx < n; idx ++)
        x[idx] = nj.x[idx];

    y = new double*[n];
    for (int idx = 0; idx < n; idx ++)
        y[idx] = new double[n];

    for (int row = 0; row < n; row ++)
        for (int col = 0; col < n; col ++)
            y[row][col] = nj.y[row][col];
}

void Newton::Move(Newton & nj) {
    n = nj.n;
    x = nj.x; nj.x = nullptr;
    y = nj.y; nj.y = nullptr;
}

void Newton::Delete() {
    delete [] x;
    for (int idx = 0; idx < n; idx ++)
        delete  y[idx];
    delete [] y;
}

Newton::Newton(const Newton& nj) {
    Copy(nj);
}

Newton::Newton(Newton&& nj) {
    Move(nj);
}

Newton::~Newton() {
    Delete();
}

Newton& Newton::operator =(const Newton& nj) {
    if (this != &nj) {
        Delete();
        Copy(nj);
    }
    return *this;
}

Newton& Newton::operator=(Newton&& nj) {
    if (this != &nj) {
        Delete();
        Move(nj);
    }
    return *this;
}

// trebao je oop, ali
double Newton::operator ()(double val, int deg, bool first) const {
    double result, quotient = 1;

    if (!first)
       result = y[n-1][0];
    else
        result = y[0][0];
    if (deg > n)
        deg = n;

    if (first) {
        for (int i = 1; i < deg; i++){
            quotient *= (val - x[i-1])/(i * (x[1]-x[0]));
            result += y[0][i] * quotient;
        }
    }
    else {
        for (int i = 1; i < deg; i++){
            quotient *= (val - x[n-i])/(i * (x[1]-x[0]));
            result += y[n-i-1][i]*quotient;
        }
    }
    return result;
}

void Newton::Evaluate() {
    for (int col = 1; col  <= n - 1; col ++)
        for (int row = 0; row  <= n - col - 1; row++)
              y[row][col] = y[row + 1][col-1] - y[row][col - 1] ;
}

int Newton::Size() const {
    return n;
}

double Newton::operator()(int row, int col) const {
    return y[row][col];
}
