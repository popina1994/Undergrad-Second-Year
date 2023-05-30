#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

Element::Element (int _key) : key(_key), cnt(0), mark(true) {}

Element::Element () : cnt(0), mark(false) {}

Array::Array() : n(0), x(nullptr), k(0), p(0), t(0), sfulSearch(0) { }

Array::Array(int _x[], int _size) : n(_size), x(new Element[_size]), k(0), p(0), t(0), sfulSearch(0) {
    for (int idx = 0; idx < n; idx ++) {
        x[idx].key = _x[idx];
        x[idx].mark = true;
        x[idx].cnt = 0;
    }
}

Array::Array(const Array& a) : n(a.n), x(new Element[a.n]), k(a.k), p(a.k), t(a.t), sfulSearch(a.sfulSearch) {
    for (int idx = 0; idx < n; idx ++)
        x[idx] = a.x[idx];
}

Array::Array(Array&& a) : n(a.n), x(a.x), k(a.k), p(a.p), t(a.t), sfulSearch(a.sfulSearch) {
    a.x = nullptr;
}

void Array::Delete() {
    delete [] x;
    x = nullptr;
    n = 0;
}

Array::~Array() {
    Delete();
}

void Array::Resize(int _n) {
    Array tmp(*this);
    int idx;

    Delete(); // delete current array
    n = _n; // new len
    x = new Element[_n];
    for (idx = 0; idx < _n; idx ++)
        if (idx >= tmp.n)
            break;

    while (idx < _n) {
        x[idx].mark = false;
        x[idx].cnt = 0;
        idx++;
    }
}

void Array::Insert(int val) {
    for (int idx = 0; idx < n; idx ++)
        if (!x[idx].mark) {
            x[idx].mark = true;
            x[idx].key = val;
            return;
        }
    throw TOO_MANY_ELEMENTS;
}

void Array::Delete(int val) {
    for (int idx = 0; idx < n; idx ++)
        if (x[idx].key == val && x[idx].mark) {
            x[idx].mark = false;
            return;
        }
}

void Array::ResetCounters() {
    for (int idx = 0; idx < n; idx++)
        x[idx].cnt = 0;
}

void Array::ShiftRight(int start, int end) {
    Element tmp = x[end + 1]; // it will work end = -1, start = 0, CHECK IT ANYWAYS
    for (int idx = end; idx >= start; idx --) // won't check if there is no place because I USE this function
        x[idx + 1] = x[idx];
    x[start] = tmp;
}

void Array::SetK(double _k) {
    if (_k >= 1)
        throw TOO_BIG;
    k = _k;
}

void Array::SetP(int _p) {
    p = _p;
}

void Array::SetT(double _t) {
    if (_t > 1)
        throw TOO_BIG;
    t = _t;
}

int Array::SearchTransposition(int val) {
    for (int idx = 0; idx < n; idx++)
        if (x[idx].key == val && x[idx].mark) {
            if (idx > 0)
                swap(x[idx], x[idx-1]);
            return idx;
        }
    return -1;
}

int Array::SearchMoveToBegin(int val) {
    for (int idx = 0; idx < n; idx++)
        if (x[idx].key == val && x[idx].mark) {
            ShiftRight(1, idx - 1);
            return idx;
        }
    return -1;
}

int Array::SearchKTransposition(int val) {
    for (int idx = 0; idx < n; idx++)
        if (x[idx].key == val && x[idx].mark) {
            swap(x[static_cast<int>(floor(k * idx))], x[idx]);
            return idx;
        }
    return -1;
}

int Array::SearchKMoveToBegin(int val) {
    for (int idx = 0; idx < n; idx ++)
        if (x[idx].key == val && x[idx].mark) {
            ShiftRight(static_cast<int>(floor(k * idx)), idx - 1);
            return idx;
        }
    return -1;
}

int Array::SearchProbability(int val) {
    for (int idx = 0; idx < n; idx ++)
        if (x[idx].key == val && x[idx].mark) {
            x[idx].cnt ++;;
            if (idx - x[idx].cnt >= 0)
                ShiftRight(idx - x[idx].cnt, idx - 1);
            else
                ShiftRight(0, idx - 1);
            return idx;
        }
    return -1;
}

int Array::SearchHybride(int val) {
    int idx;
    if (sfulSearch < p) {
        idx = SearchMoveToBegin(val);
        if (idx != -1) {
            if (idx + 1 <= t * n)
                sfulSearch++;
            else
                sfulSearch = 0;
        }
    } else
        idx = SearchKTransposition(val);
    return idx;
}

void Array::Copy(const int* _x, int len) {
    Delete();
    x = new Element[len];
    n = len;
    for (int idx = 0; idx < len; idx ++) {
        x[idx].cnt = 0;
        x[idx].key = _x[idx];
        x[idx].mark = true;
    }
}

void Array::Print() const {
    cout << "Niz:" << endl;
    for (int idx = 0; idx < n; idx ++)
        if (x[idx].mark)
            cout << x[idx].key << " ";
    cout << endl;
}




