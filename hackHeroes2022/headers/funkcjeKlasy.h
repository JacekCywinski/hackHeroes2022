#ifndef FUNKCJEKLASY_H
#define FUNKCJEKLASY_H

#include <string>
#include <string_view>

// struktura z danymi kont
struct Konto
{
    std::string imie{};
    std::string nazwisko{};
    std::string haslo{};
    double saldo{};
    double zebranePieniadze{};
    double zbiorkaKwota{};
    std::string zbiorka{};
};

// prototypy funkcji

void zalogujLubZarejestruj();

void zalogujLubZarejestruj(std::string_view wybor);

std::string podajImie();

std::string podajNazwisko();

std::string podajHaslo();

void zaloguj(Konto &konto);

void zarejestruj(Konto &konto);

void menuWybor(Konto &konto);

void wyswietlZbiorkiWybor(Konto &konto);

void brakZbiorekWybor(Konto &konto);

void profilWybor(Konto &konto);

void doladujKonto(Konto &konto);

void utworzZbiorke(Konto &konto);

void usunKonto(Konto &konto);

void dorzucDoZbiorki(Konto &konto);

void zawinTekst(std::string tekst, const int iloscZnakow);

#endif