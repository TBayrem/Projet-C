# Bin Packing in C: Wie viel bringt Sortieren?

*Von Bayrem Trabelsi. Hochschulprojekt von 2013, 2026 als portables C99-Projekt neu aufgebaut. Quellcode: [Projet-C](https://github.com/TBayrem/Projet-C).*

---

## Das Problem

Beim **Bin-Packing-Problem** sollen Gegenstände mit verschiedenen Größen in möglichst wenige Behälter mit fester Kapazität gepackt werden. Es taucht überall auf, wo Ressourcen verteilt werden: Speicher, Ladeflächen, Aufgaben auf Maschinen. Das Problem ist NP-schwer, deshalb nutzt man Heuristiken. Die Analyse von First Fit und First Fit Decreasing geht auf [1] zurück, einen Überblick gibt [2].

## Drei Heuristiken

| Verfahren | Idee |
|---|---|
| First Fit (FF) | Jeder Gegenstand kommt in den ersten Behälter, in den er passt |
| First Fit Decreasing (FFD) | wie FF, aber die Gegenstände werden vorher nach Größe absteigend sortiert |
| Best Fit Decreasing (BFD) | absteigend sortiert, gewählt wird der Behälter mit dem kleinsten Restplatz, in den der Gegenstand noch passt |

Als Maßstab dient die **untere Schranke**: die aufgerundete Summe aller Größen geteilt durch die Kapazität. Weniger Behälter als diese Schranke sind nicht möglich.

## Die Neufassung

Der Code von 2013 war eine Windows-Konsolenanwendung mit `windows.h`, farbiger Ausgabe, Cursor-Positionierung und einer verketteten Liste von Behältern. Die Neufassung trennt Algorithmen und Ausgabe:

- `src/binpacking.c` enthält die Algorithmen als kleine Bibliothek, mit einem Array für den Restplatz statt einer Liste
- `src/main.c` ist das Kommandozeilenprogramm (`./bin/binpacking 10 4 8 1 4 2 1`)
- `tests/` prüft, dass kein Behälter überladen ist, jeder Gegenstand zugeordnet wurde und ungültige Eingaben abgelehnt werden
- ein `Makefile` baut alles (`make test`, `make bench`), auf Linux, macOS und Windows

## Ein Vergleich auf 1.000 Zufallsinstanzen

Ich habe die drei Verfahren auf 1.000 zufällig erzeugten Instanzen verglichen: 50 Gegenstände je Instanz, Größen gleichverteilt von 10 bis 60, Kapazität 100, fester Zufallsstartwert (`make bench` wiederholt das Ergebnis).

| Verfahren | Ø Behälter |
|---|---|
| Untere Schranke | 18,00 |
| First Fit | 19,11 |
| First Fit Decreasing | 18,34 |
| Best Fit Decreasing | 18,34 |

**Befunde:**
- Sortieren vor dem Packen spart im Mittel etwa **0,8 Behälter** je Instanz.
- FFD war in **691 von 1.000 Instanzen besser** als FF und in keiner Instanz schlechter.
- FFD und BFD liefern bei dieser Instanzart im Mittel dasselbe Ergebnis.
- Beide sortierten Verfahren liegen im Mittel nur etwa **0,34 Behälter über der unteren Schranke**.

## Grenzen

- Der Vergleich nutzt **eine Instanzart** (gleichverteilte Größen). Andere Verteilungen können andere Ergebnisse liefern.
- Das Programm verarbeitet **höchstens 100 Gegenstände** (feste Arraygröße).
- Heuristiken liefern **keine Optimallösung**. Die untere Schranke zeigt nur, wie weit sie höchstens daneben liegen.

## Was ich mitnehme

1. **Einfache Vorverarbeitung wirkt.** Das Sortieren kostet fast nichts und spart messbar Behälter.
2. **Algorithmen von der Ausgabe trennen.** Erst dadurch lassen sie sich testen und vergleichen.
3. **Viele Instanzen schlagen ein Beispiel.** Aus einem einzelnen Beispiel hätte ich nicht gesehen, dass FF nie besser war als FFD.

## Quellen

1. Johnson, D. S. (1974): Fast algorithms for bin packing. Journal of Computer and System Sciences 8(3), S. 272–314. https://doi.org/10.1016/S0022-0000(74)80026-7
2. Coffman, E. G., Garey, M. R., Johnson, D. S. (1997): Approximation algorithms for bin packing: a survey. In: Hochbaum, D. S. (Hrsg.): Approximation Algorithms for NP-Hard Problems. Boston: PWS, S. 46–93.

*Hinweis: Preise, Herstellerangaben und Aussagen zu Produkten geben den Stand der jeweiligen Studienarbeit wieder. Alle Links wurden zuletzt im November 2026 gesucht oder abgerufen; Quellen mit dem Vermerk "wie in der Studienarbeit zitiert" sind dort im Literaturverzeichnis nachzuschlagen.*

---

*Ich suche zum 01.03.2027 den Einstieg als Junior IT Consultant oder IT Business Analyst. [LinkedIn](https://linkedin.com/in/bayremtrabelsi) · [GitHub](https://github.com/TBayrem)*