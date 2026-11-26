#include "binpacking.h"

#include <stdlib.h>
#include <string.h>

static int valid(const int *sizes, size_t n, int capacity, const BpResult *out) {
    size_t i;
    if (!sizes || !out || n == 0 || n > BP_MAX_ITEMS || capacity <= 0) return 0;
    for (i = 0; i < n; i++) {
        if (sizes[i] <= 0 || sizes[i] > capacity) return 0;
    }
    return 1;
}

/* Sortiert Indizes absteigend nach Groesse (stabil durch Index als Zweitkriterium). */
static const int *g_sizes;
static int cmp_desc(const void *a, const void *b) {
    int ia = *(const int *)a, ib = *(const int *)b;
    if (g_sizes[ia] != g_sizes[ib]) return g_sizes[ib] - g_sizes[ia];
    return ia - ib;
}

static int pack(const int *sizes, size_t n, int capacity, BpResult *out, int sorted, int best) {
    int order[BP_MAX_ITEMS];
    int free_space[BP_MAX_ITEMS];
    size_t i;
    int b;

    if (!valid(sizes, n, capacity, out)) return -1;
    for (i = 0; i < n; i++) order[i] = (int)i;
    if (sorted) {
        g_sizes = sizes;
        qsort(order, n, sizeof(int), cmp_desc);
    }
    memset(out, 0, sizeof(*out));

    for (i = 0; i < n; i++) {
        int item = order[i];
        int chosen = -1;
        for (b = 0; b < out->bin_count; b++) {
            if (free_space[b] < sizes[item]) continue;
            if (!best) { chosen = b; break; }
            if (chosen < 0 || free_space[b] < free_space[chosen]) chosen = b;
        }
        if (chosen < 0) {
            chosen = out->bin_count++;
            free_space[chosen] = capacity;
        }
        free_space[chosen] -= sizes[item];
        out->bin_of_item[item] = chosen;
    }
    return 0;
}

int bp_first_fit(const int *sizes, size_t n, int capacity, BpResult *out) {
    return pack(sizes, n, capacity, out, 0, 0);
}

int bp_first_fit_decreasing(const int *sizes, size_t n, int capacity, BpResult *out) {
    return pack(sizes, n, capacity, out, 1, 0);
}

int bp_best_fit_decreasing(const int *sizes, size_t n, int capacity, BpResult *out) {
    return pack(sizes, n, capacity, out, 1, 1);
}

int bp_lower_bound(const int *sizes, size_t n, int capacity) {
    long sum = 0;
    size_t i;
    if (!sizes || capacity <= 0) return -1;
    for (i = 0; i < n; i++) sum += sizes[i];
    return (int)((sum + capacity - 1) / capacity);
}
