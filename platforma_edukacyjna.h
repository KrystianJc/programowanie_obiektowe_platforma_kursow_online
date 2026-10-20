//
// Created by pc on 20.10.2026.
//

#ifndef PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_PLATFORMA_EDUKACYJNA_H
#define PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_PLATFORMA_EDUKACYJNA_H
#pragma once

#include <memory>
#include <vector>

#include "kurs.h"
#include "postep.h"
#include "Uzytkownicy/kursant.h"
#include "Uzytkownicy/uzytkownik.h"

using namespace std;

class PlatformaEdukacyjna {
public:
    void wygenerujCertyfikat(const Kursant& k, const Postep& p) const;
    vector<Kurs> pokazKursy() const;
    void dodajKurs(const Kurs& k);

private:
    vector<Kurs> kursy_;
    vector<unique_ptr<Uzytkownik>> uzytkownicy_;
};
#endif //PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_PLATFORMA_EDUKACYJNA_H
