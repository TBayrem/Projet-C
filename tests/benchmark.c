/* Vergleich der drei Heuristiken auf Zufallsinstanzen (feste Startwerte, wiederholbar). */
#include <stdio.h>
#include <stdlib.h>

#include "../src/binpacking.h"

int main(void) {
    const int cap = 100, instances = 1000;
    const size_t n = 50;
    long ff = 0, ffd = 0, bfd = 0, lb = 0;
    int ffd_better = 0, ff_better = 0, i;
    size_t k;
    int sizes[BP_MAX_ITEMS];
    BpResult r;

    srand(42);
    for (i = 0; i < instances; i++) {
        int a, b, c;
        for (k = 0; k < n; k++) sizes[k] = 10 + rand() % 51; /* 10..60 */
        bp_first_fit(sizes, n, cap, &r); a = r.bin_count;
        bp_first_fit_decreasing(sizes, n, cap, &r); b = r.bin_count;
        bp_best_fit_decreasing(sizes, n, cap, &r); c = r.bin_count;
        ff += a; ffd += b; bfd += c; lb += bp_lower_bound(sizes, n, cap);
        if (b < a) ffd_better++;
        if (a < b) ff_better++;
    }
    printf("Instanzen: %d, Gegenstaende je Instanz: %zu, Kapazitaet: %d, Groessen 10..60\n", instances, n, cap);
    printf("Mittelwert Behaelter:  Untere Schranke %.2f | First Fit %.2f | First Fit Decreasing %.2f | Best Fit Decreasing %.2f\n",
           (double)lb / instances, (double)ff / instances, (double)ffd / instances, (double)bfd / instances);
    printf("FFD besser als FF: %d Instanzen, FF besser als FFD: %d Instanzen\n", ffd_better, ff_better);
    return 0;
}
