#ifndef _ZBIRKA_H_
#define _ZBIRKA_H_

#include "Greska.h"
#include <iostream>

using namespace std;

template<typename T>
class Zbirka {
	T* x;
	int cap;
	int n;

	void Copy(const Zbirka& z) {
		cap = z.cap;
		n = z.n;
		x = new T[cap];
		for (int i = 0; i < z.n; i++)
			x[i] = z.x[i];
	}

	void Delete() {
		delete[] x;
	}
public:
	Zbirka(int _cap = 10) : cap(_cap), n(0), x(new T[_cap]) {}
	Zbirka(const Zbirka& z) {
		Copy(z);
	}
	Zbirka& operator=(const Zbirka& z) {
		if (this != &z) {
			Delete();
			Copy(z);
		}
		return *this;
	}
	~Zbirka() {
		Delete();
	}
	Zbirka& operator+=(const T& t) {
		if (n == cap) {
			cap += 3;
			
			T* y = new T[cap];
			for (int idx = 0; idx < n; idx++)
				y[idx] = x[idx];
			delete[] x;
			
			x = y;
		}
		x[n++] = t;
		return *this;
	}
	const T& operator[](int idx) const {
		if ((idx < 0) || (idx >= n))
			throw OutOfRange();
		return x[idx];
	}
	T& operator[](int idx) {
		if ((idx < 0) || (idx >= n))
			throw OutOfRange();
		return x[idx];
	}

	void Clear() { n = 0; }

	int Size() const { return n; }
	void DeleteElement(int idx){
		if ((idx < 0) || (idx >= n))
			throw OutOfRange();
		for (int i = idx + 1; idx < n; idx++)
			x[i - 1] = x[i];
		n--;
	}

	friend ostream& operator<<(ostream& out, const Zbirka& z) {
		for (int i = 0; i < z.n; i++)
			out << z[i] << " ";
		out << endl;
		return out;
	}
};

#endif 