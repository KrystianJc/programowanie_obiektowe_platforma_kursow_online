#include "wykladowca.h"

Wykladowca::Wykladowca(const string& imie, const string& nazwisko, int id)
    : Uzytkownik(imie, nazwisko, id) {}

Kurs Wykladowca::utworzKurs(const string& tytul) const {
    return Kurs(tytul, getNazwisko());
}

string Wykladowca::getRola() const {
    return "Wykladowca";
}