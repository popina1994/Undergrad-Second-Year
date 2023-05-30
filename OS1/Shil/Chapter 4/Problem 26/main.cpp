#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;

class Fibonacci {
    static vector <long long> fib;
public:
    static void* GenerateFib(void* arg) {
        int n = atoi((char*)arg);

        fib.resize(n + 1);

        fib[0] = 0; fib[1] = 1;

        for (int idx = 2; idx <= n; idx ++)
            fib[idx] = fib[idx - 1] + fib[idx - 2];


        pthread_exit(nullptr);
    }

    static void OutputFibonacci() {
        for (auto it : fib)
            cout << it << endl;
    }

};


vector <long long> Fibonacci::fib;

int main(int argC, char * argV[]) {

    pthread_t tId;
    pthread_attr_t defAttr;

    pthread_attr_init(&defAttr);
    pthread_create(&tId, &defAttr, Fibonacci::GenerateFib, argV[1]);
    pthread_join(tId, nullptr);

    Fibonacci::OutputFibonacci();

    return 0;
}
