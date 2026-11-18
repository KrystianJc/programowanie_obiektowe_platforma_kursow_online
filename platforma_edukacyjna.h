#pragma once

#include <vector>

#include "kurs.h"
#include "postep.h"
#include "Uzytkownicy/kursant.h"

using namespace std;

class PlatformaEdukacyjna {
public:
    void wygenerujCertyfikat(const Kursant& k, const Postep& p) const;
    vector<Kurs> pokazKursy() const;
    void dodajKurs(const Kurs& k);

private:
    vector<Kurs> kursy_;
};
