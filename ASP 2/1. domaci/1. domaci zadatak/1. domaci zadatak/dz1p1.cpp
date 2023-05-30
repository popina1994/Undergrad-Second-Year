#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

struct Element {
	int key, cnt; //key contains value of element, cnt number of appearances of element in search
	bool  mark; // mark if element is deleted
	Element();
	Element(int _key);
};

// contains array and insert, empty, delete and search techniques implemented
class Array {
	int n; // n - length of array, if there is going to be issues just const int
	Element *x; // array x with properties of each element
	double k; //  parameter in k transposition
	int p;
	double t; // p counter of repeated searches which are finished in first t * elements of array
	int sfulSearch;
	/* shift elements in Array starting with index start to index end one place right
	insert x[end] into x[start] */
	void ShiftRight(int start, int end);

public:
	Array();
	Array(int _x[], int _size);
	Array(const Array& a);
	Array(Array&& a);
	~Array();

	// resets all counters of appearance of element to 0
	void ResetCounters();

	// delete all elements from array
	void Delete();

	// resizes array, first _n elements will stay on its place, other will be deleted and mark will be set to false
	void Resize(int _n);

	// insert element val in Array, throw exception TOO_MANY_ELEMENTS if there is no more place in array
	void Insert(int val);

	// deletes element from Array, throw exception NO_ELEMENT if there is no element in array
	void Delete(int val);

	// sets parameters of search
	void SetK(double _k = 0);
	void SetP(int _p = 0);
	void SetT(double _t = 0);

	// Every search returns -1 when there is no searched element in array
	// if val is found it swaps with one element in front of him (if not is first element in Array)
	int SearchTransposition(int val);

	// if element is found it becomes first in array, all other are shifted one place right (before element)
	int SearchMoveToBegin(int val);

	//if element is found element swaps place with element k / m
	int SearchKTransposition(int val);

	// if element is found it moves on place k / m, and all other elements are shifted right (before element)
	int SearchKMoveToBegin(int val);

	// if element is found k-th time it moves k places advance
	int SearchProbability(int val);

	/* First it searches elements with Transposition, then it starts using transposition
	when p searches repeatedly end in first t * n elements of array */
	int SearchHybride(int val);

	// copies from array x length len into Array
	void Copy(const int* _x, int len);

	void Print() const;

	// TOO_MANY_ELEMENTS is thrown when there is no more place to insert new element
	enum ERRORS { TOO_MANY_ELEMENTS, TOO_BIG };

};



Element::Element(int _key) : key(_key), cnt(0), mark(true) {}

Element::Element() : cnt(0), mark(false) {}

Array::Array() : n(0), x(nullptr), k(0), p(0), t(0), sfulSearch(0) { }

Array::Array(int _x[], int _size) : n(_size), x(new Element[_size]), k(0), p(0), t(0), sfulSearch(0) {
	for (int idx = 0; idx < n; idx++) {
		x[idx].key = _x[idx];
		x[idx].mark = true;
		x[idx].cnt = 0;
	}
}

Array::Array(const Array& a) : n(a.n), x(new Element[a.n]), k(a.k), p(a.p), t(a.t), sfulSearch(a.sfulSearch) {
	for (int idx = 0; idx < n; idx++)
		x[idx] = a.x[idx];
}

Array::Array(Array&& a) : n(a.n), x(a.x), k(a.k), p(a.p), t(a.t), sfulSearch(a.sfulSearch) {
	a.x = nullptr;
}

void Array::Delete() {
	delete[] x;
	x = nullptr;
	n = 0;
}

Array::~Array() {
	Delete();
}

void Array::Resize(int _n) {
	Array tmp(*this);
	int idx;

	Delete(); // delete current array
	n = _n; // new len
	x = new Element[_n];
	for (idx = 0; idx < _n; idx++)
		if (idx >= tmp.n)
			break;

	while (idx < _n) {
		x[idx].mark = false;
		x[idx].cnt = 0;
		idx++;
	}
}

void Array::Insert(int val) {
	for (int idx = 0; idx < n; idx++)
		if (!x[idx].mark) {
		x[idx].mark = true;
		x[idx].key = val;
		return;
		}
	throw TOO_MANY_ELEMENTS;
}

void Array::Delete(int val) {
	for (int idx = 0; idx < n; idx++)
		if (x[idx].key == val && x[idx].mark) {
		x[idx].mark = false;
		return;
		}
}

void Array::ResetCounters() {
	for (int idx = 0; idx < n; idx++)
		x[idx].cnt = 0;
}

void Array::ShiftRight(int start, int end) {
	Element tmp = x[end + 1]; // it will work end = -1, start = 0, CHECK IT ANYWAYS
	for (int idx = end; idx >= start; idx--) // won't check if there is no place because I USE this function
		x[idx + 1] = x[idx];
	x[start] = tmp;
}

void Array::SetK(double _k) {
	if (_k >= 1)
		throw TOO_BIG;
	k = _k;
}

void Array::SetP(int _p) {
	p = _p;
}

void Array::SetT(double _t) {
	if (_t > 1)
		throw TOO_BIG;
	t = _t;
}

