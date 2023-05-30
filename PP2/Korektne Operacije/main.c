#include <stdio.h>
#include <stdlib.h>

int main() {
    int duz, cnt, relCnt = 0, binOp = 1;
    char c;

    freopen("ulaz4.in", "r", stdin);

    scanf("%d\n", &duz);



    for (cnt = 0; cnt < duz; cnt++) {
        scanf("%c", &c);
        if ( (c == '<' || c == '>' || c == '=') && binOp) {
                relCnt++;
                binOp = 0;
        }
        else
        if ( ( (c == '<' || c == '>' || c == '=') && !binOp) ||
            (c == '+' || c == '-' || c == '*' || c == '/')) binOp = 1;
    }
    // uspelo da me prevari, svaka cast, ali stvarno svaka cast
    printf("%d", relCnt);
    return 0;
}
