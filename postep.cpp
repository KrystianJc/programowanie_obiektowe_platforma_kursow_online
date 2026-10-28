#include "postep.h"

Postep::Postep(const Kurs& kurs)
    : ukonczoneModuly_(0), kurs_(kurs) {}

bool Postep::czyUkonczony() const {
    return ukonczoneModuly_ >= static_cast<int>(kurs_.getModuly().size());
}

bool Postep::czyOdblokowany(const Modul& m) const {
    return m.getKolejnosc() <= (ukonczoneModuly_ + 1);
}

int Postep::procentUkonczenia() const {
    int lacznie = static_cast<int>(kurs_.getModuly().size());
    if (lacznie == 0) {
        return 0;
    }
    return (ukonczoneModuly_ * 100) / lacznie;
}

void Postep::ukonczModul() {
    if (ukonczoneModuly_ < static_cast<int>(kurs_.getModuly().size())) {
        ++ukonczoneModuly_;
    }
}

int Postep::getUkonczoneModuly() const {
    return ukonczoneModuly_;
}

const Kurs& Postep::getKurs() const {
    return kurs_;
}