#ifndef _Zbirka_h_
#define _Zbirka_h_

#include <iostream>

using namespace std;

class Zbirka {
protected:
    int* x;
    int kap, zauzet = 0;

    void Kopiraj(const Zbirka&);
    void Premesti(Zbirka&);
    void Obrisi();
public:
    Zbirka(int _kap = 10) :  x(new int[_kap]), kap(_kap) {}
    Zbirka(const Zbirka& kap);
    Zbirka(Zbirka&&);
    virtual ~Zbirka();

    Zbirka& operator=(Zbirka&);
    Zbirka& operator=(Zbirka&&);
    virtual Zbirka& operator+=(int d);
    int Zauzetost() const;
    int operator[](int idx) const;
    friend ostream& operator<<(ostream& out, const Zbirka&);
};

#endif // _Zbirka_h_
