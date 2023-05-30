#ifndef _main_h_
#define _main_h_



// contains array and insert, delete and search techniques implemented
class Array {
    int* x,* cnt; // x array, cnt counts number of appearance of element
    int n, k; // n - length of array, k - parameter in k transposition
    int p, t; // p counter of repeated searches which are finished in first t * elements of array
    bool* mark; // marking of elements


public:
    Array();
    Array(int _x[], int _size);
    Array(const Array& a);
    Array(Array&& a);
    ~Array();

    // delete all elements from array
    void Empty();

    // insert element val in Array, throw exception TOO_MANY_ELEMENTS if there is no more place in array
    void Insert(int val);

    // deletes element from Array, throw exception NO_ELEMENT if there is no element in array
    void Delete(int val);

    // sets K
    void SetK();

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

    // First it searches elements with Transposition, then it starts using transposition
    // when p searches repeatedly end in first t * n elements of array
    int SearchHybride(int val);


    // NOT_ENOUGH_MEMORY is thrown when there is no memory (probably size of array which user wants is to big)
    // TOO_MANY_ELEMENTS is thrown when there is no more place to insert new element
    // NO_ELEMENT is thrown when there is no searched element in array
    enum ERRORS { NOT_ENOUGH_MEMORY, TOO_MANY_ELEMENTS, NO_ELEMENT};

};

#endif // _main_h_
