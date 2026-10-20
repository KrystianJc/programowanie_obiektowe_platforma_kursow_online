#ifndef PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_POSTEP_H
#define PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_POSTEP_H
#pragma once

#include <string>
#include "kurs.h"
#include "modul.h"
using namespace std;



class Postep {
    public:
        explicit Postep(const Kurs& kurs);

        bool czyUkonczony() const;
        bool czyOdblokowany(const Modul& m) const;
        int procentUkonczenia() const;
        void ukonczModul();

        int getUkonczoneModuly() const;
        const Kurs& getKurs() const;

    private:
        int ukonczoneModuly_;
        Kurs kurs_;
};


#endif //PROGRAMOWANIE_OBIEKTOWE_PLATFORMA_KURSOW_ONLINE_POSTEP_H