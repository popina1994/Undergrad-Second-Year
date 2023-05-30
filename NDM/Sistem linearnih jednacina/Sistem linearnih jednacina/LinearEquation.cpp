#include <iostream>
#include <map>
#include <set>
#include <functional>
#include <cmath>
#include "LinearEquation.h"

bool IsZero(double d) {
    return (fabs(d) < EPSILON);
}

bool LinearEquation::CheckEquality() const {
    return IsZero(m.begin()->second);
}

double& LinearEquation::operator[](const string& s) {
    return m[s];
}

double& LinearEquation::operator[](int idx) {
    auto it = m.begin();

    for (int i = 0; i < idx; i ++)
        it++;
    return it->second;
}

bool LinearEquation::CheckInfTilEnd(int curCol) const {
    auto it= m.begin();
    for (int cnt = 0; cnt < curCol + 1; cnt++)
        it++;

    for (; it != m.end(); it++)
        if (!IsZero(it->second))
            return true;
    return false;
}

ostream& operator<<(ostream& out, const LinearEquation& le) {
    out.precision(2);
    out.setf( ios::fixed, ios::floatfield);

    auto it = le.m.begin();
    it++;

    for (; it != le.m.end(); it++) {
        if (it->second >= 0)
            out <<  "+";
        out << it->second << " * " << it->first << " ";
    }

    out << "= ";

    it = le.m.begin();
    if (it->second < 0)
        out << "+";
    out << -it->second;

    return out;
}

const string& SystemOfLinearEquations::IthElement(const set<string>& s, int idx) {
    auto it = s.begin();

    for (int i = 0; i < idx && it != s.end(); i++) it ++;

    if (it == s.end())
        return "";

    return *it;
}


LinearEquation& SystemOfLinearEquations::operator[](int i) {
    return v[i];
}

const LinearEquation& SystemOfLinearEquations::operator[](int i) const {
    return v[i];
}

void LinearEquation::AddVariablesInSet(set <string>& s) const {
    for (auto it = m.begin(); it != m.end(); it++)
        s.insert(it->first);
}

void Merge(LinearEquation& l1, LinearEquation& l2) {
    for (auto it = l1.m.begin(); it != l1.m.end(); it++)
        l2[it->first] += 0;
    for (auto it = l2.m.begin(); it != l2.m.end(); it++)
        l1[it->first] += 0;
}

void SystemOfLinearEquations::PushBack(LinearEquation* le) {
    v.push_back(*le);
    le->AddVariablesInSet(name);
}

int SystemOfLinearEquations::NumberOfEquations() const {
    return v.size();
}

int SystemOfLinearEquations::NumberOfUnknown() const {
    return name.size() - 1;
}

void SystemOfLinearEquations::AddZeroVariablesInEquations() {
    for (int i = 0; i < NumberOfEquations() - 1; i++)
        Merge(v[i], v[i+1]);
    for (int i = NumberOfEquations() - 1; i > 0; i --)
        Merge(v[i], v[i-1]);
}

bool SystemOfLinearEquations::PutZeroColDown(int& curRow, int& curCol) {
    for (int row = curRow; row < NumberOfEquations(); row++) // puts zeroes in current column "down"
        if (!IsZero(v[row][curCol])) {
            if (row != curRow) {
                cout << "Zamenjene vrste " << curRow + 1 << " " << row + 1 << endl;
                swap(v[curRow], v[row]);
                cout << *this << endl;

            }
            return true;
        }
    return false;
}

bool SystemOfLinearEquations::OneStepDownTriangle(int& curRow, int& curCol) {
    if (!PutZeroColDown(curRow, curCol)) {
        curRow++;
        curCol++;
        return false;
    }

    cout << "Dodavanje jednacine sa rednim brojem " << curRow + 1 << " jednacinama ispod" << endl;
    for (int row = curRow + 1; row < NumberOfEquations(); row++) {
        double coef = (-1) * v[row][curCol] / v[curRow][curCol];

        v[row][0] += v[curRow][0] * coef;

        for (int col = curCol; col < NumberOfUnknown() + 1; col++)
            v[row][col] += v[curRow][col] * coef;
    }
    curCol++;
    curRow++;
    return true;
}

SystemOfLinearEquations::SOLUTION SystemOfLinearEquations::OneStepUpperTriangle(int& curRow, int& curCol) {
    if (IsZero(v[curRow][curCol]) && (!IsZero(v[curRow][0]) && !v[curRow].CheckInfTilEnd(curCol)) )
      return NOSOL;

    if ( (IsZero(v[curRow][curCol]) && IsZero(v[curRow][0])) || v[curRow].CheckInfTilEnd(curCol)) {
        curRow--; curCol--;
        return INF;
    }

    cout << "Oduzimanje promenljive " << IthElement(name, curCol) << " od vrsta iznad vrste " << curRow + 1 << endl;

    v[curRow][0] /= v[curRow][curCol];
    sol.push_back(-v[curRow][0]);
    v[curRow][curCol] = 1;
    for (int row = curRow - 1; row >= 0; row--) {
        v[row][0] += v[row][curCol] * (-1) * v[curRow][0];
        v[row][curCol] = 0;
    }

    curRow--;
    curCol--;
    return ONE;
}


SystemOfLinearEquations::SOLUTION SystemOfLinearEquations::CheckDown(int curRow) {
    for (int row = curRow + 1; row < NumberOfEquations(); row++)
        if (!v[row].CheckEquality())
            return NOSOL;
    return ONE;

}


void SystemOfLinearEquations::StepByStep() {
    int curRow = 0, curCol = 1;

    AddZeroVariablesInEquations();

    cout << *this << endl;
    while ( (curCol < NumberOfUnknown() + 1) && (curRow < NumberOfEquations()))
        if (OneStepDownTriangle(curRow, curCol))
            cout << *this << endl;
    if ( (curCol == NumberOfUnknown() + 1) || (curRow == NumberOfEquations()) ) {
        curCol--; curRow--;
    }

    SOLUTION curSol;
    numSol = ONE;
    if (curCol < NumberOfEquations())
        numSol = CheckDown(curRow);
    if (numSol == NOSOL) {
        cout << "Nema resenja" << endl;
                return;
    }

    while ( (curCol > 0) && (curRow >= 0)) {
            curSol = OneStepUpperTriangle(curRow, curCol);
            if (curSol == NOSOL) {
                numSol = NOSOL;
                cout << "Nema resenja" << endl;
                return;
            }
            else if (curSol == INF)
                numSol = INF;

            cout << *this << endl;
    }
    if (numSol == INF)
        cout << "Beskonacno mnogo resenja" << endl;
    else {
        cout << "Konacno mnogo" << endl;
        auto it = name.begin();
        it++;
        for (int idx = sol.size() - 1; idx >= 0; idx--, it++)
            cout << *it << " = " << sol[idx] << endl;
    }
}

void SystemOfLinearEquations::SolutionOutput(ostream& out) {
    if (numSol == ONE) {
        auto it = name.begin();
        it++;
        for (int idx = sol.size() - 1; idx >= 0; idx--, it++)
            out << *it << " = " << sol[idx] << endl;
    }
    else if (numSol == INF)
        out << "Beskonacno mnogo" << endl;
    else
        out << "Nema resenja" << endl;
}

ostream& operator<<(ostream& out, const SystemOfLinearEquations& sle) {
    for (int idx = 0; idx < sle.NumberOfEquations(); idx ++)
        out << sle[idx] << endl;
    return out;
}

