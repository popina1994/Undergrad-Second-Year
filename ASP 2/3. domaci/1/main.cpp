#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <utility>
#include <stack>
#include <vector>
#include <climits>
#include <cstdlib>

using namespace std;

constexpr double EPSILON = 0.000000000000000001;
constexpr int TABLE_SIZE = 10007;

class Key {
    int key;
    string info;

public:
    explicit Key() : key(-1) {};
    explicit Key(int _key, const string& _info) : key(_key), info(_info) {}

    friend bool operator==(const Key& k1, const Key& k2) {
        return k1.key == k2.key;
    }
    friend bool operator==(const Key& k1, int k2) {
        return k1.key == k2;

    }
    friend bool operator==(int k1, const Key& k2) {
        return k1 == k2.key;
    }
    friend bool operator<(const Key& k1, const Key& k2) {
        return k1.key < k2.key;
    }
    friend bool operator<(const Key& k1, int k2) {
        return k1.key < k2;
    }
    friend bool operator<(int k1, const Key& k2) {
        return k1 < k2.key;
    }


    int GetKey() const {
        return key;
    }
    string* GetInfoPt() {
        return &info;
    }

    friend ostream& operator<<(ostream& out, const Key& k) {
        return out << k.key << " " << k.info;
    }
};

class AddressFunction {
public:
    virtual int getAddress(int k, int address, int attempt) const = 0;
    virtual AddressFunction* PolyCopy() const = 0;
    virtual ~AddressFunction() {}
};

class QuadraticHashing : public AddressFunction {
    int c1, c2;
public:
    QuadraticHashing(int _c1 = 0, int _c2 = 1) : c1(_c1), c2(_c2) {}

    QuadraticHashing* PolyCopy() const override {
        return new QuadraticHashing(*this);
    }

    int getAddress(int k, int address, int attempt) const override {
        return address + c1 * attempt + c2 * attempt * attempt;
    }
};

class HashFunction {
public:
    virtual int Hash(int k) const = 0;

    virtual HashFunction* PolyCopy() const = 0;

    virtual ~HashFunction() {};
};

class HashDivision : public HashFunction {
    int n;

public:
    HashDivision(int _n = 1) : n(_n) {}

    HashDivision* PolyCopy() const override {
        return new HashDivision(*this);
    }

    int Hash(int k) const override {
        return k % n;
    }
};



class HashTable {

    struct Element {
        // I did like this because if I choose to have key and string it would be same space allocation
        // maybe string may improve, but this does everything
        Key k;
        bool empty;
        bool deleted;
        // I can speed up initialization of element, but I won't it's too risky
        Element() : empty(true), deleted(false) {}
        Element(const Key& _k, bool _empty = false, bool _deleted = false) : k(_k), empty(_empty), deleted(_deleted) {}
    };

    int size, n, cnt = 0, unsuccAttempt = 0;
    Element* x;
    HashFunction* hashFunction;
    AddressFunction* collisionFunction = nullptr;

    void Copy(const HashTable&);
    void Move(HashTable&);
    void Delete();
    // count stores how many elements are checked
    // if count equals nullptr then it won't count anything
    // returns index of element where search ended
    bool FindKey(int k, int& count, int& idx) const;
    int AdjustHash(int k) const {
        return ((k % size) + size) % size;
    }

public:
    HashTable(int _size) : size(_size), n(0), x(new Element[_size]), hashFunction(new HashDivision(_size)) {
        int c1 = 0, c2 = -1;
        collisionFunction = new QuadraticHashing(c1, c2);
        // collision function
    }

    HashTable(const HashTable&);
    HashTable(HashTable&&);
    ~HashTable();

    HashTable& operator=(const HashTable&);
    HashTable& operator=(HashTable&&);

    string* findKey(int key);
    bool insertKey(int key, const string&);
    bool deleteKey(int key);

    double avgAccessSuccess() const;
    double avgAccessUnsuccess() const;
    double avgAccessUnsuccessEst() const;

