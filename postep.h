#pragma once

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