#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>


using namespace std;

inline int CeilDiv(int x, int y) {
    return (x + y - 1) / y;
}

struct Key {
    struct infSadrzaj {
        string opis;
        int frekvencija = 0; // it's not allowed to add string without description
    };

    string key; // it's first word from file
    infSadrzaj info;
public:
    void IncFreq(); // increases freq
    void SetDescription(const string&);

    bool operator<(const Key&) const;
    bool operator==(const Key&) const;
    bool operator>(const Key&) const;
    bool operator<=(const Key&) const;
    bool operator>=(const Key&) const;

    friend istream& operator>>(istream& in, Key& key);
    friend ostream& operator<<(ostream& out, const Key& key);

};


void Key::IncFreq() {
    info.frekvencija++;
}

void Key::SetDescription(const string& s) {
    info.opis = s;
}

bool Key::operator<(const Key& k) const {
    return key < k.key;
}

bool Key::operator==(const Key& k) const {
    return key == k.key;
}

bool Key::operator>(const Key& k) const {
    return key > k.key;
}

bool Key::operator<=(const Key& k) const {
    return key <= k.key;
}

bool Key::operator>=(const Key& k) const {
    return key >= k.key;
}

istream& operator>>(istream& in, Key& key) {
    in >> key.key;
    in >> key.info.opis;
    key.info.frekvencija = 1;
    return in;
}

ostream& operator<<(ostream& out, const Key& key) {
    out << key.key << " - ";
    out << key.info.opis << " (";
    out << key.info.frekvencija << ")" << endl;
    return out;
}

// it's smarter to be inside BTree, but who gives a fuck
struct Node {
    Key** key; // array of keys
    Node** child; // array of pointers on children
    int n = 0; // current number of keys in Node
    bool leaf = true;

    Node(int m, Key* _key = nullptr);
    ~Node();

    void NormalInsert(Key* keyInsert);
    void NormalDelete(int idx);

    Node* LeftSibiling(Node* parNode, int idxChild) const;
    Node* RightSibiling(Node* parNode, int idxChild) const;
    int ChildIdx(Node* parNode) const;

    void Move(Node* nodeFrom, Node* parNode, int childIdx, int idxFrom);
    void Merge(Node* rightNode, Node* parNode, int childIdx);
};

Node::Node(int m, Key* _key) : key(new Key*[m]), child(new Node*[m + 1]) {
    for (int idx = 0; idx < m; idx ++) {
        key[idx] = nullptr;
        child[idx] = nullptr;
    }
    child[m] = nullptr;

    if (_key != nullptr) {
        key[0] = _key;
        n = 1;
    }

}


Node::~Node() {
    delete [] key; // it is not logical to delete keys :/
    delete [] child;
    n = 0;
}

void Node::NormalInsert(Key* keyInsert) {
    int idx = n - 1;

    while ( (idx >= 0) && (*key[idx] > *keyInsert) ) {
        key[idx + 1] = key[idx];
        idx --;
    }

    key[idx + 1] = keyInsert;
    n++;
}

void Node::NormalDelete(int idx) {
    if (idx < 0 || idx >= n)
        return;
    delete key[idx];
    for (int i = idx; i < n; i ++)
        key[i] = key[i + 1];
    key[n - 1] = nullptr;
    n--;
}

int Node::ChildIdx(Node* parNode) const {
    for (int i = 0; i <= parNode->n; i ++)
        if (parNode->child[i] == this)
            return i;
    return -1;
}

Node* Node::LeftSibiling(Node* parNode, int idxChild) const {
    if (parNode == nullptr)
        return nullptr;
    if (idxChild - 1 < 0)
        return nullptr;
    return parNode->child[idxChild - 1];
}

Node* Node::RightSibiling(Node* parNode, int idxChild) const {
    if (parNode == nullptr)
        return nullptr;
    if (idxChild + 1 > parNode->n)
        return nullptr;
    return parNode->child[idxChild + 1];
}

