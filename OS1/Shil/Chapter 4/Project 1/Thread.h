#ifndef _THREAD_H_
#define _THREAD_H_

#include "pthread.h"
#include <map>

using namespace std;

using FunPt = void* (*)(void*);

class Thread {
    static map <Thread*, pthread_t> mapId;
    pthread_t tId;
    FunPt funPt;
    void* arg;
public:
    Thread();
    // starts the Thread
    void Start();

    // wait for thread to finish
    void Join(Thread*);

    // abstract run


};

#endif
