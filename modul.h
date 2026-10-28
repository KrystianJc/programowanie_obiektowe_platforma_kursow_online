#pragma once

#include <string>
#include <vector>
#include "lekcja.h"

using namespace std;

class Modul {
public:
    Modul(const string& tytul, int kolejnosc);

    string getTytul() const;
    int getKolejnosc() const;
    const vector<Lekcja>& getLekcje() const;

    void dodajLekcje(const Lekcja& l);

private:
    string tytul_;
    int kolejnosc_;
    vector<Lekcja> lekcje_;
};
