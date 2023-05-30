#ifndef _TACKA_H_
#define _TACKA_H_

#include <cmath>
#include <iostream>

using namespace std;

template <typename T>
class Tacka {
	T x, y;
public:
	explicit Tacka(T _x = 0, T _y = 0) : x(_x), y(_y) {}
	
	T GetX() const { return x; }
	T GetY() const { return y; }
	double Distance(const Tacka& t) const { return sqrt((t.x - x) * (t.x - x) + (t.y - y) * (t.y - y)); }
	friend ostream& operator<<(ostream& out, const Tacka& t) {
		return out << "(" << t.x << ", " << t.y << ")";
	}
};

#endif