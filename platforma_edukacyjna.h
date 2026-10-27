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
