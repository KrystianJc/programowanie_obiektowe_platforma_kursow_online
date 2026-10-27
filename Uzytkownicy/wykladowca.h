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