    void resetStatistics();
    void clear();
    int keyCount() const;
    int tableSize() const;
    friend ostream& operator<<(ostream&, const HashTable&);
    double fillRatio() const;

    int Min() const; // returns  minimum element in array
    int Max() const; // returns  maximum element in array

    enum Error { DIV_ZERO };
};


void HashTable::Copy(const HashTable& h) {
    size = h.size;
    n = h.n;
    cnt = h.cnt;
    unsuccAttempt = h.unsuccAttempt;
    x = new Element[size];
    for (int idx = 0; idx < size; idx++)
        x[idx] = h.x[idx];
    hashFunction = h.hashFunction->PolyCopy(); // polymorphic copy, do it when you can
    collisionFunction = h.collisionFunction->PolyCopy();
}

void HashTable::Move(HashTable& h) {
    size = h.size;
    h.size = 0;
    n = h.n;
    h.n = 0;
    x = h.x;
    h.x = nullptr;
    cnt = h.cnt;
    unsuccAttempt = h.unsuccAttempt;
    hashFunction = h.hashFunction;
    h.hashFunction = nullptr;
    collisionFunction = h.collisionFunction;
    h.collisionFunction = nullptr;
}

void HashTable::Delete() {
    delete [] x;
    delete hashFunction;
    delete collisionFunction;
}

bool HashTable::FindKey(int k, int& count, int& idx) const {
    int h0 = hashFunction->Hash(k) % size;

    count = 0;

    for (int i = 0; i < size; i ++) {
        idx = AdjustHash(collisionFunction->getAddress(k, h0, i));
        count ++;
        if ((x[idx].k) == k && !x[idx].deleted && !x[idx].empty)
            return true;
        if ( (x[idx].empty) || (k == x[idx].k && x[idx].deleted) )
            return false;
    }
    return false;
}

HashTable::HashTable(const HashTable& h) {
    Copy(h);
}

HashTable::HashTable(HashTable&& h) {
    Move(h);
}
HashTable::~HashTable() {
    Delete();
}

HashTable& HashTable::operator=(const HashTable& h) {
    if (this != &h) {
        Delete();
        Copy(h);
    }
    return *this;
}

HashTable& HashTable::operator=(HashTable&& h) {
    if (this != &h) {
        Delete();
        Move(h);
    }
    return *this;
}

string* HashTable::findKey(int k)  {
    int cntCur, idx;

    if (!FindKey(k, cntCur, idx)) {
        unsuccAttempt++;
        cnt += cntCur;
        return nullptr;
    }

    return x[idx].k.GetInfoPt();
}

bool HashTable::insertKey(int k, const string& s) {
    int cntCur, idx;
    if (FindKey(k, cntCur, idx))
        return false; // key already exists in hash table

    cnt += cntCur;
    unsuccAttempt++;

    if (cntCur == size)  // table is full
        return false;

    n++;
    x[idx] = Element(Key(k, s));
    return true;
}

bool HashTable::deleteKey(int k) {
    int cntCur, idx;
    if (!FindKey(k, cntCur, idx)) {
        cnt += cntCur;
        unsuccAttempt++;
        return false;
    }

    n--;
    x[idx].deleted = true;
    return true;
}

double HashTable::avgAccessSuccess() const {
    stack <int> s;
    int cnt = 0;

    for (int i = 0; i < size; i++)
        if (!x[i].empty && !x[i].deleted)
            s.push(x[i].k.GetKey());

    while (!s.empty()) {
        int curCnt, idx;
        FindKey(s.top(), curCnt, idx);
        cnt += curCnt;
        s.pop();
    }

    if (n == 0)
        throw DIV_ZERO;

    return static_cast<double>(cnt) / n;
}

double HashTable::avgAccessUnsuccess() const {
    if (unsuccAttempt == 0)
        throw DIV_ZERO;

    return static_cast<double>(cnt) / unsuccAttempt;
}

double HashTable::avgAccessUnsuccessEst() const {
    if (1 - fillRatio() < EPSILON)
        throw DIV_ZERO;

    return static_cast<double>(1) / (1 - fillRatio());
}

