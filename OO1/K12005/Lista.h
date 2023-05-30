#ifndef _Lista_h_
#define _Lista_h_

#include "Datum.h"

class List {
    struct Node { // Node of linked list
        Datum info;
        Node* next;
        Node();
        Node(const Datum& val);
    };
    Node* begin, *end; // pointers on beginning and end of list

    void Delete(); // deletes current list, and sets begin and end on nullptr


public:
    List();
    List(const List&);
    List(List&&);
    ~List();

    void Insert(const Datum&);
    void Clear();
    int Length() const; // returns length of list
    Datum* LatestDate() const; // returns nullptr if list is empty, else returns latest date in list
    bool Empty() const; // checks if list is empty
    void Print() const; // prints entire list
};
#endif // _Lista_h_
