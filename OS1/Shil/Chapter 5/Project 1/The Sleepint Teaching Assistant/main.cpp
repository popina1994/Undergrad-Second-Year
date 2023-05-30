#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

constexpr int STUDENTS = 10, BIG_DATA = 100'000'0, ROW_SIZE = 1, JOBS = 2;
enum State{ CONSULTATION, NOTHING};
constexpr char* work[JOBS] = {"Consulatation with profesor!", "Procastrinating!"};

void DummyWork(int bigIdx, State s) {
    for (int idx = 0; idx < BIG_DATA; idx ++);
        cout << "Student " << bigIdx << " is " << work[s] << endl;
}

class BoundedChair {
    static int x[ROW_SIZE], begin, end, size;
    static pthread_mutex_t mutex;

    friend class Student;
    friend class Profesor;
    // spaceAvailable shows how much chairs are free for students to sit
    static sem_t spaceAvailable, itemAvailable;
public:
    static void Initialization() {
        pthread_mutex_init(&mutex, nullptr);
        sem_init(&spaceAvailable, 0, ROW_SIZE);
        sem_init(&itemAvailable, 0, 0);
    }

    static bool Sit(int& student) {
        pthread_mutex_lock(&mutex);
        cout << "Student " << student << " has tried and size is" << size << endl;
        if (size == ROW_SIZE) {

            pthread_mutex_unlock(&mutex);
            return false;

        }

        size++;
        x[(end + 1) % ROW_SIZE] = student;
        end = (end + 1) % ROW_SIZE;
        // inform Profesor about student
        sem_post(&itemAvailable);
        pthread_mutex_unlock(&mutex);
        return true;
        // student can sit on chair
    }

    // returns -1 when there is no students in waiting room
    static int Pull() {
        pthread_mutex_lock(&mutex);
        if (size == 0) {
            pthread_mutex_unlock(&mutex);
            return -1;
        }

        size --;
        int student = x[begin];
        begin = (begin + 1) % ROW_SIZE;
        pthread_mutex_unlock(&mutex);
        return student;
    }
};

pthread_mutex_t BoundedChair::mutex;
sem_t BoundedChair::spaceAvailable, BoundedChair::itemAvailable;
int BoundedChair::begin = 0, BoundedChair::end = 0, BoundedChair::size = 0, BoundedChair::x[ROW_SIZE];

class Profesor {
    friend class Student;
     static pthread_mutex_t mutex;
public:

    static void* Run(void* arg);
};

class Student {
    friend class Profesor;
    static sem_t semStudent[STUDENTS];

public:
    static void Initialize() {
        for (int idx = 0; idx < STUDENTS; idx ++)
            sem_init(&semStudent[idx], 0, 0);
    }

    static void* Run(void* arg) {
        int idx = *( (int*)(arg) );

        while (true) {
            while (!BoundedChair::Sit(idx) ) DummyWork(idx, NOTHING); // busy waiting

            pthread_mutex_lock(&Profesor::mutex);
            DummyWork(idx, CONSULTATION);
            pthread_mutex_unlock(&Profesor::mutex);

            sem_post(&semStudent[idx]);
        }
        pthread_exit(nullptr);
    }
};

sem_t Student::semStudent[STUDENTS];



void* Profesor::Run(void* arg) {
    cout << "Enter" << endl;
    while (true) {
        int student;
        while ( (student = BoundedChair::Pull()) == -1)
            sem_wait(&BoundedChair::itemAvailable);
        sem_wait(&Student::semStudent[student]);
    }
}

 pthread_mutex_t Profesor::mutex;

int x[STUDENTS];

constexpr void Init() {
    for (int idx = 0 ; idx < STUDENTS; idx ++)
        x[idx] = idx;
}
int main() {

    freopen("Output.out", "w", stdout);
    pthread_t tId, pId;
    pthread_attr_t defAtr;

    pthread_attr_init(&defAtr);
    BoundedChair::Initialization();
    Student::Initialize();
    Init();


    pthread_create(&pId, &defAtr, &Profesor::Run, nullptr);
    for (int idx = 0; idx < STUDENTS; idx ++) {
        pthread_create(&tId, &defAtr, Student::Run, &x[idx]);
        cout << "idx created" << endl;
    }
    pthread_join(pId, nullptr);

    return 0;
}