void Node::Move(Node* nodeFrom, Node* parNode, int childIdx, int idxFrom) {
    if (idxFrom == nodeFrom->n - 1) { // from left sibiling
        for (int idx = n - 1; idx >= 0; idx --)
            key[idx + 1] = key[idx];
        for (int idx = n; idx >= 0; idx --)
            child[idx + 1] = child[idx];

        key[0] = parNode->key[childIdx-1]; // spusti se odozgo
        parNode->key[childIdx-1] = nodeFrom->key[idxFrom]; // digne se gore
        child[0] = nodeFrom->child[idxFrom + 1]; // pokazivac predje desno
        nodeFrom->key[idxFrom] = nullptr;
        nodeFrom->child[idxFrom + 1] = nullptr;
        nodeFrom->n--;
    } else {
// see this carefully
        key[n] = parNode->key[childIdx]; // spusti se odozgo
        parNode->key[childIdx] = nodeFrom->key[idxFrom]; // digne se gore
        child[n + 1] = nodeFrom->child[0]; // pokazivac predje levo
        for (int idx = 1; idx < nodeFrom->n; idx ++)
            nodeFrom->key[idx - 1] = nodeFrom->key[idx];
        for (int idx = 1; idx <= nodeFrom->n; idx ++)
            nodeFrom->child[idx -1] = nodeFrom->child[idx];
        nodeFrom->key[nodeFrom->n-1] = nullptr;
        nodeFrom->child[nodeFrom->n] = nullptr;
        nodeFrom->n--;
    }
    n++;
}

void Node::Merge(Node* rightNode, Node* parNode, int childIdx) {
    key[n] = parNode->key[childIdx]; // spustis odozgo
    for (int idx = 0; idx < rightNode->n; idx ++)
        key[n + 1 + idx] = rightNode->key[idx];
    for (int idx = 0; idx <= rightNode->n; idx ++)
        child[n + 1 + idx] = rightNode->child[idx];
    n += 1 + rightNode->n;
    delete rightNode;

    for (int idx = childIdx; idx < parNode->n - 1; idx ++)
        parNode->key[idx] = parNode->key[idx + 1];
    parNode->key[parNode->n-1] = nullptr;

    for (int idx = childIdx + 1; idx < parNode->n; idx ++)
        parNode->child[idx] = parNode->child[idx + 1];
    parNode->child[parNode->n] = nullptr;
    parNode->n--;

}

class BTree {
    Node* root = nullptr;
    int m; // order of tree
    Node* Split(Node* y); // returns pointer on parent

    static int Find(Node*, Key*); // returns index of key in current node

    static bool Succ(Key* keyCur, Node* curNode, Node*& parNode, Node*& nextNode);
    static bool Pred(Key* keyCur, Node* curNode, Node*& parNode, Node*& prevNode);

    void DeleteLeaf(Node* curNode, Node* parNode, int idx);
public:
    void Delete();

    BTree(int _m) : m(_m) {}
    ~BTree();

    Key* Find(const string& keySearch, Node*& ptNode, Node*& parentNode) const; // returns Node in which val is contained
    void Insert(Key* key); // inserts key into BTree
    void InOrder() const; // InOrder traversal through tree
    bool Delete(const string& key); // Deletes key with key val from BTree
    void LevelOrder();

};

int BTree::Find(Node* curNode, Key* key) {
    for (int idx = 0; idx < curNode->n; idx ++)
        if (*curNode->key[idx] == *key)
            return idx;
    return -1;
}

bool BTree::Succ(Key* keyCur, Node* curNode, Node*& parNode, Node*& nextNode) {
    int i = Find(curNode, keyCur);

    parNode = nullptr;
    nextNode = curNode;

    if (nextNode->child[i + 1] == nullptr) {
        nextNode = nullptr;
        return false; // there is no successor
    } else
        i++;

    while (nextNode->child[i] != nullptr) {
        parNode = nextNode;
        nextNode = nextNode->child[i];
        i = 0;
    }
    return true;
}

bool BTree::Pred(Key* keyCur, Node* curNode, Node*& parNode, Node*& prevNode) {
    int i = Find(curNode, keyCur);

    parNode = nullptr;
    prevNode = curNode;

    if (prevNode->child[i] == nullptr) {
        prevNode = nullptr;
        return false; // there is no successor
    }

    while (prevNode->child[i] != nullptr) {
        parNode = prevNode;
        prevNode = prevNode->child[i];
        i = prevNode->child[i]->n;
    }
    return true;
}

Node* BTree::Split(Node* y) {
    Node* x;
    Node* z = new Node(m); // check if cur node is root

    Find(y->key[0]->key, y, x);
    int t = CeilDiv(m, 2), i;

    z->n = m - t;

    for (int j = 0; j < z->n; j++) { // keys
        z->key[j] = y->key[t + j];
        y->key[t + j] = nullptr;
    }
    for (int j = 0; j <= z->n; j ++) { // children
        z->child[j] = y->child[t + j];
        y->child[t + j] = nullptr;
    }
    y->n = t - 1;
    Key* middle = y->key[t - 1];
    y->key[t-1] = nullptr;

    if (x == nullptr) {
        x = new Node(m);
        root = x;
        x->child[0] = y;
    }

    for (i = x->n; i >=0; i--) {
        x->child[i + 1] = x->child[i];
        if (y == x->child[i])
            break;
        x->key[i] = x->key[i - 1];
    }
    x->child[i + 1] = z;
    x->key[i] = middle;
    x->n++;
    return x;
}

