#include "kurs.h"

Kurs::Kurs(const string& tytul, const string& nazwiskoWykladowcy)
    : tytul_(tytul), nazwiskoWykladowcy_(nazwiskoWykladowcy) {}

string Kurs::getTytul() const {
    return tytul_;
}

string Kurs::getNazwiskoWykladowcy() const {
    return nazwiskoWykladowcy_;
}

const vector<Modul>& Kurs::getModuly() const {
    return moduly_;
}

void Kurs::dodajModul(const Modul& m) {
    moduly_.push_back(m);
}