#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NumOfStatesMax 101

int voterNum[NumOfStatesMax], numStates;

int main() {
    int cnt, cnt1, cnt2, voterNumMin = 0;

    freopen("ulaz.in", "r", stdin);

    scanf("%d", &numStates);

    for (cnt = 0; cnt < numStates; cnt++)
        scanf("%d", &voterNum[cnt]);

    for (cnt1 = 0; cnt1 < numStates - 1; cnt1++)
        for (cnt2 = cnt1 + 1; cnt2 < numStates; cnt2++)
            if (voterNum[cnt1] > voterNum[cnt2]) {
                int tmp = voterNum[cnt1];
                voterNum[cnt1] = voterNum[cnt2];
                voterNum[cnt2] = tmp;
    }

    for (cnt = 0; cnt <= numStates / 2;  cnt++)
        voterNumMin += (voterNum[cnt] + 1) / 2;

    printf("%d", voterNumMin);

    return 0;
}
