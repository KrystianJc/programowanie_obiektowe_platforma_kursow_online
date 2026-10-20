#ifndef PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_WYKLADOWCA_H
#define PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_WYKLADOWCA_H


#pragma once

#include <string>

#include "uzytkownik.h"
#include "../kurs.h"

using namespace std;

class Wykladowca : public Uzytkownik {
public:
    Wykladowca(const string& imie, const string& nazwisko, int id);

    Kurs utworzKurs(const string& tytul) const;
    string getRola() const override;
};


#endif //PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_WYKLADOWCA_H