int Array::SearchTransposition(int val) {
	for (int idx = 0; idx < n; idx++)
		if (x[idx].key == val && x[idx].mark) {
		if (idx > 0)
			swap(x[idx], x[idx - 1]);
		return idx;
		}
	return -1;
}

int Array::SearchMoveToBegin(int val) {
	for (int idx = 0; idx < n; idx++)
		if (x[idx].key == val && x[idx].mark) {
		ShiftRight(1, idx - 1);
		return idx;
		}
	return -1;
}

int Array::SearchKTransposition(int val) {
	for (int idx = 0; idx < n; idx++)
		if (x[idx].key == val && x[idx].mark) {
		swap(x[static_cast<int>(floor(k * idx))], x[idx]);
		return idx;
		}
	return -1;
}

int Array::SearchKMoveToBegin(int val) {
	for (int idx = 0; idx < n; idx++)
		if (x[idx].key == val && x[idx].mark) {
		ShiftRight(static_cast<int>(floor(k * idx)), idx - 1);
		return idx;
		}
	return -1;
}

int Array::SearchProbability(int val) {
	for (int idx = 0; idx < n; idx++)
		if (x[idx].key == val && x[idx].mark) {
		x[idx].cnt++;;
		if (idx - x[idx].cnt >= 0)
			ShiftRight(idx - x[idx].cnt, idx - 1);
		else
			ShiftRight(0, idx - 1);
		return idx;
		}
	return -1;
}

int Array::SearchHybride(int val) {
	int idx;
	if (sfulSearch < p) {
		idx = SearchMoveToBegin(val);
		if (idx != -1) {
			if (idx + 1 <= t * n)
				sfulSearch++;
			else
				sfulSearch = 0;
		}
	}
	else
		idx = SearchKTransposition(val);
	return idx;
}

void Array::Copy(const int* _x, int len) {
	Delete();
	x = new Element[len];
	n = len;
	for (int idx = 0; idx < len; idx++) {
		x[idx].cnt = 0;
		x[idx].key = _x[idx];
		x[idx].mark = true;
	}
}

void Array::Print() const {
	cout << "Niz:" << endl;
	for (int idx = 0; idx < n; idx++)
		if (x[idx].mark)
			cout << x[idx].key << " ";
	cout << endl;
}




void OutputMenu(int& choice) {
	cout << "Unesite:\n" << endl;
	cout << "0) ako hocete da prekinete program" << endl;
	cout << "1) ako hocete da ucitate niz" << endl;
	cout << "2) ako hocete da generisete slucajan niz" << endl;
	cout << "3) ako hocete da uneste sekvencu za pretrazivanje" << endl;
	cout << "4) ako hocete da generisete sekvencu za pretrazivanje" << endl;
	cout << "5) ako hocete da pretrazujete transpozicijom" << endl;
	cout << "6) ako hocete da pretrazujete prebacivanjem na pocetak" << endl;
	cout << "7) ako hocete da pretrazujete k-transpozicijom" << endl;
	cout << "8) ako hocete da pretrazujete k-prebacivanjem" << endl;
	cout << "9) ako hocete da pretrazujete prebacivanjem na osnovu verovatnoce" << endl;
	cout << "10) ako hocete da pretrazujete hibridnom tehnikom" << endl;
	cout << "11) ako hocete da ubacite element u niz" << endl;
	cout << "12) ako hocete da obrisete element iz niza" << endl;
	cout << "13) ako hocete da obrisete niz koji se pretrazuje" << endl;
	cout << "14) ako hocete da ispisete niz koji se pretrazuje" << endl;
	cout << "15) ako hocete da ispisete sekvencu kljuceva koji se traze" << endl;
	cout << "16) ako hocete da promenite velicinu niza koji se pretrazuje" << endl;
	cout << "17) ako hocete da podesite parametar k" << endl;
	cout << "18) ako hocete da podesite parametar p" << endl;
	cout << "19) ako hocete da podesite parametar t" << endl;
	cin >> choice;
	cout << endl;
}

void ReadArrayFile(FILE* f, int*& x, int& len) {
	if (f == stdin)
		cout << "unesite duzinu" << endl;
	fscanf(f, "%d", &len);

	delete[] x;
	x = new int[len];

	if (f == stdin)
		cout << "Unesite niz: " << endl;
	for (int idx = 0; idx < len; idx++)
		fscanf(f, "%d", &x[idx]);
	if (f == stdin)
		cout << endl;
}

void ReadArray(int*& x, int& len) {
	int choice;

	cout << "Ako hocete sa standardnog unesite 1" << endl;
	cout << "Ako hocete iz datoteke unesite 2" << endl;
	cin >> choice;

	if (choice == 1)
		ReadArrayFile(stdin, x, len);
	else if (choice == 2) { // reading from file
		FILE* f;
		char s[255];

		cout << "Unesite ime datoteke" << endl;
		scanf("%s", &s);

		f = fopen(s, "r");
		if (f == nullptr) {
			cout << "Pogresno ime datoteke" << endl;
			return;
		}
		ReadArrayFile(f, x, len);
		fclose(f);
	}
}

