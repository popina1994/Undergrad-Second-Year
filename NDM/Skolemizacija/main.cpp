#include <iostream>
#include <fstream>
#include "const.hpp"
#include "Translation.hpp"


using namespace std;

void OutputMenu(int& choice) {
    cout << "Унесите 0 ако хоћете да прекинете, 1 ако хоћете да наставите" << endl;
    cin >> choice;
    cout << endl;
}

int main() {
    int choice;

    OutputMenu(choice);
    while (choice != 0) {
        FileLoading();
        OutputMenu(choice);
    }

    return 0;
}
