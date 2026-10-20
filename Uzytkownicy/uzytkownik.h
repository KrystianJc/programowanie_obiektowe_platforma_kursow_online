#ifndef PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_UZYTKOWNIK_H
#define PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_UZYTKOWNIK_H
#pragma once

#include <string>

using namespace std;

class Uzytkownik {
public:
    Uzytkownik(const string& imie, const string& nazwisko, int id);
    virtual ~Uzytkownik() = default;

    string getImie() const;
    string getNazwisko() const;

    virtual string getRola() const = 0;

private:
    string imie_;
    string nazwisko_;
    int id_;
};


#endif //PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_UZYTKOWNIK_H
