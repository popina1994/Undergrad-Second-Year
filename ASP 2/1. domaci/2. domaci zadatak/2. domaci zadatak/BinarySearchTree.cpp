#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "BinarySearchTree.h"

using namespace std;

const int MAX_WIDTH = 3;

Node::Node(int _key) : key(_key), left(nullptr), right(nullptr), parent(nullptr) {}

Interval::Interval(int _begin, int _end)  : begin(_begin), end(_end) {}

void Interval::Set(int _begin, int _end) {
    begin = _begin;
    end = _end;
}

BinarySearchTree::BinarySearchTree() : root(nullptr), maxHeight(-1), nNodes(0), t(1) {}

void BinarySearchTree::Delete() {
    queue <Node*> q;

    if (root == nullptr)
        return;

    q.push(root);
    while (!q.empty()) {
        root = q.front();
        q.pop();
        if (root->left != nullptr)
            q.push(root->left);
        if (root->right != nullptr)
            q.push(root->right);
        delete root;
    }
    root = nullptr;
    nNodes = 0;
    maxHeight = -1;
}

int BinarySearchTree::MaxHeight() const {
    return maxHeight;
}

int BinarySearchTree::MinHeight() const {
    return static_cast<int>(ceil(log(nNodes + 1) / log(2) - 1));
}

BinarySearchTree::~BinarySearchTree() {
    Delete();
}

Node* BinarySearchTree::Min(Node* curRoot) const {
    if (curRoot == nullptr)
        return nullptr; // empty tree

    Node* tmpRoot = curRoot;
    while (tmpRoot->left != nullptr) // most left node
        tmpRoot = tmpRoot->left;
    return tmpRoot;
}

Node* BinarySearchTree::Succ(Node* curRoot) const {
    if (curRoot == nullptr)
        return nullptr; // empty tree

    Node* nextNode = Min(curRoot->right);
    if (nextNode != nullptr)
        return nextNode;

    nextNode = curRoot;
    while (nextNode->parent != nullptr && nextNode->parent->right == nextNode)
        nextNode = nextNode->parent;
    return nextNode->parent;
}

void BinarySearchTree::Inorder() const {
    Node* itRoot = Min(root);

    while (itRoot != nullptr) {
        printf("%d\n", itRoot->key);
        itRoot = Succ(itRoot);
    }
}

void BinarySearchTree::StandardInsert(int key) {
    Node* parent = nullptr, *tmpRoot = root, *newNode;
    int curHeight = 0;
    // tmpRoot is root through iteration, newNode is node in which key is inserted

    newNode = new Node(key);
    while (tmpRoot != nullptr) {
        parent = tmpRoot;
        if (tmpRoot->key == key)
            throw SAME_KEY; // same key already exists in tree, damn you
        if (key < tmpRoot->key) // insert in left subtree
            tmpRoot = tmpRoot->left;
        else
            tmpRoot = tmpRoot->right; // insert in right subtree
        curHeight++;
    }

    if (parent == nullptr) // key is inserted in empty tree
        root = newNode;
    else {
        newNode->parent = parent;
        if (key < parent->key)
            parent->left = newNode;
        else
            parent->right = newNode;
    }
    nNodes++;
    maxHeight = max(curHeight, maxHeight);


}

void BinarySearchTree::Reconfigure() {
    vector <int> v;
    queue <Interval> q;
    Node* tmpRoot = Min(root); // first root in inorder Search

    while (tmpRoot != nullptr) { // inserts all keys in inorder into vector
        v.push_back(tmpRoot->key);
        tmpRoot = Succ(tmpRoot);
    }
    Delete(); // deletes current tree
    q.push(Interval(0, v.size() - 1));
    while (!q.empty()) {
        Interval inter = q.front();
        int mid = (inter.begin + inter.end) / 2;

        if (inter.begin <= inter.end) { // if element exists
            StandardInsert(v[mid]);
            q.push(Interval(inter.begin, mid - 1));
            q.push(Interval(mid + 1, inter.end));
        }
        q.pop();
    }
    v.clear();
}


void BinarySearchTree::Insert(int key) {
    int minHeight = MinHeight();

    StandardInsert(key);

    cout << *this;
    if (maxHeight >= minHeight * t) {
        Reconfigure();
        cout << "Posle rekonfigurisanja" << endl << *this;
    }
}

ostream& operator<<(ostream& out, BinarySearchTree& bst) {
    queue <Node*> q;
    int maxHeight = bst.MaxHeight();
    long long nNodes = (1ll << (maxHeight + 1)) - 1; // number of nodes

    q.push(bst.root);
    for (int height = 0; height <= maxHeight; height++) {
        for (int idx = 0; idx < (1ll << height); idx ++ ) {

            Node* curRoot = q.front();
            q.pop();

            if (height < maxHeight) {  // not last level,
                if (curRoot == nullptr) {
                    q.push(nullptr);
                    q.push(nullptr);
                } else {
                    q.push(curRoot->left);
                    q.push(curRoot->right);
                }
            }

            if (curRoot == nullptr)
                out << setw(MAX_WIDTH * ((nNodes + 1) >> height)) << "NULL";
            else
                out << setw(MAX_WIDTH * ((nNodes + 1) >> height)) << curRoot->key;

        }
        out << endl;
    }

    return out;
}

istream& operator>>(istream& in, BinarySearchTree& bst) {
    bst.Delete();

    int val;
    while (in >> val)
        bst.Insert(val);

    in.clear();
    return in;
}

void BinarySearchTree::SetT(int _t) {
    t = _t;
}