void BTree::LevelOrder() {
    queue <Node*> q;
    cout << "Uslo" << endl;

    if (root != nullptr)
        q.push(root);

    while (!q.empty()) {
        Node* curNode = q.front();
        q.pop();

        for (int i = 0; i < curNode->n + 1; i ++)
            if (curNode->child[i] != nullptr) // if there is child of current node
                q.push(curNode->child[i]);
        for (int i = 0; i < curNode->n; i ++) {
            if (curNode->key[i] != nullptr)
                cout << *curNode->key[i];
        }
    }
}
void BTree::Delete() {
    queue <Node*> q;

    if (root != nullptr)
        q.push(root);

    while (!q.empty()) {
        Node* curNode = q.front();
        q.pop();

        for (int i = 0; i < curNode->n + 1; i ++)
            if (curNode->child[i] != nullptr) // if there is child of current node
                q.push(curNode->child[i]);
        for (int i = 0; i < curNode->n; i ++)
            delete curNode->key[i];
        delete curNode;
    }
    root = nullptr;
}

BTree::~BTree() {
    Delete();
}

Key* BTree::Find(const string& keySearch, Node*& curNode, Node*& parentNode) const {
    curNode = root;
    parentNode = nullptr;

    while (curNode != nullptr) {
        int idx;
        for (idx = 0; idx < curNode->n ; idx ++) {
            if (keySearch == curNode->key[idx]->key) {
                return curNode->key[idx];
            } else if (keySearch < curNode->key[idx]->key) break;
        }
        parentNode = curNode;
        curNode = curNode->child[idx]; // whether has broken in for or in checking
    }
    return nullptr;
}


void BTree::Insert(Key* key) {
    Node* curNode,* parNode;
    Key* ptKey = this->Find(key->key, curNode, parNode);

    if (root == nullptr) {
        root = new Node(m, key);
        return;
    }

    if (ptKey != nullptr) { // key exists in tree
        ptKey->SetDescription(key->info.opis);
        ptKey->IncFreq();
        delete key;
        return;
    }
    parNode->NormalInsert(key);
    while (parNode->n == m)
        parNode = Split(parNode);
}

// do when you can
void BTree::DeleteLeaf(Node* curNode, Node* parNode, int idx) {
    int childIdx, t = CeilDiv(m, 2);
    Node* rightSibiling,* leftSibiling,* granNode;

    curNode->NormalDelete(idx); // deletes key

    while (parNode != nullptr &&  curNode->n < t - 1) {
        childIdx = curNode->ChildIdx(parNode);
        rightSibiling = curNode->RightSibiling(parNode, childIdx);
        leftSibiling = curNode->LeftSibiling(parNode, childIdx);
        Find(parNode->key[0]->key, parNode, granNode);

        if (leftSibiling != nullptr && leftSibiling->n > t - 1)
            curNode->Move(leftSibiling, parNode, childIdx, leftSibiling->n - 1);
        else if (rightSibiling != nullptr && rightSibiling->n > t - 1)
            curNode->Move(rightSibiling, parNode, childIdx, 0);
        else if (leftSibiling != nullptr)
            leftSibiling->Merge(curNode, parNode, childIdx - 1);
        else
            curNode->Merge(rightSibiling, parNode, childIdx);
        if (root->n == 0) {
            curNode = root;
            parNode = nullptr;
            }
        else {
            curNode = parNode;
            parNode = granNode;
        }
    }

    if (root->n == 0 ) {
        Node* tmp = root;
        root = root->child[0];
        delete tmp;
    }
}

bool BTree::Delete(const string& key) {
    Node* curNode,* parNode,* parSwapNode ,* swapNode;
    Key* deleteKey = Find(key, curNode, parNode);
    int swapIdx = -1, idx;

    if (!deleteKey)
        return false;
    idx = Find(curNode, deleteKey);
    if (Succ(deleteKey, curNode, parSwapNode, swapNode))
        swapIdx = 0;
    else if (Pred(deleteKey, curNode, parSwapNode, swapNode))
        swapIdx = swapNode->n - 1;

    if (swapIdx != -1) { // not leaf
        Key* ptKey = curNode->key[idx];
        curNode->key[idx] = swapNode->key[swapIdx];
        swapNode->key[swapIdx] = ptKey;

        parNode = parSwapNode;
        curNode = swapNode;
        idx = swapIdx;
    }

    DeleteLeaf(curNode, parNode, idx);



    return true;
}

