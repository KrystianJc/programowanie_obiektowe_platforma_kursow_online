#ifndef PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_KURS_H
#define PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_KURS_H
#pragma once

#include <string>
#include <vector>
#include "modul.h"

using namespace std;

class Kurs {
public:
    Kurs(const string& tytul, const string& nazwiskoWykladowcy);

    string getTytul() const;
    string getNazwiskoWykladowcy() const;
    const vector<Modul>& getModuly() const;

    void dodajModul(const Modul& m);

private:
    string tytul_;
    vector<Modul> moduly_;
    string nazwiskoWykladowcy_;
};


#endif //PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_KURS_H