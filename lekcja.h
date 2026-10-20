#ifndef PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_LEKCJA_H
#define PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_LEKCJA_H
#pragma once

#include <string>

using namespace std;

class Lekcja {
public:
    explicit Lekcja(const string& tytul);

    string getTytul() const;
    void setTytul(const string& tytul);

private:
    string tytul_;
};


#endif //PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_LEKCJA_H