#include <iostream>
#include <cmath>

using namespace std;

constexpr double PI = 3.1415129, EPSILON = 0.000001;

constexpr bool Equal(double a, double b) {
    return fabs(a - b) < EPSILON;
}

class Stvar {
public:
    virtual ~Stvar() = 0;
    virtual bool operator==(const Stvar& s) const = 0;
};

inline Stvar::~Stvar() {}

class Proizvod : public Stvar {
    static int id;
    int idP;

public:
    explicit Proizvod()  {
        idP = id++;
    }
    Proizvod(const Proizvod& ) {
        idP = id++;
    }
    Proizvod& operator=(const Proizvod&) {
        return *this;
    }
    virtual char Oznaka() const = 0;
    virtual double Zapremina() const = 0;
    virtual Proizvod* PolyCopy() const = 0;
    bool operator==(const Stvar& p) const override {
        return Oznaka() == dynamic_cast<const Proizvod&>(p).Oznaka();
    }

protected:
    virtual void Write(ostream& out) const {
        out << Oznaka() << " " <<  idP;
    }
    friend ostream& operator<<(ostream& out, const Proizvod& p) {
        p.Write(out);
        return out;
    }
};

class Sanduk: public Proizvod {
    double a, b, c;
public:
    explicit Sanduk(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
    char Oznaka() const override {
        return 's';
    }
    double Zapremina() const override {
        return a * b * c;
    }
    Sanduk* PolyCopy() const override {
        return new Sanduk(*this);
    }

    bool operator==(const Stvar& ss) const override {
        Sanduk s = dynamic_cast<const Sanduk&>(ss);
        return Proizvod::operator==(s) &&
               Equal(a, s.a) && Equal(b, s.b) && Equal(c, s.c);
    }
protected:
    void Write(ostream& out) const override {
        Proizvod::Write(out);
        out << " (" << a << ", " << b << ", " << c << ")";
    }
};

class Bure : public Proizvod {
    double r, h;
public:
    explicit Bure(double _r, double _h) : r(_r), h(_h) {}
    char Oznaka() const override {
        return 'b';
    }
    double Zapremina() const override {
        return r * r * PI * h;
    }
    Bure* PolyCopy() const override {
        return new Bure(*this);
    }

    bool operator==(const Stvar& ss) const override {
        Bure b = dynamic_cast<const Bure&>(ss);
        return ( (Proizvod::operator==(b)) && Equal(r, b.r) && Equal(h, b.h));
    }
protected:
    void Write(ostream& out) const override {
        Proizvod::Write(out);
        out << " (" << r << ", " << h << ")";
    }
};

int Proizvod::id  = 0;

class ErrorPuna : public exception {
    const char* what() const noexcept override {
        return "Zbirka je prepunjena";
    }
};

class ErrorNema : public exception {
    const char* what() const noexcept override {
        return "Nema podatka";
    }
};

class ErrorPrevise : public exception {
    const char* what() const noexcept override {
        return "Nema mesta";
    }
};

template <typename T>
class Zbirka {
protected:
    T** x;
    int kap, n;
private:
    void Move(Zbirka& z) {
        kap = z.kap;
        z.kap = 0;
        n = z.n;
        z.n = 0;
        x = z.x;
        z.x = nullptr;
    }

    void Copy(const Zbirka& z) {
        kap = z.kap;
        n = z.n;
        x = new T* [kap];
        for (int idx = 0; idx < n; idx ++)
            x[idx] = z.x[idx]->PolyCopy();
    }
    void Delete() {
        for (int idx = 0; idx < n; idx ++)
            delete x[idx];
        delete [] x;
    }
public:
    explicit Zbirka(int _kap = 10) : kap(_kap) {
        x = new T*[kap];
        n = 0;
    }

    Zbirka(const Zbirka& z) {
        Copy(z);
    }

    Zbirka(Zbirka&& z) {
        Move(z);
    }

    virtual ~Zbirka() {
        Delete();
    }

    Zbirka& operator=(const Zbirka& z) {
        if (this != &z) {
            Delete();
            Copy(z);
        }
        return *this;
    }

    Zbirka& operator=(Zbirka&& z) {
        if (this != &z) {
            Delete();
            Move(z);
        }
        return *this;
    }

    virtual Zbirka& operator+=(const T& p) {
        if (n == kap) throw ErrorPuna();
        x[n++] = p.PolyCopy();
        return *this;
    }

    T* operator-=(const T& p) {
        int idx;
        for (idx = 0; idx < n; idx ++)
            if (*x[idx] == p) {
                T* ptT = x[idx];
                for (int idxShift = idx; idxShift < n - 1; idxShift ++)
                    x[idxShift] = x[idxShift + 1];
                n--;
                return ptT;
            }
        throw ErrorNema();
    }

    int Slobodnih() const {
        return kap - n;
    }

    friend ostream& operator<<(ostream& out, const Zbirka& z) {
        out << "(";
        for (int i = 0; i < z.n; i ++) {
            out << *z.x[i];
            if (i != z.n - 1)
                out << ", ";
        }
        out << ")";
        return out;
    }
};

class Skladiste : public Zbirka<Proizvod> {
    double maxZap;
public:
    explicit Skladiste(double _maxZap, int _kap) : Zbirka<Proizvod>(_kap), maxZap(_maxZap) {}

    Zbirka& operator+=(const Proizvod& p) override {
        if (n == kap) throw ErrorPuna();

        double curZap = 0;
        for (int idx = 0; idx < n; idx ++)
            curZap += x[idx]->Zapremina();
        if (curZap + p.Zapremina() > maxZap)
            throw ErrorPrevise();
        x[n++] = p.PolyCopy();
        return *this;
    }
};

int main() {
    Proizvod* p1 = new Sanduk(1, 2, 3);
    Proizvod* p2 = new Bure(1, 2);
    try {
        Skladiste s(100, 10);
        s += *p1;
        s += *p2;
        delete (s -= *p1);
        cout << s;
    } catch (const exception& e) {
        cout << e.what();
    }

    return 0;
}
