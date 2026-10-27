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

