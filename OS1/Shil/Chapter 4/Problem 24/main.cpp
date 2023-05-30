#include <iostream>
#include <pthread.h>
#include <vector>
#

using namespace std;

enum class Error {ARGS = 1};

class PrimeNumber {
    static int n;

public:
    // outputs all prime numbers less or equal than n
    static void* OutputPrimes(void* arg) {
        n = atoi(((char**)arg)[0]);

        vector <bool> IsPrime(n, true);
        IsPrime[0] = IsPrime[1] = false;

        for (int it = 2; it <= n; it ++)
            if (IsPrime[it])
                for (int itVector = 2 * it; itVector <= n; itVector += it)
                    IsPrime[itVector] = false;

        for (int it = 2; it <= n; it ++)
            if (IsPrime[it])
                cout << it << endl;

        pthread_exit(nullptr);
    }

    // inits arguments
    static void Init(int _n) { n = _n; }
};

int PrimeNumber::n = - 1;

int main(int argC, char* argV[]) {
    if (argC != 2) {
        cerr << "Wrong number of arguments" << endl;
        exit((int)(Error::ARGS));
    }

    pthread_t tId;
    pthread_attr_t defAttr;

    pthread_attr_init(&defAttr);
    pthread_create(&tId, &defAttr, PrimeNumber::OutputPrimes, argV + 1);
    pthread_join(tId, nullptr);
    return 0;
}
