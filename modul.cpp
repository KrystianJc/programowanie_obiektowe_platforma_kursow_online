#include "modul.h"

Modul::Modul(const string& tytul, int kolejnosc)
    : tytul_(tytul), kolejnosc_(kolejnosc) {}

string Modul::getTytul() const {
    return tytul_;
}

int Modul::getKolejnosc() const {
    return kolejnosc_;
}

const vector<Lekcja>& Modul::getLekcje() const {
    return lekcje_;
}

void Modul::dodajLekcje(const Lekcja& l) {
    lekcje_.push_back(l);
}