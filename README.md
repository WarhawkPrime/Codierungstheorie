# Codierungstheorie Praktikumsaufgaben

## Task 1

Schreiben Sie ein Programm, welches die Multiplikationstabellen für Körper GF(2^e) konstruiert.
Die Eingabe des Programms soll das irreduzible Polynom erwarten.
Testen Sie das Programm für die Erweiterungsgrade e = 2, 3, . . . , 8.

Cmake Target Task_1 generiert alle additions und multiplikations Tabellen als CSV-Tabellen.

Für die Darstellung kann das Godot Programm genutzt werden:
[MatrixVisualisation](MultMatrix/README.md)

## Task 2

Der erweiterte euklidische Algorithmus (EEA) für binäre Polynome bietet die Möglichkeit der multiplikativen Inversion in
Erweiterungskörpern.

> Für verschiedene Körpergrade e = 2, 3, . . . , 8 wählen Sie alle
> Körperelemente, invertieren diese mittels EEA und multiplizie-
> ren das Ergebnis mit dem Ausgangselement. Ist das Ergebnis 1,
> so war die Inversion korrekt.

Cmake Target Task_2 gibt für alle GF(2^e) (mit 0 < e < 9) die Elemente und ihre multiplicativen Inversen aus.

Für erweitere Informationen kann beim compelieren VERBOSE true definiert werden, dann werden die einzelen Schritte im
EEA mit ausgegeben.

Zudem werden die Elemente und ihre multiplicativen Inverse im TEST_CASE: "Multiplicative inverse calculation Fuzzy test
in EGF p = 2" getestet.

## Task 3

Schreiben Sie ein Programm zur Behandlung von linearen Codes über einem binären Erweiterungskörper GF(2^e):

1. Implementieren Sie ein Routine, welche bei Eingabe einer Generatormatrix die kanonische Generatormatrix erzeugt.
2. Implementieren Sie eine Routine, welche aus einer kanonischen Generatormatrix eine Kontrollmatrix generiert.
3. Implementieren Sie eine Routine, welche die Syndromtabelle erzeugt.
4. Implementieren Sie eine Routine, welche die Fehlerkorrektur mittels Maximum-Likelihood-Decodierung und Syndromtabelle
   durchführt.

## Task 4

Schreiben Sie ein Programm zur Behandlung von binären Hamming-Codes:

1. Implementieren Sie eine Routine, welche bei Eingabe von m ≥ 3 eine Kontrollmatrix eines binären (2 m − 1, 2m − 1 − m,
   3; 2) Hamming-Codes erzeugt (inkl. der dazugehörigen Generatormatrix).
2. Implementieren Sie die Decodierung für binäre (2m − 1, 2m −1 − m, 3; 2) Hamming-Codes.

## Task 5

Schreiben Sie ein Programm zur rekursiven Konstruktion der Generatormatrix eines Reed-Muller-Codes RM(r, m).

## Task 6

Schreiben Sie eine Programm, welches bei Eingabe der Parameter e und 2 ≤ d ≤ 2 e − 2 eines Reed-Solomon-Codes RS(2^e, d)
konstruiert.
Konkret gehen Sie dabei wie folgt vor:

1. Implementieren Sie eine Routine zur Bestimmung eines primitives Element in GF(2^e).
2. Implementieren Sie eine Routine zur Berechnung des Generatorund Kontrollpolynoms für RS(2^e, d).
3. Implementieren Sie eine Routine zur Berechnung von Generatorund Kontrollmatrix aus Generator- und Kontrollpolynom für
   RS(2^e, d).
4. Implementieren Sie eine Routine zur Berechnung einer weiteren Kontrollmatrix mittels Vandermonde-Matrix.

# HOT LIST (todo)

- [x] Task 1
- [x] Task 2
- [ ] Task 3
- [x] Task 4
- [ ] Task 5
- [ ] Task 6
- [ ] FIXME Still pretty unorganised and duplication of code
- [ ] FIXME: Not enough tests / code coverage
- [ ] FIXME: REMOVE UNNECESSARY FILES

# Usefull websites

- https://mathsci2.appstate.edu/~cookwj/sage/algebra/Euclidean_algorithm-poly.html
- https://www.matheretter.de/rechner/polynomrechner - so lala
- http://www.arndt-bruenner.de/mathe/scripts/gaussjordan.htm
- https://www.di-mgt.com.au/cgi-bin/matrix_canon_form.cgi
- https://www.di-mgt.com.au/cgi-bin/matrix_stdform.cgi
- https://www.partow.net/programming/polynomials/index.html
- http://web.eecs.utk.edu/~jplank/plank/papers/CS-07-593/primitive-polynomial-table.txt
- http://www.ee.unb.ca/cgi-bin/tervo/calc.pl