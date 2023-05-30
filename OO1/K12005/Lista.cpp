#include "Lista.h"
#include <iostream>

using namespace std;

List::Node::Node() : next(nullptr) {}

List::Node::Node(const Datum& val) : info(val), next(nullptr) {}

void List::Delete() {
    for (Node* it = begin; it != nullptr; )  {
        Node* tmp = it;
        it = it->next;
        delete tmp;
    }
    begin = nullptr; end = nullptr;
}

List::List() : begin(nullptr), end(nullptr) {}

List::List(const List& l) {
    for (Node* it = l.begin; it != nullptr;) {
        Node* tmpNode = new Node(it->info);

        if (begin == nullptr)
            begin = tmpNode;
        else
            end->next = tmpNode; // if there is at least one element in list
        end = tmpNode; // end of list is new element
    }
}

List::List(List&& l) {
    begin = l.begin; l.begin = nullptr;
    end = l.end; l.end = nullptr;
}

List::~List() {
    Delete();
}

void List::Insert(const Datum& d) {
    Node* tmp = new Node(d);

    if (begin == nullptr)
        begin = tmp;
    else
        end->next = tmp;
    end = tmp;
}

void List::Clear() {
    Delete();
}

int List::Length() const {
    int cnt = 0;

    for (Node* it = begin; it != nullptr; it = it->next, cnt ++);

    return cnt;
}

Datum* List::LatestDate() const {
    if (begin == nullptr)
        return nullptr;
    Datum* date = &begin->info;

    for (Node* it = begin; it != nullptr; it = it->next)
        if (Compare(*date, it->info) < 0)
            date = &it->info;
    return date;
}

bool List::Empty() const {
    return begin == nullptr;
}

void List::Print() const {
    if (begin == nullptr)
        cout << "Prazna" << endl;

    for (Node* it = begin; it != nullptr; it = it->next) {
        it->info.Write();
        if (it != end)
            cout << "->";
    }
    cout << endl;
}