int Random(int low = 0, int high = 0) {
	return static_cast<int>(((high - low) * static_cast<double>(rand()) / RAND_MAX + low));
	
}

void GenerateSeq(int*& x, int& len, bool search = false, int low = 0, int high = 0) {
	srand(static_cast<unsigned int>(time(0)));

	delete[] x;
	x = new int[len];
	
	if (!search) {
		for (int idx = 0; idx < len; idx++)
			x[idx] = idx;
		for (int idx = len - 1; idx >= 0; idx--) {
			int swapIndex = Random(0, idx);
			swap(x[idx], x[swapIndex]);
		}
	}
	else {
		for (int idx = 0; idx < len; idx++)
			x[idx] = Random(low, high);
	}
}


void PrintSeq(int* x, int len) {
	cout << "Niz: " << endl;
	for (int idx = 0; idx < len; idx++)
		cout << x[idx] << " ";
	cout << endl;
}

using funSearch = int (Array::*)(int);

// uses method search of class a to check number of checked keys until searched key is found
void TestSearch(Array a, funSearch search, const int* seqSearch, int len) {
	double arSum = 0;
	int counter = 0;
	int choice;

	for (int idx = 0; idx < len; idx++) {
		int index = 1 + (a.*search)(seqSearch[idx]);
		arSum += index;
		if (index != 0)
			counter++;
	}
	if (counter != 0)
		arSum /= counter;
	cout << "Broj uporedjivanja " << arSum << endl;

	cout << "Hocete li novodobijeni niz da vidite, pritisnite 1 ako hocete" << endl;
	cin >> choice;
	if (choice == 1) a.Print();
}


int main() {
	Array a; // array which we are searching
	int* x = nullptr; // array which we are generating
	int* seqKey = nullptr; // sequence of searched keys
	int choice, len = 0, lenKey = 0, val, low, high;
	double valDouble;

	OutputMenu(choice);
	while (choice != 0) {
		try {
			switch (choice)  {
			case 1:
				ReadArray(x, len);
				a.Copy(x, len);
				break;
			case 2:
				cout << "Unesite duzinu niza koji hocete da generisete" << endl;
				cin >> len;
				cout << endl;
				GenerateSeq(x, len);
				a.Copy(x, len);
				break;
			case 3:
				ReadArray(seqKey, lenKey);
				break;
			case 4:
				cout << "Unesite duzinu sekvence koju hocete da generisete" << endl;
				cin >> lenKey;
				cout << endl;
				cout << "Unesite donju i gornju granicu sekvence" << endl;
				cin >> low >> high;
				cout << endl;
				GenerateSeq(seqKey, lenKey, true, low, high);
				break;
			case 5:
				TestSearch(a, &Array::SearchTransposition, seqKey, lenKey);
				break;
			case 6:
				TestSearch(a, &Array::SearchMoveToBegin, seqKey, lenKey);
				break;
			case 7:
				TestSearch(a, &Array::SearchKTransposition, seqKey, lenKey);
				break;
			case 8:
				TestSearch(a, &Array::SearchKMoveToBegin, seqKey, lenKey);
				break;
			case 9:
				TestSearch(a, &Array::SearchProbability, seqKey, lenKey);
				break;
			case 10:
				TestSearch(a, &Array::SearchHybride, seqKey, lenKey);
				break;
			case 11:
				cout << "Koji element hocete da ubacite u niz" << endl;
				cin >> val;
				a.Insert(val);
				break;
			case 12:
				cout << "Koji element hocete da izbrisete iz niza" << endl;
				cin >> val;
				a.Delete(val);
				break;
			case 13:
				a.Delete();
				break;
			case 14:
				a.Print();
				break;
			case 15:
				PrintSeq(seqKey, lenKey);
				break;
			case 16:
				cout << "Unesite velicinu na koju menjate" << endl;
				cin >> val;
				cout << endl;
				a.Resize(val);
				break;
			case 17:
				cout << "Unesite velicinu parametra k:" << endl;
				cin >> valDouble;
				a.SetK(valDouble);
				break;
			case 18:
				cout << "Unesite velicinu parametra p:" << endl;
				cin >> val;
				a.SetP(val);
				break;
			case 19:
				cout << "Unesite velicinu parametra t:" << endl;
				cin >> valDouble;
				a.SetT(valDouble);
				break;
			default:
				cout << "Pogresno unet izbor" << endl;
			}

		}
		catch (Array::ERRORS& ArrayError) {
			if (ArrayError == Array::TOO_MANY_ELEMENTS)
				cout << "Ne mozete vise elemenata da ubacite, promenite ogranicenje" << endl;
			else if (ArrayError == Array::TOO_BIG) {
				cout << "Mora vrednost manja od 1 ili jednaka 1" << endl;
			}
		}
		catch (bad_alloc& e) {
			cout << "Nedovoljno memorije" << endl;
		}
		OutputMenu(choice);
	}
	delete[] x; delete[] seqKey; // deleting of temporary arrays
	return 0;
}


