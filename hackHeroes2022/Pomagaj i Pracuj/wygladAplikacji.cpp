#include "headers/wygladAplikacji.h"
#include "headers/funkcjeKlasy.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

// funkja wyświetlająca informację o konieczności zalogowania lub rejestracji
void ekranLogowania()
{
    // usuniecie poprzednich informacji z konsoli
    system("CLS");

    // wyświetlenie początkowego ekranu aplikacji
    std::cout << " ______________________________________________________________________________________________________________________________________ \n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                             Aby kontynuowac zaloguj sie lub zarejestruj.                                             |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << " ______________________________________________________________________________________________________________________________________ \n\n";

    // wywołanie funkcji do logowania i rejestracji
    zalogujLubZarejestruj();
}

// funcja wyświetlająca menu główne, zawierające dostępne zakładki do wybrania
void menuGlowne(Konto &konto)
{
    // usuniecie poprzednich informacji z konsoli
    system("CLS");

    // stworzenie linii wypisującej imię, nazwisko oraz saldo zalogowanego użytkownika
    std::ostringstream infoSstream;
    infoSstream << "Zalogowano jako: " << konto.imie << ' ' << konto.nazwisko << ", Saldo: " << std::fixed << std::setprecision(2) << konto.saldo << "zl";
    std::string info{infoSstream.str()};

    // wyświetlenie menu głównego
    std::cout << " ______________________________________________________________________________________________________________________________________ \n";
    std::cout << "|   " << std::left << std::setw(128) << info << "   |\n"; // wypisanie imienia, nazwiska oraz salda zalogowanego użytkownika
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|   ZBIORKI      PROFIL                                                                                                                |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << " ______________________________________________________________________________________________________________________________________ \n\n";

    // wywołanie funkcji do wyboru zakładki
    menuWybor(konto);
}

// funkcja wyświetlająca informację o braku dostępnych zbiórek
void brakZbiorek(Konto &konto)
{
    // usuniecie poprzednich informacji z konsoli
    system("CLS");

    // stworzenie linii wypisującej imię, nazwisko oraz saldo zalogowanego użytkownika
    std::ostringstream infoSstream;
    infoSstream << "Zalogowano jako: " << konto.imie << ' ' << konto.nazwisko << ", Saldo: " << std::fixed << std::setprecision(2) << konto.saldo << "zl";
    std::string info{infoSstream.str()};

    // wyświetlenie informacji o braku dostępnych zbiórek
    std::cout << " ______________________________________________________________________________________________________________________________________ \n";
    std::cout << "|   " << std::left << std::setw(128) << info << "   |\n"; // wypisanie imienia, nazwiska oraz salda zalogowanego użytkownika
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                   Aktualnie nie ma zadnych zbiorek                                                   |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << " ______________________________________________________________________________________________________________________________________ \n\n";

    // wywołanie funckji do wyboru opcji
    brakZbiorekWybor(konto);
}

