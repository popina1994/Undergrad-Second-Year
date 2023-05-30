#include <iostream>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

constexpr int THREADS = 3;

namespace Sorting {
    enum SortE {FIRST = 0, SECOND, MERGE};
    constexpr int PARTS = 2;
    vector <int> arrayHalf = {3, 1, 3, 5, 6};
    vector <int> sorted;

    void* Sort(void* arg) {
        int part = *( (int*)(arg));
        int len = arrayHalf.size() / 2;

        if (part == 0)
            sort(arrayHalf.begin() + part * len, arrayHalf.begin() + (part + 1) * len);
        else
            sort(arrayHalf.begin() + part * len, arrayHalf.begin() + (part + 1) * len + 1);
    }

    void* Merge(void* arg) {
        // maximum index which indexes can achieve
        static int end[PARTS] = {arrayHalf.size() / 2, arrayHalf.size()};
        // curent index of subarrays
        int begin[PARTS] = {0, arrayHalf.size() / 2};

        for (int cnt = 0; cnt < arrayHalf.size(); cnt ++ ) {
            int curMin = INT_MAX, curIdx = -1;

            for (int idx = 0; idx < sizeof(begin) / sizeof(begin[0]); idx ++)
                if ( (begin[idx] != end[idx]) && (arrayHalf[begin[idx]] <= curMin) ) {
                    curIdx = idx;
                    curMin = arrayHalf[begin[idx]];
                }
            begin[curIdx]++;
            sorted.push_back(curMin);
        }
    }
}

int main(){
    pthread_t tId[THREADS];
    int argList[Sorting::PARTS] = {0, 1};
    pthread_attr_t defAttr;

    pthread_attr_init(&defAttr);



    for (int cnt = 0; cnt <= Sorting::SECOND; cnt ++)
        pthread_create(&tId[cnt], &defAttr, Sorting::Sort, &argList[cnt]);

    for (int cnt = 0; cnt <= Sorting::SECOND; cnt ++)
        pthread_join(tId[cnt], nullptr);

    pthread_create(&tId[Sorting::MERGE], &defAttr, Sorting::Merge, nullptr);
    pthread_join(tId[Sorting::MERGE], nullptr);

    cout << "Sorted array is" << endl;
    for (auto it : Sorting::sorted)
        cout << it  << " ";

    return 0;
}
