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

bool czekajNaEnter() {
    cout << "[Enter - dalej, 0 - powrot] ";
    string linia;
    getline(cin, linia);
    return linia != "0";
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
    string tytul = wczytajTekst("Podaj tytul kursu (0 - powrot): ");
    if (tytul == "0") {
        return;
    }
    Kurs kurs = wykladowca.utworzKurs(tytul);
    int liczbaModulow = wczytajLiczbe(
        "Ile modulow ma miec kurs? (0 - powrot) ", 0, 20);
    if (liczbaModulow == 0) {
        cout << "Anulowano tworzenie kursu.\n";
        return;
    }

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

    cout << "0. Powrot\n";

    return wczytajLiczbe("Wybierz kurs: ", 0, kursant.getLiczbaPostepow()) - 1;
}

void przejdzKolejnyModul(Postep& postep) {
    if (postep.czyUkonczony()) {
        cout << "Wszystkie moduly tego kursu sa juz ukonczone.\n";
        return;
    }

    int numer = postep.getUkonczoneModuly() + 1;
    for (const Modul& modul : postep.getKurs().getModuly()) {
        if (modul.getKolejnosc() == numer) {
            cout << "\nModul " << numer << ": " << modul.getTytul() << '\n';
            const vector<Lekcja>& lekcje = modul.getLekcje();

            for (int i = 0; i < static_cast<int>(lekcje.size()); ++i) {
                cout << "Lekcja " << i + 1 << "/" << lekcje.size() << ": "
                     << lekcje[i].getTytul() << '\n';
                if (!czekajNaEnter()) {
                    cout << "Przerwano. Modul nie zostal ukonczony.\n";
                    return;
                }
            }

            postep.ukonczModul();
            cout << "Ukonczono modul " << numer << ". Nowy postep: "
                 << postep.procentUkonczenia() << "%\n";
            return;
        }
    }
}