void HashTable::resetStatistics() {
    unsuccAttempt = 0;
    cnt = 0;
}

void HashTable::clear() {
    for (int idx = 0; idx < size; idx ++) {
        x[idx].empty = true;
        x[idx].deleted = false;
    }
    n = 0;
}

int HashTable::keyCount() const {
    return n;
}

int HashTable::tableSize() const {
    return size;
}

ostream& operator<<(ostream& out, const HashTable& h) {
    for (int idx = 0; idx < h.size; idx++) {
        if (h.x[idx].empty || h.x[idx].deleted)
            out << "EMPTY";
        else
            out << h.x[idx].k;
        out << endl;
    }
    return out;
}

double HashTable::fillRatio() const {
    return static_cast<double>(n) / size;
}

int HashTable::Min() const {
    int minVal = INT_MAX;
    for (int idx = 0; idx < size; idx ++)
        if ( (x[idx].empty == false) && (x[idx].deleted == false) && (x[idx].k < minVal) )
            minVal = x[idx].k.GetKey();
    return minVal;
}

int HashTable::Max() const {
    int maxVal = INT_MIN;
    for (int idx = 0; idx < size; idx ++)
        if ( (x[idx].empty == false) && (x[idx].deleted == false) && (maxVal < x[idx].k ) )
            maxVal = x[idx].k.GetKey();
    return maxVal;
}

int Random(int low, int high) {
    srand(time(nullptr));
    return static_cast<double>(rand()) / RAND_MAX * (high - low) + low;
}


void Statistics(HashTable h, stack<int>& sKeys, stack<string>& sInfo, int n) {
    h.resetStatistics();


    while (!sKeys.empty()) {
        h.insertKey(sKeys.top(), sInfo.top());
        sKeys.pop();
        sInfo.pop();
    }
    if (h.keyCount() == 0)
        return;

    int minVal = h.Min(), maxVal = h.Max();
    for (int i = 0; i < n; i ++)
        h.findKey(Random(minVal, maxVal));

    cout << "Broj uspesnih " << h.avgAccessSuccess() << endl;
    cout << "Broj neuspesni" << h.avgAccessUnsuccess() << endl;
    cout << "Procenjen broj neuspesnih" << h.avgAccessUnsuccessEst() << endl;
}


void OutputMenu(int& choice) {
    string x [] = {
        "da prekinete program",
        "da pronadjete kljuc",
        "da ubacite kljuc",
        "da izbrisete kljuc",
        "prosecan broj pristupa tabeli prilikom uspesnog trazenja",
        "prosecan broj pristupa tabeli prilikom neuspesnog trazenja",
        "procenjen na osnovu popunjenosti prosecan broj pristupa tabeli prilikom neuspesnog trazenja",
        "da resetujete stastiku",
        "da obrisete sve kljuceve",
        "broj kljuceva u tabeli",
        "velicinu tabele",
        "da ispisete sadrzaj tabele",
        "stepen popunjenosti",
        "statisticku funkciju",
        "da unesete velicinu hes tabele"
    };

    cout << "Unesite:" << endl;
    for (unsigned int i = 0; i < sizeof(x) / sizeof(x[0]); i ++)
        cout << i << ") Ako hocete " << x[i] << endl;
    cout << endl;
    cin >> choice;
    cout << endl;
}

