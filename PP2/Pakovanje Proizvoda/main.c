#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NumLetter 26

const int BagSizeMax = 1000, ProductByeMax = 5e5;

int letter[NumLetter];

int main() {
    int cnt, bagSize, productBye, solBag = 0;

    //freopen("ulaz.in", "r", stdin);

    scanf("%d%d\n", &bagSize, &productBye);

    memset(letter, 0, sizeof(letter));
    for (cnt = 0; cnt < productBye; cnt++) {
        char c;
        scanf("%c", &c);
        letter[c - 'A'] ++;
    }

    for (cnt = 0; cnt < NumLetter; cnt++)
        solBag += (letter[cnt] + bagSize - 1) / bagSize;

    printf("%d", solBag);

    return 0;
}