void obsluzKursanta(PlatformaEdukacyjna& platforma, Kursant& kursant) {
    int wybor;

    do {
        cout << "\n--- Menu kursanta ---\n"
             << "1. Pokaz dostepne kursy\n"
             << "2. Zapisz sie na kurs\n"
             << "3. Pokaz postep i dostepne moduly\n"
             << "4. Przejdz kolejny modul\n"
             << "5. Wygeneruj certyfikat\n"
             << "0. Powrot\n";
        wybor = wczytajLiczbe("Wybierz opcje: ", 0, 5);

        if (wybor == 1) {
            wyswietlKursy(platforma);
        } else if (wybor == 2) {
            vector<Kurs> kursy = platforma.pokazKursy();
            wyswietlKursy(platforma);
            if (!kursy.empty()) {
                cout << "0. Powrot\n";
                int numer = wczytajLiczbe(
                    "Wybierz kurs do zapisania: ", 0,
                    static_cast<int>(kursy.size()));
                if (numer == 0) {
                    continue;
                }
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
                przejdzKolejnyModul(kursant.getPostep(indeks));
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

void obsluzWykladowce(PlatformaEdukacyjna& platforma,
                      const Wykladowca& wykladowca) {
    int wybor;

    do {
        cout << "\n--- Menu wykladowcy ---\n"
             << "1. Utworz kurs\n"
             << "2. Pokaz wszystkie kursy\n"
             << "0. Powrot\n";
        wybor = wczytajLiczbe("Wybierz opcje: ", 0, 2);

        if (wybor == 1) {
            utworzKurs(platforma, wykladowca);
        } else if (wybor == 2) {
            wyswietlKursy(platforma);
        }
    } while (wybor != 0);
}

void dodajKursyBazowe(PlatformaEdukacyjna& platforma,
                      const Wykladowca& wykladowca) {
    Kurs podstawyCpp = wykladowca.utworzKurs("C++ od podstaw");
    Modul cppWprowadzenie("Wprowadzenie do C++", 1);
    cppWprowadzenie.dodajLekcje(Lekcja(
        "Aby pisac programy w C++, potrzebujesz kompilatora, czyli "
        "programu, ktory zamienia kod zrodlowy na plik wykonywalny. "
        "W tej lekcji instalujesz kompilator g++ oraz srodowisko CLion "
        "i sprawdzasz poleceniem g++ --version, czy wszystko dziala."));
    cppWprowadzenie.dodajLekcje(Lekcja(
        "Piszesz klasyczny program Hello World. Poznajesz funkcje main, "
        "od ktorej zaczyna sie kazdy program, biblioteke iostream oraz "
        "obiekt cout, ktory wypisuje tekst na ekran. Na koniec "
        "kompilujesz i uruchamiasz swoj pierwszy program."));
    podstawyCpp.dodajModul(cppWprowadzenie);

    Modul cppObiekty("Klasy i obiekty", 2);
    cppObiekty.dodajLekcje(Lekcja(
        "Klasa to przepis na obiekty: opisuje, jakie dane maja obiekty "
        "(pola) i co potrafia robic (metody). Tworzysz klase z polami "
        "prywatnymi i metodami publicznymi oraz uczysz sie, czym rozni "
        "sie klasa od obiektu."));
    cppObiekty.dodajLekcje(Lekcja(
        "Konstruktor to specjalna metoda wywolywana automatycznie przy "
        "tworzeniu obiektu. Poznajesz liste inicjalizacyjna, "
        "konstruktory z parametrami i bez nich oraz destruktor, ktory "
        "sprzata, gdy obiekt przestaje istniec."));
    podstawyCpp.dodajModul(cppObiekty);
    platforma.dodajKurs(podstawyCpp);

    Kurs podstawyPython = wykladowca.utworzKurs("Python dla poczatkujacych");
    Modul pythonWprowadzenie("Podstawy jezyka", 1);
    pythonWprowadzenie.dodajLekcje(Lekcja(
        "W Pythonie nie trzeba deklarowac typu zmiennej, bo jezyk sam "
        "go rozpoznaje. Poznajesz podstawowe typy: liczby calkowite "
        "(int), zmiennoprzecinkowe (float), napisy (str) i wartosci "
        "logiczne (bool) oraz funkcje type()."));
    pythonWprowadzenie.dodajLekcje(Lekcja(
        "Instrukcje if, elif i else pozwalaja programowi podejmowac "
        "decyzje. Uczysz sie porownywac wartosci, laczyc warunki "
        "slowami and i or oraz pamietac o wcieciach, ktore w Pythonie "
        "wyznaczaja bloki kodu."));
    podstawyPython.dodajModul(pythonWprowadzenie);

    Modul pythonKolekcje("Kolekcje danych", 2);
    pythonKolekcje.dodajLekcje(Lekcja(
        "Lista przechowuje wiele wartosci w jednej zmiennej, w "
        "okreslonej kolejnosci. Poznajesz dodawanie elementow metoda "
        "append(), odczyt po indeksie liczonym od 0 oraz przechodzenie "
        "po liscie petla for."));
    pythonKolekcje.dodajLekcje(Lekcja(
        "Slownik przechowuje pary klucz-wartosc, na przyklad imie i "
        "numer telefonu. Uczysz sie dodawac i odczytywac elementy po "
        "kluczu, sprawdzac, czy klucz istnieje, oraz przechodzic po "
        "wszystkich parach petla for."));
    podstawyPython.dodajModul(pythonKolekcje);
    platforma.dodajKurs(podstawyPython);
}

int wybierzWykladowce(const vector<Wykladowca>& wykladowcy) {
    cout << "\nWykladowcy:\n";
    for (int i = 0; i < static_cast<int>(wykladowcy.size()); ++i) {
        cout << i + 1 << ". " << wykladowcy[i].getImie() << " "
             << wykladowcy[i].getNazwisko() << '\n';
    }
    cout << "0. Powrot\n";

    return wczytajLiczbe("Wybierz wykladowce: ", 0,
                         static_cast<int>(wykladowcy.size())) - 1;
}

int wybierzKursanta(const vector<Kursant>& kursanci) {
    cout << "\nKursanci:\n";
    for (int i = 0; i < static_cast<int>(kursanci.size()); ++i) {
        cout << i + 1 << ". " << kursanci[i].getImie() << " "
             << kursanci[i].getNazwisko() << '\n';
    }
    cout << "0. Powrot\n";

    return wczytajLiczbe("Wybierz kursanta: ", 0,
                         static_cast<int>(kursanci.size())) - 1;
}

void dodajWykladowce(vector<Wykladowca>& wykladowcy, int& nastepneId) {
    string imie = wczytajTekst("Podaj imie (0 - powrot): ");
    if (imie == "0") {
        return;
    }
    string nazwisko = wczytajTekst("Podaj nazwisko: ");

    wykladowcy.push_back(Wykladowca(imie, nazwisko, nastepneId));
    ++nastepneId;
    cout << "Dodano wykladowce: " << imie << " " << nazwisko << '\n';
}

void dodajKursanta(vector<Kursant>& kursanci, int& nastepneId) {
    string imie = wczytajTekst("Podaj imie (0 - powrot): ");
    if (imie == "0") {
        return;
    }
    string nazwisko = wczytajTekst("Podaj nazwisko: ");

    kursanci.push_back(Kursant(imie, nazwisko, nastepneId));
    ++nastepneId;
    cout << "Dodano kursanta: " << imie << " " << nazwisko << '\n';
}

int main() {
    PlatformaEdukacyjna platforma;
    vector<Wykladowca> wykladowcy;
    vector<Kursant> kursanci;
    int nastepneId = 3;
    int wybor;

    wykladowcy.push_back(Wykladowca("Anna", "Nowak", 1));
    kursanci.push_back(Kursant("Jan", "Kowalski", 2));
    dodajKursyBazowe(platforma, wykladowcy[0]);

    cout << "Platforma Kursow Online\n";

    do {
        cout << "\n--- Menu glowne ---\n"
             << "1. Panel wykladowcy\n"
             << "2. Panel kursanta\n"
             << "3. Pokaz wszystkie kursy\n"
             << "4. Dodaj wykladowce\n"
             << "5. Dodaj kursanta\n"
             << "0. Zakoncz program\n";
        wybor = wczytajLiczbe("Wybierz opcje: ", 0, 5);

        if (wybor == 1) {
            int i = wybierzWykladowce(wykladowcy);
            if (i >= 0) {
                cout << "Zalogowano jako: " << wykladowcy[i].getImie() << " "
                     << wykladowcy[i].getNazwisko() << '\n';
                obsluzWykladowce(platforma, wykladowcy[i]);
            }
        } else if (wybor == 2) {
            int i = wybierzKursanta(kursanci);
            if (i >= 0) {
                cout << "Zalogowano jako: " << kursanci[i].getImie() << " "
                     << kursanci[i].getNazwisko() << '\n';
                obsluzKursanta(platforma, kursanci[i]);
            }
        } else if (wybor == 3) {
            wyswietlKursy(platforma);
        } else if (wybor == 4) {
            dodajWykladowce(wykladowcy, nastepneId);
        } else if (wybor == 5) {
            dodajKursanta(kursanci, nastepneId);
        }
    } while (wybor != 0);

    cout << "Dziekujemy za skorzystanie z platformy.\n";
    return 0;
}