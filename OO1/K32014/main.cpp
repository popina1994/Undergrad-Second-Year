#include <iostream>
#include <exception>
#include <string>

using namespace std;

class Dete {
    char pol;
    string ime;
public:
    explicit Dete(char _pol, const string& _ime) : pol(_pol), ime(_ime) {}
    Dete(const Dete&) = delete;
    Dete(Dete&&) = delete;
    Dete& operator=(const Dete&) = delete;
    Dete& operator=(Dete&&) = delete;

    const string& GetIme() const { return ime; }
    char GetPol() { return pol; }

    friend ostream& operator<<(ostream& out, const Dete& d) {
        return out << d.ime << ":" << d.pol;
    }
};

class Poklon {
    static int id;
    int idx;
    double cena;
public:
    explicit Poklon(double _cena) : idx(id++), cena(_cena) {}
    Poklon(const Poklon& p) :  idx(id++), cena(p.cena) {}
    virtual ~Poklon(){}
    Poklon& operator=(const Poklon& p) {
        cena = p.cena;
        idx = id++;
        return *this;
    }

    virtual char GetOznaka() const = 0;
    virtual char GetPol() const = 0;
    virtual double GetCena() const { return cena; }
    virtual Poklon* PolyCopy() const = 0;

    friend ostream& operator<<(ostream& out, const Poklon& p) {
        return out << p.GetOznaka() << "." << p.idx << "(" << p.cena << ")";
    }
};

int Poklon::id = 0;

class Autic : public Poklon {
    using Poklon::Poklon;
    char GetOznaka() const override { return 'A'; }
    char GetPol() const override { return 'M'; }
    Autic* PolyCopy() const override { return new Autic(*this); }
};

class Lutka : public Poklon {
    using Poklon::Poklon;
    char GetOznaka() const override { return 'L'; }
    char GetPol() const override { return 'Z'; }
    Lutka* PolyCopy() const override { return new Lutka(*this); }
};

class Ukras : public Poklon {
    using Poklon::Poklon;
    char GetOznaka() const override { return 'U'; }
    char GetPol() const override { return '?'; }
    Ukras* PolyCopy() const override { return new Ukras(*this); }
};

class ErrorPrazna : public exception {
    const char* what() const noexcept {
        return "Prazno mali";
    }
};

template <typename T>
class Zbirka {
protected:
    struct Elem {
        Elem* next;
        T* info;
        explicit Elem(T* ptT) : next(nullptr), info(ptT) {}
    };
    Elem* begin,* end;
    void Move(Zbirka<T>& z) {
        begin = z.begin; z.begin = nullptr;
        end = z.end; z.end = nullptr;
    }
private:
    void Copy(const Zbirka<T>& z) {
        begin = nullptr;
        Elem* end = nullptr;
        for (Elem* it = z.begin; it != nullptr; it = it->next) {
            Elem* ptNew = new Elem(it->info->PolyCopy());
            if (begin == nullptr)
                begin = ptNew;
            else
                end->next = ptNew;
            end = ptNew;
        }
    }

    void Delete() {
        for (Elem* it = begin; it != nullptr; ) {
            Elem* pt = it;
            it = it->next;

            delete pt->info;
            delete pt;
        }
    }
public:
    Zbirka() : begin(nullptr), end(nullptr) {}
    Zbirka(const Zbirka<T>& z) {
        Copy(z);
    }
    Zbirka(Zbirka<T>&& z) {
        Move(z);
    }
    ~Zbirka() {
        Delete();
    }
    Zbirka<T>& operator=(const Zbirka<T>& z) {
        if (this != &z) {
            Delete();
            Copy(z);
        }
        return *this;
    }
    Zbirka<T>& operator=(Zbirka<T>&& z) {
        if (this != &z) {
            Delete();
            Move(z);
        }
        return *this;
    }
    Zbirka<T>& operator+=(T* ptT) {
        Elem* ptNew = new Elem(ptT);

        if (end == nullptr)
            begin = ptNew;
        else
            end->next = ptNew;
        end = ptNew;
        return *this;
    }
    T* PopFront() {
        if (begin == nullptr) {
            throw ErrorPrazna();
        }
        else {
            Elem* tmpPt = begin;
            begin = begin->next;
            if (begin == nullptr)
                end = nullptr;
            return tmpPt;
        }
    }

    int Number() const {
        int cnt = 0;
        for (auto it = begin; it != nullptr; it = it->next)
            cnt ++;
        return cnt;
    }

    friend ostream& operator<<(ostream& out, const Zbirka<T>& z) {
        out << "[";
        for (Elem* it = z.begin; it != nullptr; it = it->next) {
            out << *it->info;
            if (it->next != nullptr)
                out << ", ";
        }
        return out << "]";
    }
};

class Magacin : public Zbirka<Poklon> {
    Magacin() = default;
    Magacin(const Magacin&) = delete;
    Magacin(Magacin&&) = delete;
    Magacin& operator=(const Magacin&) = delete;
    Magacin& operator=(Magacin&&) = delete;
};

class ErrorPogresanPol : public exception {
    const char* what() const noexcept {
        return "Pogresan pol";
    }
};

class ErrorNemaSe : public exception {
    const char* what() const noexcept {
        return "Nema se";
    }
};

class Paketic : public Zbirka<Poklon> {
    double dozCena, stvarnaCena;
    char pol;
public:
    Paketic(double _dozCena, double _pol) : dozCena(_dozCena), stvarnaCena(0), pol(_pol) {}
    Paketic& operator+=(Poklon* ptE) {
        if ( (ptE->GetPol() != pol) && (ptE->GetPol() != '?') )
            throw ErrorPogresanPol();
        if ((stvarnaCena + ptE->GetCena()) > dozCena)
            throw ErrorNemaSe();
        Zbirka<Poklon>::operator+=(ptE);
        stvarnaCena += ptE->GetCena();
        return *this;
    }
    double GetDozvoljena() const {
        return dozCena;
    }
    double GetStvarna() const {
        return stvarnaCena;
    }
};



int main() {
    Autic* ptA = new Autic(1);
    Lutka* ptL = new Lutka(2);
    Ukras* ptU = new Ukras(3);
    cout << *ptA << " " << *ptL << " " << *ptU << endl;
    Paketic* ptP = new Paketic(100, 'M');
    (*ptP  += ptA) += ptU;
    cout << *ptP;

    return 0;
}