int main() {
    int choice;
    HashTable* ptH = nullptr;
    OutputMenu(choice);

    while (choice != 0) {
        int key, file, n;
        string s,* ptS;
        ifstream f;
        stack<int> sKey;
        stack<string> sString;
        try {
            if ( (choice >= 1) && (choice < 14) && (ptH == nullptr))
                cout << "POPIO SI" << endl;
            else {
                switch (choice) {
                case 1:
                    cout << "Unesite kljuc koji trazite" << endl;
                    cin >> key;
                    cout << endl;
                    ptS = ptH->findKey(key);
                    if (!ptS)
                        cout << "kljuc ne postoji" << endl;
                    else
                        cout << "kljuc postoji i sadrzaj je" << endl << *ptS << endl;
                    break;

                case 2:
                    cout << "Uneiste 0 ako hocete sa standradnog, inace ce biti iz datoteke" << endl;
                    cin >> file;

                    if (!file) {
                        cout << "Unesite kljuc koji ubacujete" << endl;
                        cin >> key;
                        cout << "Unesite sadrzaj koji ubacujete" << endl;
                        cin >> s;

                        if (!ptH->insertKey(key, s))
                            cout << "Neuspelo ubacivanje" << endl;
                    } else {
                        cout << "Unesite ime ulazne datoteke" << endl;
                        cin >> s;
                        cout << s << endl;
                        f.open(s);

                        while (!f.is_open()) {
                            cout << "Pogresno ime" << endl;
                            cout << "Unesite ponovo ime ulazne datoteke" << endl;
                            cin >> s;
                            f.open(s);
                        }
                        while (f >> s) {
                            f >> key;
                            if (!ptH->insertKey(key, s))
                                cout << "Neuspesno ubacivanje " << key << " " << s << endl;
                        }

                        f.close();
                    }
                    break;

                case 3:
                    cout << "Unesite kljuc koji brisete" << endl;
                    cin >> key;
                    if (!ptH->deleteKey(key))
                        cout << "Neuspelo brisanje" << endl;
                    else
                        cout << "Uspelo brisanje" << endl;
                    break;

                case 4:
                    cout << "Prosecan broj pristupa pri uspesnom pretrazivanju" << endl;
                    cout << ptH->avgAccessSuccess() << endl;

                    break;

                case 5:
                    cout << "Prosecan broj pristupa tabeli prilikom neuspesnog pretrazivanja je" << endl;
                    cout << ptH->avgAccessUnsuccess() << endl;
                    break;

                case 6:
                    cout << "Procenjen prosecan broj pristupa tabeli prilikom neuspesnog pretrazivanja je" << endl;
                    cout << ptH->avgAccessUnsuccessEst() << endl;
                    break;

                case 7:
                    ptH->resetStatistics();
                    cout << "Resetovana je statistika" << endl;
                    break;

                case 8:
                    ptH->clear();
                    cout << "Obrisana je hes tabela" << endl;
                    break;

                case 9:
                    cout << "Broj umtenutih kljuceva u tabeli je" << endl;
                    cout << ptH->keyCount() << endl;
                    break;

                case 10:
                    cout << "Velicina tabele je" << endl;
                    cout << ptH->tableSize() << endl;
                    break;

                case 11:
                    cout << *ptH;
                    break;

                case 12:
                    cout << "Popunjenost tabele je" << endl;
                    cout << ptH->fillRatio() << endl;
                    break;

                case 13:
                    cout << "-1 je kljuc koji prekida unos" << endl;

                    cout << "Unesite kljuc pa informacije (ako unesete -1 kraj)" << endl;
                    cin >> key;

                    while (key != -1) {
                        cin >> s;
                        sKey.push(key);
                        sString.push(s);
                        cout << "Unesite kljuc pa informacije (ako unesete -1 kraj)" << endl;
                        cin >> key;
                    }

                    cout << "Unesite broj pretrazivanja koje hocete da generisete" << endl;
                    cin >> n;
                    Statistics(*ptH, sKey, sString, n);
                    break;

                case 14:
                    cout << "Unesite velicinu hes tabele" << endl;
                    cin >> n;
                    cout << endl;

                    delete ptH;
                    ptH = new HashTable(n);
                    break;

                default:
                    cout << "Pogresan izbor, molimo ponovo unesite" << endl;

                }
            }
        } catch (const HashTable::Error& e) {
            if (e == HashTable::DIV_ZERO)
                cout << "Deljenje nulom, nemoj da se igras :)" << endl;
        }
        OutputMenu(choice);
    }
    delete ptH;

    return 0;
}
