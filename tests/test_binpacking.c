#include <stdio.h>

#include "../src/binpacking.h"

static int failures = 0;
#define CHECK(cond) do { if (!(cond)) { printf("FEHLER Zeile %d: %s\n", __LINE__, #cond); failures++; } } while (0)

/* Prueft, dass kein Behaelter ueberladen ist und jeder Gegenstand zugeordnet wurde. */
static void check_valid(const int *s, size_t n, int cap, const BpResult *r) {
    int load[BP_MAX_ITEMS] = {0};
    size_t i;
    for (i = 0; i < n; i++) {
        CHECK(r->bin_of_item[i] >= 0 && r->bin_of_item[i] < r->bin_count);
        load[r->bin_of_item[i]] += s[i];
    }
    for (i = 0; i < (size_t)r->bin_count; i++) CHECK(load[i] <= cap);
}

int main(void) {
    const int s[] = {4, 8, 1, 4, 2, 1};
    const int big[] = {11};
    BpResult r;

    CHECK(bp_lower_bound(s, 6, 10) == 2);

    CHECK(bp_first_fit(s, 6, 10, &r) == 0);
    check_valid(s, 6, 10, &r);
    CHECK(r.bin_count == 2);

    CHECK(bp_first_fit_decreasing(s, 6, 10, &r) == 0);
    check_valid(s, 6, 10, &r);
    CHECK(r.bin_count == 2);

    CHECK(bp_best_fit_decreasing(s, 6, 10, &r) == 0);
    check_valid(s, 6, 10, &r);
    CHECK(r.bin_count == 2);

    /* Perfekte Paarung: Untere Schranke (3) wird erreicht */
    {
        const int t[] = {3, 7, 3, 7, 4, 6};
        CHECK(bp_first_fit(t, 6, 10, &r) == 0);
        check_valid(t, 6, 10, &r);
        CHECK(bp_first_fit_decreasing(t, 6, 10, &r) == 0);
        check_valid(t, 6, 10, &r);
        CHECK(r.bin_count == 3);
    }

    /* Ungueltige Eingaben */
    CHECK(bp_first_fit(big, 1, 10, &r) == -1);
    CHECK(bp_first_fit(NULL, 1, 10, &r) == -1);
    CHECK(bp_first_fit(s, 0, 10, &r) == -1);
    CHECK(bp_first_fit(s, 6, 0, &r) == -1);

    if (failures == 0) printf("Alle Tests bestanden.\n");
    return failures ? 1 : 0;
}
