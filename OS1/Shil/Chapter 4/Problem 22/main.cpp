#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class MonteCarlo {
    static double pi;
    static int in, n;

    static double RandomNumber(int low = 0, int upper = 1) {
        return (double)rand() / RAND_MAX * (upper - low) + low;
    }

    static double Distance(double x1, double y1, double x2 = 0, double y2 = 0) {
        return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
    }
public:
    static void* Generate(void* param) {
        srand(time(nullptr));

        for (int cnt = 0; cnt < n; cnt ++) {
            double x = RandomNumber(-1, 1), y = RandomNumber(-1, 1);
            if (Distance(x, y) < 1)  in ++ ;
        }
        pi = 4 * (double)(in) / n;
        pthread_exit(nullptr);
    }

    static double GetPi() {
        return pi;
    }
};

double MonteCarlo::pi = 0;
int MonteCarlo::in, MonteCarlo::n = 1'000'000'00;


int main() {

    pthread_t tid;
    pthread_attr_t defAttr;

    pthread_attr_init(&defAttr);
    pthread_create(&tid, &defAttr, MonteCarlo::Generate, nullptr);
    pthread_join(tid, nullptr);

    cout << "Pi value is" << MonteCarlo::GetPi() << endl;

    return 0;
}
