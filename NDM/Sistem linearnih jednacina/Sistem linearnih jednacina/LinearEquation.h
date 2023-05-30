#ifndef _LinearEquation_h_
#define _LinearEquation_h_

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <set>

using namespace std;

const double EPSILON = 0.000001;

bool IsZero(double d);

class LinearEquation {
    map <string, double> m; // maps names of variables and values
public:
    double& operator[](const string&);
    double& operator[](int idx);
    // expands unknowns of two variables
    friend void Merge(LinearEquation&, LinearEquation&);
    bool CheckEquality() const;
    // checks coeficinets from curCol+1, if there is coeficient != it will return true
    // (there are infinite solutions)
    bool CheckInfTilEnd(int curCol) const;

    friend ostream& operator<<(ostream&, const LinearEquation&);
    friend istream& operator>>(istream&, LinearEquation&);
    void AddVariablesInSet(set<string>&) const;


};


class SystemOfLinearEquations {
public:
    enum SOLUTION { INF, ONE, NOSOL };
private:
    vector <LinearEquation> v;
    vector <double> sol;
    set <string> name; // set of names of unknown variables

    SOLUTION numSol;

    static const string& IthElement(const set<string>&, int idx);

    int NumberOfUnknown() const;
    int NumberOfEquations() const;

    void AddZeroVariablesInEquations();

    // returns true if it's possible to put in current position non zero element
    bool PutZeroColDown(int&, int&);

    // checks linear equations down of curRow, if there is nonconsistent it will tell that there is no sol
    SOLUTION CheckDown(int curRow);
    // returns true if it's everything okay
    bool OneStepDownTriangle(int& curRow, int& curCol);
    SOLUTION OneStepUpperTriangle(int& curRow, int& curCol);
public:

    LinearEquation& operator[](int i);
    const LinearEquation& operator[](int i) const;
    void PushBack(LinearEquation* );
    void StepByStep();

    void SolutionOutput(ostream& out);
    friend ostream& operator<<(ostream&, const SystemOfLinearEquations&);


};

#endif // _