void BTree::InOrder() const {
    stack <Node*> s;
    stack <int> sIdx;

    if (root == nullptr) {
        cout << "Prazno stablo" << endl;
        return;
    }
    s.push(root);
    sIdx.push(0);

    while ( s.top()->child[0] != nullptr ) {
        s.push(s.top()->child[0]); // let's find most left node
        sIdx.push(0);
    }

    while (!s.empty()) {
        Node* ptNode = s.top();
        int idx = sIdx.top();

        if (ptNode->n == idx) {
            s.pop();
            sIdx.pop();
        } else {
            cout << *(ptNode->key[idx]) << endl;
            sIdx.top()++;
            ptNode = ptNode->child[idx + 1];
            while (ptNode != nullptr) {
                s.push(ptNode);
                sIdx.push(0);
                ptNode = ptNode->child[0];
            }
        }
    }
}

void OutputMenu(int& choice) {
    const char* output[] = {
        "ako hocete da prekinete program",
        "ako hocete da napravite B stablo sa m cvorova",
        "ako hocete da izbrisete trenutno stablo",
        "ako hocete da umetnete kljuc i informacije sa standardnog ulaza",
        "ako hocete da obrisete kljuc i informacije sa standardnog ulaza",
        "ako hocete da nadjete kluc i da ispisete informacije sa standardnog ulaza",
        "ako hocete da ispisete stablo u inorder poretku na standardnom ulazu",
        "ako hocete da ubacite kljuceve i informacije u stablo iz datoteke"
    };
    cout << "Unesite" << endl;
    for (unsigned int idx = 0; idx < sizeof(output) / sizeof(const char*); idx ++)
        cout << idx << ") " << output[idx] << endl;
    cin >> choice;
    cout << endl;
}

int main() {
    int choice;
    BTree* ptTree = nullptr;

    //freopen("DZ2_Recnik_10K.txt", "r", stdin);

    OutputMenu(choice);
    while (choice != 0) {
        int m;
        Key key, *ptKey;
        Node* curNode,* parNode;
        string keyDelete, keySearch, inputName;
        ifstream f;
        if ( (ptTree == nullptr) && (choice != 1 && choice != 2))
            cout << "ZEZNUO SI SE\nSREDI SE\nNESTO SI POPIO\n";
        else {
            switch (choice) {

            case 1:
                delete ptTree;
                cout << "Unesite maksimalno grananje cvora stabla" << endl;
                cin >> m;
                cout << endl;
                ptTree = new BTree(m);
                break;

            case 2:
                delete ptTree;
                cout << "Stablo je izbrisano" << endl;
                ptTree = nullptr;
                break;

            case 3:
                cout << "Unesite kljuc i informacioni sadrzaj koji umecete" << endl;
                ptKey = new Key;
                cin >> *ptKey;
                cout << endl;
                ptTree->Insert(ptKey);
                cout << "Kljuc je ubacen u stablo" << endl;
                break;

            case 4:
                cout << "Unesite kljuc koji brisete iz stabla" << endl;
                cin >> keyDelete;
                cout << endl;
                if (!ptTree->Delete(keyDelete))
                    cout << "Kljuc nije obrisan iz stabla" << endl;
                else
                    cout << "Kljuc je obrisan iz stabla" << endl;
                break;

            case 5:
                cout << "Unesite kljuc koji trazite" << endl;
                cin >> keySearch;
                ptKey = ptTree->Find(keySearch, curNode, parNode);
                if (ptKey == nullptr)
                    cout << "Ne postoji dati element u stablu" << endl;
                else
                    cout << ptKey->info.opis << endl;
                break;

            case 6:
                ptTree->InOrder();
                break;
            case 7:
                cout << "Unesite ime ulazne datoteke" << endl;
                cin >> inputName;
                cout << endl;
                f.open(inputName);
                if (f.is_open()) {
                    ptKey = new Key;
                    while (f >> *ptKey) {
                        ptTree->Insert(ptKey);
                        ptKey = new Key;

                    }
                    delete ptKey; // eof key hasn't been read
                    f.close();
                } else
                    cout << "Greska u otvaranju" << endl;

                break;

            default:
                cout << "Pogresan izbor, molimo vas unesite ponovo" << endl;
            }

        }
        OutputMenu(choice);
    }

    delete ptTree;
    // for every Case, there are assholes :) delete ptTree;
    return 0;
}
