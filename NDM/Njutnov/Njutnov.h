#ifndef NJUTNOV_H
#define NJUTNOV_H

constexpr int EPSILON = 0.00000000001;

bool IsZero(double d);

class Newton {
    double** y;
    double* x;
    int n;
    void Move(Newton&);
    void Copy(const Newton&);
    void Delete();
public:
    Newton(int _n = 0, double* _x = nullptr, double* _y = nullptr);
    Newton(const Newton&);
    Newton(Newton&&);
    ~Newton();

    Newton& operator=(const Newton&);
    Newton& operator=(Newton&&);
    double operator() (double x, int deg, bool first = true) const;
    double operator()(int row, int col) const;
    void Evaluate();
    int Size() const;

    const double** ReadTable() const;
};

#endif // NJUTNOV_H
