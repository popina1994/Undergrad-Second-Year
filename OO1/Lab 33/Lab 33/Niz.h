#ifndef _NIZ_H_
#define _NIZ_H_

#include "Greska.h"

template<typename T> 
class Niz {
	T* x;
	int kap;
	int n = 0;

	void Copy(const Niz& niz) {
		kap = niz.kap;
		n = niz.n;
		x = new T[n];
		for (int i = 0; i < n; i++)
			x[i] = niz.x[i];
	}
	void Move(Niz& niz) {
		kap = niz.kap; niz.kap = 0;
		n = niz.n; niz.n = 0;
		x = niz.x; niz.x = nullptr;
	}
	void Delete() {
		delete[] x;
	}
public:
	Niz(int _kap= 5) : kap(_kap), x(new T[_kap]){}
	Niz(const Niz& niz) { Copy(niz); }
	Niz(Niz&& niz) { Move(niz); }
	~Niz() { Delete(); }

	Niz& operator=(const Niz& niz) {
		if (this != &niz) {
			Delete();
			Copy(niz);
		}
		return *this;
	}
	Niz& operator=(Niz&& niz) {
		if (this != &niz) {
			Delete();
			Move(niz);
		}
		return *this;
	}

	Niz& operator+=(const T& t) {
		if (n == kap) {
			kap += 5;
			T* y = new T[kap];
			for (int i = 0; i < n; i++)
				y[i] = x[i];
			delete[] x;
			x = y;
		}
		x[n++] = t;
		return *this;
	}

	const T& operator[](int idx) const {
		if ((idx < 0) || (idx >= n))
			throw Out_Of_Bounds();
		return x[idx];
	}
	T& operator[](int idx)  {
		if ((idx < 0) || (idx >= n))
			throw Out_Of_Bounds();
		return x[idx];
	}

	int Size() const {
		return n;
	}

	void Clear() {
		n = 0;
	}
};

#endif