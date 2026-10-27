#include "uzytkownik.h"

Uzytkownik::Uzytkownik(const string& imie, const string& nazwisko, int id)
    : imie_(imie), nazwisko_(nazwisko), id_(id) {}

string Uzytkownik::getImie() const {
    return imie_;
}

string Uzytkownik::getNazwisko() const {
    return nazwisko_;
}