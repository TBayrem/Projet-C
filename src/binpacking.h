#ifndef BINPACKING_H
#define BINPACKING_H

#include <stddef.h>

#define BP_MAX_ITEMS 100

/* Ergebnis einer Packung: Fuer jeden Gegenstand der Index des Behaelters. */
typedef struct {
    int bin_of_item[BP_MAX_ITEMS]; /* Behaelter-Nummer je Gegenstand (ab 0) */
    int bin_count;                 /* Anzahl der benutzten Behaelter */
} BpResult;

/* Gemeinsamer Rueckgabecode: 0 = Erfolg, -1 = ungueltige Eingabe. */

/* First Fit: Jeder Gegenstand kommt in den ersten Behaelter, in den er passt. */
int bp_first_fit(const int *sizes, size_t n, int capacity, BpResult *out);

/* First Fit Decreasing: wie First Fit, aber nach Groesse absteigend sortiert. */
int bp_first_fit_decreasing(const int *sizes, size_t n, int capacity, BpResult *out);

/* Best Fit Decreasing: absteigend sortiert, Behaelter mit dem kleinsten Restplatz. */
int bp_best_fit_decreasing(const int *sizes, size_t n, int capacity, BpResult *out);

/* Untere Schranke: aufgerundete Summe der Groessen geteilt durch die Kapazitaet. */
int bp_lower_bound(const int *sizes, size_t n, int capacity);

#endif
