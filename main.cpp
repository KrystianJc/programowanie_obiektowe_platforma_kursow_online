#include <iostream>
#include "platforma_edukacyjna.h"
#include "Uzytkownicy/kursant.h"
#include "Uzytkownicy/wykladowca.h"
using namespace std;

void wyswietlUzytkownika(const Uzytkownik& u) {
    cout << u.getImie() << " " << u.getNazwisko()
         << " (" << u.getRola() << ")" << endl;
}

int main() {
    PlatformaEdukacyjna platforma;
    Wykladowca anna("Anna", "Nowak", 1);
    Kursant jan("Jan", "Kowalski", 2);

    cout << "Użytkownicy platformy edukacyjnej" << endl;
    wyswietlUzytkownika(anna);
    wyswietlUzytkownika(jan);

    cout << "Dodawanie kursów" << endl;
    Kurs kurs = anna.utworzKurs("C++ od podstaw");
    platforma.dodajKurs(kurs);
    cout << "Kurs dodany na platforme" << endl;

    cout << "Przeglądanie kursów" << endl;
    vector<Kurs> lista = platforma.pokazKursy();
    cout << "Liczba dostepnych kursow: " << lista.size() << endl;

    cout << "Zapisywanie się na kursy" << endl;
    jan.zapiszSie(lista[0]);
    cout << jan.getImie() << " zapisal sie na kurs" << endl;

    return 0;
}