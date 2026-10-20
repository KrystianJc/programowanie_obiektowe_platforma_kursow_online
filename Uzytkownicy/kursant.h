#ifndef PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_KURSANT_H
#define PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_KURSANT_H
#pragma once

#include <string>
#include <vector>

#include "uzytkownik.h"
#include "../kurs.h"
#include "../postep.h"

using namespace std;

class Kursant : public Uzytkownik {
public:
    Kursant(const string& imie, const string& nazwisko, int id);

    void zapiszSie(const Kurs& kurs);
    Postep& getPostep(int indeks);
    string getRola() const override;

private:
    vector<Postep> postepy_;
};


#endif //PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_KURSANT_H
