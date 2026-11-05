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
    int getLiczbaPostepow() const;
    string getRola() const override;

private:
    vector<Postep> postepy_;
};
