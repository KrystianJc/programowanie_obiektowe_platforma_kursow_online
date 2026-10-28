#include "platforma_edukacyjna.h"

#include <ctime>
#include <iostream>

void PlatformaEdukacyjna::wygenerujCertyfikat(const Kursant& k,const Postep& p) const {
    if (p.czyUkonczony()) {
        time_t teraz = time(nullptr);
        tm data = *localtime(&teraz);

        cout << "===== CERTYFIKAT =====" << endl;
        cout << "Kursant: " << k.getImie() << " " << k.getNazwisko() << endl;
        cout << "Kurs: " << p.getKurs().getTytul() << endl;
        cout << "Data wydania: " << data.tm_mday << "." << data.tm_mon + 1
            << "." << data.tm_year + 1900 << endl;
    } else {
        cout << "Certyfikat niedostepny - kurs nie zostal ukonczony" << endl;
    }
}

vector<Kurs> PlatformaEdukacyjna::pokazKursy() const {
    return kursy_;
}

void PlatformaEdukacyjna::dodajKurs(const Kurs& k) {
    kursy_.push_back(k);
}