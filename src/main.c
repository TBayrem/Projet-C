#include <stdio.h>
#include <stdlib.h>

#include "binpacking.h"

static void print_result(const char *name, const int *sizes, size_t n, int capacity, const BpResult *r) {
    int b;
    size_t i;
    printf("\n%s: %d Behaelter\n", name, r->bin_count);
    for (b = 0; b < r->bin_count; b++) {
        int used = 0;
        printf("  Behaelter %d:", b + 1);
        for (i = 0; i < n; i++) {
            if (r->bin_of_item[i] == b) {
                printf(" %d", sizes[i]);
                used += sizes[i];
            }
        }
        printf("  (belegt %d von %d)\n", used, capacity);
    }
}

int main(int argc, char **argv) {
    int sizes[BP_MAX_ITEMS];
    int capacity, count = 0, i;
    BpResult r;

    if (argc < 3) {
        fprintf(stderr, "Aufruf: %s <Kapazitaet> <Groesse1> <Groesse2> ...\n", argv[0]);
        fprintf(stderr, "Beispiel: %s 10 4 8 1 4 2 1\n", argv[0]);
        return 2;
    }
    capacity = atoi(argv[1]);
    for (i = 2; i < argc && count < BP_MAX_ITEMS; i++) sizes[count++] = atoi(argv[i]);

    printf("Kapazitaet je Behaelter: %d, Gegenstaende: %d\n", capacity, count);
    printf("Untere Schranke: %d Behaelter\n", bp_lower_bound(sizes, (size_t)count, capacity));

    if (bp_first_fit(sizes, (size_t)count, capacity, &r) != 0) {
        fprintf(stderr, "Ungueltige Eingabe: Groessen muessen zwischen 1 und der Kapazitaet liegen.\n");
        return 1;
    }
    print_result("First Fit", sizes, (size_t)count, capacity, &r);
    bp_first_fit_decreasing(sizes, (size_t)count, capacity, &r);
    print_result("First Fit Decreasing", sizes, (size_t)count, capacity, &r);
    bp_best_fit_decreasing(sizes, (size_t)count, capacity, &r);
    print_result("Best Fit Decreasing", sizes, (size_t)count, capacity, &r);
    return 0;
}