// funkcja wyświetlająca wszystkie dostępne zbiórki
void wyswietlZbiorki(Konto &kontoInfo)
{
    // usuniecie poprzednich informacji z konsoli
    system("CLS");

    // stworzenie linii wypisującej imię, nazwisko oraz saldo zalogowanego użytkownika
    std::ostringstream infoSstream;
    infoSstream << "Zalogowano jako: " << kontoInfo.imie << ' ' << kontoInfo.nazwisko << ", Saldo: " << std::fixed << std::setprecision(2) << kontoInfo.saldo << "zl";
    std::string info{infoSstream.str()};

    // sprawdzenie czy konto posiada zbiorkę, aby w razie braku jakichkolwiek zbiórek nie wyswietlić pustego ekranu
    bool puste{true};

    // wyświetlenie nagłówka
    std::cout << " ______________________________________________________________________________________________________________________________________ \n";
    std::cout << "|   " << std::left << std::setw(128) << info << "   |\n"; // wypisanie imienia, nazwiska oraz salda zalogowanego użytkownika
    std::cout << "|                                                                                                                                      |\n";

    // przeszukanie folderu "konta" w celu znalezienia dostępnych kont, z których można wypisać zbiórki
    const fs::path konta{"/konta/"};
    for (auto const &i : fs::directory_iterator{konta.parent_path().filename()})
    {
        // stworzenie obiektu zawierającego informacje o koncie
        Konto konto{};

        // otworzenie znalezionego konta
        std::ifstream plik(i.path());

        // spisanie wszystkich informacji z konta do obiektu
        plik >> konto.imie;
        plik >> konto.nazwisko;
        plik >> konto.haslo;
        plik >> konto.saldo;
        plik >> konto.zebranePieniadze;
        plik >> konto.zbiorkaKwota;
        std::getline(plik >> std::ws, konto.zbiorka);

        // jeżeli to konto nie posiada zbiórki, przejdz do kolejnego konta
        if (konto.zbiorka.empty())
        {
            continue;
        }

        // po znalezieniu zbiorki na koncie, wyślij informację o tym, że istnieje jakakolwiek zbiórka do wyświetlenia
        puste = false;

        // wyświetlenie imienia i nazwiska właściciela zbiórki, kwoty zebranej, celu zbiórki oraz samej zbiórki
        std::cout << "|   " << std::left << std::setw(128) << konto.imie << "   |\n";
        std::cout << "|   " << std::left << std::setw(128) << konto.nazwisko << "   |\n";
        std::cout << "|                                                                                                                                      |\n";
        std::ostringstream zebranaKwota;
        zebranaKwota << "Zebrana kwota: " << std::fixed << std::setprecision(2) << konto.zebranePieniadze << '/' << konto.zbiorkaKwota << "zl";
        std::cout << "|   " << std::left << std::setw(128) << zebranaKwota.str() << "   |\n";
        std::cout << "|                                                                                                                                      |\n";
        zawinTekst(konto.zbiorka, 128);
        // przerywnik oddzielający jedną zbiórkę od drugiej
        std::cout << "|                                                                                                                                      |\n";
        std::cout << "|   --------------------------------------------------------------------------------------------------------------------------------   |\n";
        std::cout << "|                                                                                                                                      |\n";

        plik.close();
    }

    // ostatnie linie ekranu
    std::cout << "|                                                                                                                                      |\n";
    std::cout << " ____________________________________________________________________________________________________________________________________ \n\n";

    // jeżeli żadna zbiórka nie została znaleziona, wyświetl informację o braku zbiórek
    if (puste == true)
    {
        brakZbiorek(kontoInfo);
    }

    // wywołanie funkcji do wyboru opcji
    wyswietlZbiorkiWybor(kontoInfo);
}

void profil(Konto &konto)
{
    // usuniecie poprzednich informacji z konsoli
    system("CLS");

    // stworzenie linii wypisującej imię, nazwisko oraz saldo zalogowanego użytkownika
    std::ostringstream infoSstream;
    infoSstream << "Zalogowano jako: " << konto.imie << ' ' << konto.nazwisko << ", Saldo: " << std::fixed << std::setprecision(2) << konto.saldo << "zl";
    std::string info{infoSstream.str()};

    // wyświetlenie opcji dostępnych dla zalogowanego użytkownika
    std::cout << " ______________________________________________________________________________________________________________________________________ \n";
    std::cout << "|   " << std::left << std::setw(128) << info << "   |\n"; // wypisanie imienia, nazwiska oraz salda zalogowanego użytkownika
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|   1. Doladuj konto.                                                                                                                  |\n";
    std::cout << "|   2. Utworz zbiorke (mozesz posiadac maksymalnie jedna zbiorke na raz).                                                              |\n";
    std::cout << "|   3. Usun konto.                                                                                                                     |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << "|                                                                                                                                      |\n";
    std::cout << " ______________________________________________________________________________________________________________________________________ \n\n";

    // wywołanie funkcji do wyboru opcji
    profilWybor(konto);
}