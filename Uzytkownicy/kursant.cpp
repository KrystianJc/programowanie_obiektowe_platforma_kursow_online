#include "kursant.h"

Kursant::Kursant(const string& imie, const string& nazwisko, int id)
    : Uzytkownik(imie, nazwisko, id) {}

void Kursant::zapiszSie(const Kurs& kurs) {
    postepy_.push_back(Postep(kurs));
}

Postep& Kursant::getPostep(int indeks) {
    return postepy_.at(indeks);
}

int Kursant::getLiczbaPostepow() const {
    return static_cast<int>(postepy_.size());
}

string Kursant::getRola() const {
    return "Kursant";
}