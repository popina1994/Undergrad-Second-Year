#include <stdio.h>
#include <stdlib.h>
#define NumFarmerMax 5000

const int MilkQuantMax = 2e6, PriceMax = 1e3, MilkDayMax = 2e6;

int price[NumFarmerMax], milkDay[NumFarmerMax];

int main() {
    int cnt, numFarmer, cnt1, cnt2, milkQuant, totalPrice = 0;

    freopen("ulaz.in", "r", stdin);

    scanf("%d%d", &milkQuant, &numFarmer);

    for (cnt = 0; cnt < numFarmer; cnt++)
        scanf("%d%d", &price[cnt], &milkDay[cnt]);

    for (cnt1 = 0; cnt1 < numFarmer - 1; cnt1++)
        for (cnt2 = cnt1 + 1; cnt2 < numFarmer; cnt2++)
            if (price[cnt1] > price[cnt2]) {
                int tmpPrice = price[cnt2], tmpMilkDay = milkDay[cnt2];
                price[cnt2] = price[cnt1]; milkDay[cnt2] = milkDay[cnt1];
                price[cnt1] = tmpPrice; milkDay[cnt1] = tmpMilkDay;
            }
            // neki shit sort

    for (cnt = 0; milkQuant > 0; cnt++)
        if (milkQuant - milkDay[cnt] < 0) {
            totalPrice += price[cnt] * milkQuant;
            milkQuant = 0;
        }
        else {
            milkQuant -= milkDay[cnt];
            totalPrice += price[cnt] * milkDay[cnt];
        }

    printf("%d", totalPrice);
    return 0;
}
