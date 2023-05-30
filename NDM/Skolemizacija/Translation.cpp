#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "const.hpp"
#include "Translation.hpp"

using namespace std;

char CurQuant(string& s, int idx) {
    if (idx < s.length() && (s[idx] == FOREACH || s[idx] == EXIST))
        return s[idx];
    return 0;
}

void Transform(string& s, ostream& out) {
    int idx = 1, cnt = 0; // idx is index of current char, cnt is counter of constants
    map <char, string> m;

    while (CurQuant(s, idx) == EXIST) {
        m[s[idx + 1]] = "c" + to_string(cnt); // every char in new string will be replaced with c_cnt
        cnt++;
        idx += 4;
    }
    // Make map
    cnt = 0;
    string curString = "";
    bool existForEach = false;
    while (CurQuant(s, idx)) {
        if (s[idx] == FOREACH) {

            out << string(s, idx - 1, 4);
            if (!existForEach) {
                curString.push_back(s[idx + 1]);
                existForEach = true;
            } else {
                curString.push_back(',');
                curString.push_back(s[idx+1]);
            }
        } else {
            cnt ++;
            m[s[idx+1]] = "f" + to_string(cnt) + "(" + curString + ")";
        }
        idx += 4;
    }
    for (idx --; idx < s.length(); idx ++) {
        if (m.find(s[idx]) != m.end())
            out << m[s[idx]];
        else
            out << s[idx];
    }
    out << endl;
}

void FileLoading() {
    string inFileName;

    cout << "Унесите име фајла из којег хоћете да изразе сређујете" << endl;
    cin >> inFileName;
    cout << endl;

    ifstream in;
    in.open(inFileName);

    while (!in.is_open()) {
        cout << "Погрешно име, молимо поново унесите име фајла из којег хоћете да изразе сређујете" << endl;
        cin >> inFileName;
        in.open(inFileName);
    }

    string outFileName;
    cout << "Унесите име фајла у који хоћете да испишете или stdout ако хоћете на стандардни излаз да испишете" << endl;
    cin >> outFileName;

    string s;
    ofstream out;
    if (outFileName == "stdout")
        while (getline(in, s))  Transform(s, cout);
    else {
        out.open(outFileName);
        while (!out.is_open()) {
            cout << "Грешка при стварању датотеке, молимо покушајте поново" << endl;
            cin >> outFileName;
            out.open(outFileName); // it won't  open stdout, because stdout is regulary opened
        }
        while (getline(in, s))  Transform(s, out);
        out.close();
    }

    in.close();
}
