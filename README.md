# Bin Packing: drei Heuristiken in C

Umsetzung der klassischen Heuristiken für das **Bin-Packing-Problem**: Gegenstände mit verschiedenen Größen sollen in möglichst wenige Behälter gleicher Kapazität gepackt werden. Ursprünglich 2013 als Hochschulprojekt entstanden (Windows-Konsole), jetzt als portables C99-Projekt mit Tests neu aufgebaut.

## Verfahren

| Verfahren | Idee |
|---|---|
| First Fit | Jeder Gegenstand kommt in den ersten Behälter, in den er passt |
| First Fit Decreasing | wie First Fit, aber Gegenstände vorher nach Größe absteigend sortiert |
| Best Fit Decreasing | absteigend sortiert, Behälter mit dem kleinsten passenden Restplatz |

Zusätzlich berechnet das Programm die **untere Schranke** (Summe der Größen geteilt durch die Kapazität, aufgerundet), um die Güte der Ergebnisse einzuordnen.

## Verwendung

```bash
make            # baut bin/binpacking
make test       # baut und startet die Tests
./bin/binpacking 10 4 8 1 4 2 1
```

Der erste Parameter ist die Kapazität, die weiteren sind die Größen der Gegenstände (maximal 100). Beispielausgabe:

```
First Fit: 2 Behaelter
  Behaelter 1: 4 1 4 1  (belegt 10 von 10)
  Behaelter 2: 8 2  (belegt 10 von 10)
```

## Aufbau

```
src/binpacking.[ch]   Algorithmen als Bibliothek (ohne Ein- und Ausgabe)
src/main.c            Kommandozeilenprogramm
tests/                Tests (Gültigkeit der Packung, Grenzfälle, ungültige Eingaben)
legacy_windows/       ursprünglicher Code von 2013 (Windows-Konsole, unverändert)
docs/                 Projektbericht (Französisch)
```

## Was gegenüber 2013 besser ist

- Läuft auf Linux, macOS und Windows (kein `windows.h`, kein `gotoxy`)
- Algorithmen sind von der Ausgabe getrennt und testbar
- Eingaben werden geprüft, es gibt keine Zugriffe außerhalb der Arrays
- Der alte Code verwendete eine verkettete Liste von Behältern. Hier genügt ein Array mit Restplatz, das ist kürzer und leichter zu prüfen.

## Grenzen

- Bin Packing ist NP-schwer. Die Heuristiken liefern gute, aber nicht immer optimale Ergebnisse.
- Maximal 100 Gegenstände (feste Arraygröße).

## Autor

Bayrem Trabelsi
