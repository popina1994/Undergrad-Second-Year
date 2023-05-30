#ifndef _Array_h_
#define _Array_h_

#include <iostream>

using namespace std;

struct Element {
    int key, cnt; //key contains value of element, cnt number of appearances of element in search
    bool  mark; // mark if element is deleted
    Element();
    Element(int _key);
};

// contains array and insert, empty, delete and search techniques implemented
class Array {
    int n; // n - length of array, if there is going to be issues just const int
    Element *x; // array x with properties of each element
    double k; //  parameter in k transposition
    int p;
    double t; // p counter of repeated searches which are finished in first t * elements of array
    int sfulSearch;
    /* shift elements in Array starting with index start to index end one place right
        insert x[end] into x[start] */
    void ShiftRight(int start, int end);

public:
    Array();
    Array(int _x[], int _size);
    Array(const Array& a);
    Array(Array&& a);
    ~Array();

    // resets all counters of appearance of element to 0
    void ResetCounters();

    // delete all elements from array
    void Delete();

    // resizes array, first _n elements will stay on its place, other will be deleted and mark will be set to false
    void Resize(int _n);

    // insert element val in Array, throw exception TOO_MANY_ELEMENTS if there is no more place in array
    void Insert(int val);

    // deletes element from Array, throw exception NO_ELEMENT if there is no element in array
    void Delete(int val);

    // sets parameters of search
    void SetK(double _k = 0);
    void SetP(int _p = 0);
    void SetT(double _t = 0);

    // Every search returns -1 when there is no searched element in array
    // if val is found it swaps with one element in front of him (if not is first element in Array)
    int SearchTransposition(int val);

    // if element is found it becomes first in array, all other are shifted one place right (before element)
    int SearchMoveToBegin(int val);

    //if element is found element swaps place with element k / m
    int SearchKTransposition(int val);

    // if element is found it moves on place k / m, and all other elements are shifted right (before element)
    int SearchKMoveToBegin(int val);

    // if element is found k-th time it moves k places advance
    int SearchProbability(int val);

    /* First it searches elements with Transposition, then it starts using transposition
     when p searches repeatedly end in first t * n elements of array */
    int SearchHybride(int val);

    // copies from array x length len into Array
    void Copy(const int* _x, int len);

    void Print() const;

    // TOO_MANY_ELEMENTS is thrown when there is no more place to insert new element
    enum ERRORS { TOO_MANY_ELEMENTS, TOO_BIG };

};

#endif // _Array_h_
