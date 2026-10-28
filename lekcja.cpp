#include "lekcja.h"

Lekcja::Lekcja(const string& tytul)
    : tytul_(tytul) {}

string Lekcja::getTytul() const {
    return tytul_;
}

void Lekcja::setTytul(const string& tytul) {
    tytul_ = tytul;
}