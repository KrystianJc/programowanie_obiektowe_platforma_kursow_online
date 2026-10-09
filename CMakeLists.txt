cmake_minimum_required(VERSION 4.3)
project(programowanie_obiektowe_platforma_kursow_online)

set(CMAKE_CXX_STANDARD 14)

add_executable(programowanie_obiektowe_platforma_kursow_online
        main.cpp
        Uzytkownicy/uzytkownik.cpp
        Uzytkownicy/uzytkownik.h
        Uzytkownicy/kursant.cpp
        Uzytkownicy/kursant.h
        Uzytkownicy/wykladowca.cpp
        Uzytkownicy/wykladowca.h)
