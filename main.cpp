#include <iostream>
#include <limits>
#include <string>

#include "platforma_edukacyjna.h"
#include "Uzytkownicy/kursant.h"
#include "Uzytkownicy/wykladowca.h"

using namespace std;

int wczytajLiczbe(const string& komunikat, int minimum, int maksimum) {
    int liczba;

    while (true) {
        cout << komunikat;
        if (cin >> liczba && liczba >= minimum && liczba <= maksimum) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return liczba;
        }

        cout << "Podaj liczbe od " << minimum << " do " << maksimum << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string wczytajTekst(const string& komunikat) {
    string tekst;
    cout << komunikat;
    getline(cin, tekst);

    while (tekst.empty()) {
        cout << "Tekst nie moze byc pusty. Sprobuj ponownie.\n";
        cout << komunikat;
        getline(cin, tekst);
    }

    return tekst;
}

void wyswietlKursy(const PlatformaEdukacyjna& platforma) {
    vector<Kurs> kursy = platforma.pokazKursy();

    if (kursy.empty()) {
        cout << "Brak kursow na platformie.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(kursy.size()); ++i) {
        cout << i + 1 << ". " << kursy[i].getTytul()
             << " - wykladowca: " << kursy[i].getNazwiskoWykladowcy()
             << '\n';
    }
}

void wyswietlSzczegolyKursu(const Kurs& kurs) {
    cout << "\nKurs: " << kurs.getTytul() << '\n';

    for (const Modul& modul : kurs.getModuly()) {
        cout << "  Modul " << modul.getKolejnosc() << ": "
             << modul.getTytul() << '\n';

        for (const Lekcja& lekcja : modul.getLekcje()) {
            cout << "    - " << lekcja.getTytul() << '\n';
        }
    }
}

void utworzKurs(PlatformaEdukacyjna& platforma,
                const Wykladowca& wykladowca) {
    string tytul = wczytajTekst("Podaj tytul kursu: ");
    Kurs kurs = wykladowca.utworzKurs(tytul);
    int liczbaModulow = wczytajLiczbe("Ile modulow ma miec kurs? ", 1, 20);

    for (int numerModulu = 1; numerModulu <= liczbaModulow; ++numerModulu) {
        string tytulModulu = wczytajTekst(
            "Podaj tytul modulu " + to_string(numerModulu) + ": ");
        Modul modul(tytulModulu, numerModulu);
        int liczbaLekcji = wczytajLiczbe("Ile lekcji ma modul? ", 1, 20);

        for (int numerLekcji = 1; numerLekcji <= liczbaLekcji; ++numerLekcji) {
            string tytulLekcji = wczytajTekst(
                "Podaj tytul lekcji " + to_string(numerLekcji) + ": ");
            modul.dodajLekcje(Lekcja(tytulLekcji));
        }

        kurs.dodajModul(modul);
    }

    platforma.dodajKurs(kurs);
    cout << "Kurs zostal utworzony.\n";
    wyswietlSzczegolyKursu(kurs);
}

int wybierzPostep(Kursant& kursant) {
    if (kursant.getLiczbaPostepow() == 0) {
        cout << "Nie jestes zapisany na zaden kurs.\n";
        return -1;
    }

    cout << "Twoje kursy:\n";
    for (int i = 0; i < kursant.getLiczbaPostepow(); ++i) {
        Postep& postep = kursant.getPostep(i);
        cout << i + 1 << ". " << postep.getKurs().getTytul()
             << " (" << postep.procentUkonczenia() << "%)\n";
    }

    return wczytajLiczbe("Wybierz kurs: ", 1, kursant.getLiczbaPostepow()) - 1;
}

void obsluzKursanta(PlatformaEdukacyjna& platforma, Kursant& kursant) {
    int wybor;

    do {
        cout << "\n--- Menu kursanta ---\n"
             << "1. Pokaz dostepne kursy\n"
             << "2. Zapisz sie na kurs\n"
             << "3. Pokaz postep i dostepne moduly\n"
             << "4. Ukoncz kolejny modul\n"
             << "5. Wygeneruj certyfikat\n"
             << "0. Powrot\n";
        wybor = wczytajLiczbe("Wybierz opcje: ", 0, 5);

        if (wybor == 1) {
            wyswietlKursy(platforma);
        } else if (wybor == 2) {
            vector<Kurs> kursy = platforma.pokazKursy();
            wyswietlKursy(platforma);
            if (!kursy.empty()) {
                int numer = wczytajLiczbe(
                    "Wybierz kurs do zapisania: ", 1,
                    static_cast<int>(kursy.size()));
                kursant.zapiszSie(kursy[numer - 1]);
                cout << "Zapisano na kurs: " << kursy[numer - 1].getTytul()
                     << '\n';
            }
        } else if (wybor == 3) {
            int indeks = wybierzPostep(kursant);
            if (indeks >= 0) {
                Postep& postep = kursant.getPostep(indeks);
                cout << "Postep: " << postep.procentUkonczenia() << "%\n";
                for (const Modul& modul : postep.getKurs().getModuly()) {
                    cout << "Modul " << modul.getKolejnosc() << " ("
                     << modul.getTytul() << ") - "
                     << (postep.czyOdblokowany(modul)
                             ? "dostepny" : "zablokowany") << '\n';
                }
            }
        } else if (wybor == 4) {
            int indeks = wybierzPostep(kursant);
            if (indeks >= 0) {
                Postep& postep = kursant.getPostep(indeks);
                postep.ukonczModul();
                cout << "Ukonczono modul. Ukonczone moduly: "
                 << postep.getUkonczoneModuly() << ". Nowy postep: "
                 << postep.procentUkonczenia() << "%\n";
            }
        } else if (wybor == 5) {
            int indeks = wybierzPostep(kursant);
            if (indeks >= 0) {
                platforma.wygenerujCertyfikat(
                    kursant, kursant.getPostep(indeks));
            }
        }
    } while (wybor != 0);
}

void dodajKursyBazowe(PlatformaEdukacyjna& platforma,
                      const Wykladowca& wykladowca) {
    Kurs podstawyCpp = wykladowca.utworzKurs("C++ od podstaw");
    Modul cppWprowadzenie("Wprowadzenie do C++", 1);
    cppWprowadzenie.dodajLekcje(Lekcja("Instalacja kompilatora"));
    cppWprowadzenie.dodajLekcje(Lekcja("Pierwszy program"));
    podstawyCpp.dodajModul(cppWprowadzenie);

    Modul cppObiekty("Klasy i obiekty", 2);
    cppObiekty.dodajLekcje(Lekcja("Tworzenie klasy"));
    cppObiekty.dodajLekcje(Lekcja("Konstruktory"));
    podstawyCpp.dodajModul(cppObiekty);
    platforma.dodajKurs(podstawyCpp);

    Kurs podstawyPython = wykladowca.utworzKurs("Python dla poczatkujacych");
    Modul pythonWprowadzenie("Podstawy jezyka", 1);
    pythonWprowadzenie.dodajLekcje(Lekcja("Zmienne i typy danych"));
    pythonWprowadzenie.dodajLekcje(Lekcja("Instrukcje warunkowe"));
    podstawyPython.dodajModul(pythonWprowadzenie);

    Modul pythonKolekcje("Kolekcje danych", 2);
    pythonKolekcje.dodajLekcje(Lekcja("Listy"));
    pythonKolekcje.dodajLekcje(Lekcja("Slowniki"));
    podstawyPython.dodajModul(pythonKolekcje);
    platforma.dodajKurs(podstawyPython);
}

int main() {
    PlatformaEdukacyjna platforma;
    Wykladowca wykladowca("Anna", "Nowak", 1);
    Kursant kursant("Jan", "Kowalski", 2);
    int wybor;

    dodajKursyBazowe(platforma, wykladowca);

    cout << "Platforma Kursow Online\n";
    cout << "Zalogowano jako: " << wykladowca.getImie() << " "
         << wykladowca.getNazwisko() << " i " << kursant.getImie() << " "
         << kursant.getNazwisko() << "\n";

    do {
        cout << "\n--- Menu glowne ---\n"
             << "1. Panel wykladowcy\n"
             << "2. Panel kursanta\n"
             << "3. Pokaz wszystkie kursy\n"
             << "0. Zakoncz program\n";
        wybor = wczytajLiczbe("Wybierz opcje: ", 0, 3);

        if (wybor == 1) {
            utworzKurs(platforma, wykladowca);
        } else if (wybor == 2) {
            obsluzKursanta(platforma, kursant);
        } else if (wybor == 3) {
            wyswietlKursy(platforma);
        }
    } while (wybor != 0);

    cout << "Dziekujemy za skorzystanie z platformy.\n";
    return 0;
}
