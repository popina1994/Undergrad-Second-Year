#include <iostream>
#include <climits>
#include "Datum.h"
#include "Lista.h"

using namespace std;

int main() {
    List l;

    do {
        l.Clear();

        Datum d;
        while (d.Read())
            l.Insert(d);
        l.Print();

        Datum* latestDate = l.LatestDate();

        if (latestDate == nullptr)
            cout << "Prazna lista" << endl;
        else  {
            latestDate->Write();
            cout << endl;
        }
    }
    while (!l.Empty());

    return 0;
}
