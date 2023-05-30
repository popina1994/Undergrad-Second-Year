#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

constexpr int PHILOSOPHERS = 5, TIME_DOWN = 1, TIME_UP = 3;

int PhiIdx[PHILOSOPHERS] = {0, 1, 2, 3, 4};

int Rand(int low, int high) {
    srand(time(nullptr));
    return static_cast<double>(rand()) / RAND_MAX * (high - low) + low;
}

class Philosopher {
    enum STATE { THINKING, EATING, STARVING};
    static STATE philosState[PHILOSOPHERS];
    static pthread_mutex_t mutex;
    static pthread_cond_t condVar[PHILOSOPHERS];

public:
    static void* Run(void* arg) {
        int idx = *(int*)(arg);
        cout << "Idx is" << idx << endl;
        srand(time(nullptr));
        while (true) {

            PickupForks(idx);

            cout << "Philosopher: " << idx << " is eating" << endl;
            sleep(Rand(TIME_DOWN, TIME_UP));

            ReturnForks(idx);

            cout << "Philosopher: " << idx << " is thinking" << endl;
            sleep(Rand(TIME_DOWN, TIME_UP));

        }
    }

    static void PickupForks(int phiNum) {
        pthread_mutex_lock(&mutex);
        int nextPhi = (phiNum + 1) % PHILOSOPHERS, prevPhi = (phiNum + PHILOSOPHERS - 1) % PHILOSOPHERS;

        // philosopher waits untill both of chopsticks are available
        while ( (philosState[nextPhi] == EATING) || (philosState[prevPhi] == EATING) ) {
            cout << "Philosopher: " << phiNum << " is starving" << endl;
            philosState[phiNum] = STARVING;
            pthread_cond_wait(&condVar[phiNum], &mutex);
        }
        philosState[phiNum] = EATING; // philosopher gets the both chopsticks

        pthread_mutex_unlock(&mutex);
    }

    static void ReturnForks(int phiNum) {
        pthread_mutex_lock(&mutex);
        int nextPhi = (phiNum + 1) % PHILOSOPHERS, prevPhi = (phiNum + PHILOSOPHERS - 1) % PHILOSOPHERS;
        philosState[phiNum] = THINKING;

        pthread_cond_signal(&condVar[nextPhi]);
        pthread_cond_signal(&condVar[prevPhi]);

        pthread_mutex_unlock(&mutex);
    }

    static void Initialization() {
        pthread_mutex_init(&mutex, nullptr);
        for (int idx = 0; idx < PHILOSOPHERS; idx ++) {
            pthread_cond_init(&condVar[idx], nullptr);
            philosState[idx] = THINKING;
        }

    }


};

pthread_cond_t Philosopher::condVar[PHILOSOPHERS];
pthread_mutex_t Philosopher::mutex;
Philosopher::STATE Philosopher::philosState[PHILOSOPHERS];

int main() {
    freopen("Izlaz.out", "w", stdout);
    pthread_t tId;
    pthread_attr_t defAtr;

    pthread_attr_init(&defAtr);
    Philosopher::Initialization();

    for (int idx = 0; idx < PHILOSOPHERS; idx ++) {
        pthread_create(&tId, &defAtr, Philosopher::Run, &PhiIdx[idx]);
    }
    pthread_join(tId, nullptr);
    cout << "Everything finished well " << endl;


    return 0;
}
