#include <iostream>
#include <pthread.h>
#include <climits>

using namespace std;

enum class ERROR { NO_INPUT = 1};
constexpr int THREADS = 3;

class Statistic {
    static int min, max, n;
    static double avg;
public:
    static void Init(int _n) { n = _n; }
    static void* Average(void* param) {
        char** arg = (char**)(param);

        for (int idx = 0; idx < n; idx ++) {
            avg += atoi(arg[idx]);
        }
        avg /= n;
        pthread_exit(0);
    }

    static void* Minimum(void* param) {
        char** arg = (char**)(param);

        for (int idx = 0; idx < n; idx ++) {
            int val = atoi(arg[idx]);
            min = min < val ? min : val;
        }
        pthread_exit(0);
    }


    static void* Maximum(void* param) {
        char** arg = (char**)(param);

        for (int idx = 0; idx < n; idx ++) {
            int val = atoi(arg[idx]);
            max = max > val ? max : val;
        }
        pthread_exit(0);
    }

    static int Minimum() { return min; }
    static int Maximum() { return max; }
    static double Average() { return avg; }
};

int Statistic::min = INT_MAX, Statistic::max = INT_MIN, Statistic::n = -1;
double Statistic::avg = 0;

using ptFunction = void* (*)(void*) ;



int main(int argC, char* argV[]) {
    pthread_attr_t defAttr; // default arguments in initialisation of thread
    pthread_t threadId[THREADS];
    ptFunction fun[THREADS] = { Statistic::Average, Statistic::Minimum, Statistic::Maximum};


    if (argC == 1) { // no data for input is giver
        cerr << "Nothing for input" << endl;
        exit((int)ERROR::NO_INPUT);
    }
    Statistic::Init(argC - 1);

    for (int idx = 0; idx < THREADS; idx ++)  {
        pthread_attr_init(&defAttr);
        pthread_create(&threadId[idx], &defAttr, fun[idx], argV + 1);

    }
    for (int idx = 0; idx < THREADS; idx ++ ) {
        pthread_join(threadId[idx], NULL);
        switch (idx) {
            case 0 :
                cout << "The average value is " << Statistic::Average() << endl;
                break;
            case 1 :
                cout << "The minimum value is " << Statistic::Minimum() << endl;
                break;
            case 2 :
                cout << "The maximum value is " << Statistic::Maximum() << endl;
                break;
        }
    }

    return 0;
}
