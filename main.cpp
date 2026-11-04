#include <iostream>

#include "platforma_edukacyjna.h"
#include "Uzytkownicy/kursant.h"
#include "Uzytkownicy/uzytkownik.h"
#include "Uzytkownicy/wykladowca.h"

using namespace std;

void wyswietlUzytkownika(const Uzytkownik& u) {
    cout << u.getImie() << " " << u.getNazwisko()
         << " (" << u.getRola() << ")" << endl;
}

string takNie(bool wartosc) {
    return wartosc ? "tak" : "nie";
}

int main() {
    PlatformaEdukacyjna platforma;
    Wykladowca anna("Anna", "Nowak", 1);
    Kursant jan("Jan", "Kowalski", 2);

    cout << "=Uzytkownicy platformy" << endl;
    wyswietlUzytkownika(anna);
    wyswietlUzytkownika(jan);

    // User Story 1
    cout << endl << "User Story 1: Wykladowca tworzy kurs" << endl;
    Kurs kurs = anna.utworzKurs("C++ od podstaw");

    Modul modul1("Wprowadzenie", 1);
    modul1.dodajLekcje(Lekcja("Instalacja kompilatora"));
    Modul modul2("Klasy i obiekty", 2);
    modul2.dodajLekcje(Lekcja("Pierwsza klasa"));
    modul2.dodajLekcje(Lekcja("Konstruktory"));
    Modul modul3("Dziedziczenie", 3);
    modul3.dodajLekcje(Lekcja("Klasa bazowa"));

    kurs.dodajModul(modul1);
    kurs.dodajModul(modul2);
    kurs.dodajModul(modul3);
    platforma.dodajKurs(kurs);

    Kurs kurs2 = anna.utworzKurs("Python dla poczatkujacych");
    kurs2.dodajModul(Modul("Podstawy", 1));
    platforma.dodajKurs(kurs2);

    cout << "Kurs: " << kurs.getTytul() << endl;
    for (const Modul& m : kurs.getModuly()) {
        cout << "  Modul " << m.getKolejnosc() << ": " << m.getTytul()
             << endl;
        for (const Lekcja& l : m.getLekcje()) {
            cout << "    - " << l.getTytul() << endl;
        }
    }

    // User Story 2
    cout << endl << "User Story 2: Lista kursow" << endl;
    vector<Kurs> lista = platforma.pokazKursy();
    for (const Kurs& k : lista) {
        cout << k.getTytul() << " - prowadzacy: "
             << k.getNazwiskoWykladowcy() << endl;
    }

    // User Story 3
    cout << endl << "User Story 3: Zapis na kurs" << endl;
    jan.zapiszSie(lista[0]);
    Postep& postep = jan.getPostep(0);
    cout << jan.getImie() << " zapisal sie na: "
         << postep.getKurs().getTytul() << endl;
    cout << "Modul 1 dostepny: " << takNie(postep.czyOdblokowany(modul1))
         << endl;

    // User Story 4
    cout << endl << "User Story 4: Postep w kursie" << endl;
    cout << "Postep: " << postep.procentUkonczenia() << "%" << endl;
    postep.ukonczModul();
    cout << "Ukonczono modul 1 -> postep: " << postep.procentUkonczenia()
         << "%" << endl;

    // User Story 5
    cout << endl << "User Story 5: Odblokowywanie modulow" << endl;
    cout << "Modul 3 dostepny: " << takNie(postep.czyOdblokowany(modul3))
         << endl;
    postep.ukonczModul();
    cout << "Ukonczono modul 2 -> postep: " << postep.procentUkonczenia()
         << "%" << endl;
    cout << "Modul 3 dostepny: " << takNie(postep.czyOdblokowany(modul3))
         << endl;

    // User Story 6
    cout << endl << "User Story 6: Certyfikat" << endl;
    platforma.wygenerujCertyfikat(jan, postep);
    postep.ukonczModul();
    cout << "Ukonczono modul 3 -> postep: " << postep.procentUkonczenia()
         << "%" << endl;
    platforma.wygenerujCertyfikat(jan, postep);

    return 0;
}