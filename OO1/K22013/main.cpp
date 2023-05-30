#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class Domina {
    int a, b;
public:
    explicit Domina(int _a = 0, int _b = 0) : a(_a), b(_b) {}

    Domina& operator~() {
        int c = a;
        a = b;
        b = c;
        return *this;
    }

    friend bool operator==(const Domina& d1, const Domina& d2) {
        return ( ( (d1.a == d2.b) && (d1.b == d2.a)) || ( (d1.b == d2.b) & (d1.a == d2.a) ) );
    }

    friend ostream& operator<<(ostream& out, const Domina& d) {
        return out << "(" << d.a << ", " << d.b << ")";
    }
};

class Skup {
protected:
    struct Elem {
        Domina info;
        Elem* next;
        Elem(const Domina& _info, Elem* _next = nullptr) : info(_info), next(_next) {}
    };
    Elem *begin = nullptr,* end = nullptr;
private:
    void Kopiraj(const Skup& s);
    void Premesti(Skup& s);
    void Brisi();
public:
    Skup() {}
    Skup(const Skup& s) { Kopiraj(s); }
    Skup(Skup&& s) { Premesti(s); }
    virtual ~Skup() { Brisi(); }
    Skup& operator=(const Skup& s) {
        if (this != &s) {
            Brisi();
            Kopiraj(s);
        }
        return *this;
    }
    Skup& operator=(Skup&& s) {
        if (this != &s) {
            Brisi();
            Premesti(s);
        }
        return *this;
    }
    bool Ima()

};

int main() {
    Domina d(1, 2);
    return 0;
}
