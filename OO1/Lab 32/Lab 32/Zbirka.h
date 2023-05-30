#ifndef _ZBIRKA_H_
#define _ZBIRKA_H_

#include <iostream>
#include "Greska.h"

template <typename T>
class Zbirka {
	T** x;
	int kap;
	int n = 0; // trenutni broj elemenata u nizu
	
	void Copy(const Zbirka& z) {
		kap = z.kap;
		n = z.n;
		x = new T*[kap];

		for (int i = 0; i < n; i++)
			x[i] = new T(*z.x[i]);
	}
	void Move(T& z) {
		kap = z.kap; z.kap = 0;
		n = z.n; z.n = 0;
		x = z.x; z.x = nullptr;
	}
	void Delete() {
		cout << "Motherfucker" << endl;
		for (int i = 0; i < n; i++)
			delete x[i];
		delete[] x;
	}
public:
	Zbirka(int _kap = 10) : kap(_kap) { x = new T*[kap]; }
	Zbirka(const Zbirka& z) { Copy(z); }
	Zbirka(Zbirka&& z) { Move(z); }
	~Zbirka() { Delete(); }

	Zbirka& operator=(const Zbirka& z) {
		if (this != &z) {
			Delete();
			Copy(z);
		}
		return *this;
	}

	Zbirka& operator=(Zbirka&& z) {
		if (this != &z){
			Delete();
			Move(z);
		}
		return *this;
	}

	Zbirka& operator+=(const T& t) {
		if (n == kap)
			throw GreskaPuna();
		x[n++] = new T(t);
		return *this;
	}

	const T& operator[](int idx) const {
		if ((idx < 0) || (idx >= n))
			throw GreskaNepostojeci();
		return *x[idx];
	}
	int Size() const {
		return n;
	}

	friend ostream& operator<<(ostream& out, const Zbirka& z) {
		for (int i = 0; i < z.n; i++)
			out << *z.x[i] << endl;
		return out;
	}
};

#endif