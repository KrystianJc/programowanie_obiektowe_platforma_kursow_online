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
