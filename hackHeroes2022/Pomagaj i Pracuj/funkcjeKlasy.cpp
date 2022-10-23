#include "headers/wygladAplikacji.h"
#include "headers/funkcjeKlasy.h"
#include <iostream>
#include <string>
#include <string_view>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <limits>

namespace fs = std::filesystem;

// funkcja przyjmująca wybór na ekranie logowania
void zalogujLubZarejestruj()
{
    while (true)
    {
        // wybranie opcji
        std::string wybor{};
        std::cout << "Wpisz \"zaloguj\" by zalogowac sie, \"zarejestruj\" by zarejestrowac sie, lub \"wyjdz\" by wylaczyc aplikacje: ";
        std::cin >> wybor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // wywołanie funkcji wyświetlającej informacje zależne od wyboru
        zalogujLubZarejestruj(wybor);
    }
}

// funkcja wyświetlająca informacje zależne od wyboru
void zalogujLubZarejestruj(std::string_view wybor)
{
    // jeżeli wybrano opcję "zaloguj"...
    if (wybor == "zaloguj")
    {
        // ...utwórz obiekt zawierający informacje o koncie
        Konto konto{};

        // poproś o imię, nazwisko oraz hasło, potrzebne do zalogowania się
        konto.imie = podajImie();
        konto.nazwisko = podajNazwisko();
        konto.haslo = podajHaslo();

        // wywołanie funkcji umożliwiającej zalogowanie się
        zaloguj(konto);
    }
    else if (wybor == "zarejestruj") // jeżeli wybrano opcję "zarejestruj"...
    {
        // ...utwórz obiekt zawierający informacje o koncie
        Konto konto{};

        // poproś o imię, nazwisko oraz hasło, potrzebne do zarejestrowania się
        konto.imie = podajImie();
        konto.nazwisko = podajNazwisko();
        konto.haslo = podajHaslo();

        // wywołanie funkcji umożliwiającej zarejestrowanie się
        zarejestruj(konto);
    }
    else if (wybor == "wyjdz") // jeżeli wybrano opcję "wyjdz"...
    {
        // ...wyjdź z aplikacji
        std::exit(0);
    }
    else // jeżeli podano niepoprawną opcję, poproś o ponowne podanie jej
    {
        std::cout << "Podano nieprawidlowa opcje. Sprobuj jeszcze raz.\n";
    }
}

// funkcja pobierająca imię od użytkownika
std::string podajImie()
{
    std::string imie{};
    std::cout << "Podaj imie: ";
    std::cin >> imie;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return imie;
}

// funkcja pobierająca nazwisko od użytkownika
std::string podajNazwisko()
{
    std::string nazwisko{};
    std::cout << "Podaj nazwisko: ";
    std::cin >> nazwisko;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return nazwisko;
}

// funkcja pobierająca hasło od użytkownika
std::string podajHaslo()
{
    std::string haslo{};
    std::cout << "Podaj haslo: ";
    std::cin >> haslo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return haslo;
}

// funkcja umożliwiająca zalogowanie się
void zaloguj(Konto &konto)
{
    // sprawdź czy podane konto istnieje, jeśli nie wyświetl błąd
    if (!(std::ifstream("konta/" + konto.imie + konto.nazwisko + ".txt")))
    {
        std::cout << "To konto nie istnieje.\n";

        return;
    }

    // otwórz plik z kontem
    std::ifstream plik("konta/" + konto.imie + konto.nazwisko + ".txt");
    if (!plik) // jeżeli nie udało się otworzyć, wyświetl błąd
    {
        std::cout << "Cos poszlo nie tak, sprobuj jeszcze raz.\n";

        return;
    }
    else // jeżeli udało się otworzyć
    {
        // zmienna potrzebna do sprawdzenia czy podane hasło, zgadza się z tym zapisanym w pliku
        std::string sprawdzHaslo{};

        // pobranie hasła z pliku do zmiennej oraz innych danych z pliku z pominięciem imienia i nazwiska, ponieważ one zostały podane wcześniej
        plik >> sprawdzHaslo;
        plik >> sprawdzHaslo;
        plik >> sprawdzHaslo;
        plik >> konto.saldo;
        plik >> konto.zebranePieniadze;
        plik >> konto.zbiorkaKwota;
        std::getline(plik >> std::ws, konto.zbiorka);

        plik.close();

        // jeżeli podane hasło zgadza się z tym zapisanym w pliku, zaloguj
        if (konto.haslo == sprawdzHaslo)
        {
            std::cout << "Zalogowano pomyslnie.\n";

            // wywołanie funkcji wyświetlającej menu główne
            menuGlowne(konto);
        }
        else // jeżeli podane hasło nie zgadza się z tym zapisanym w pliku, wyświetl informację o złym haśle
        {
            std::cout << "Podano zle haslo.\n";
        }
    }
}

// funkcja umożliwiająca zarejestrowanie się
void zarejestruj(Konto &konto)
{
    // sprawdź czy podane konto istnieje, jeśli tak wyświetl informację o istniejącym koncie
    if (std::ifstream("konta/" + konto.imie + konto.nazwisko + ".txt"))
    {
        std::cout << "To konto juz istnieje.\n";

        return;
    }

    // otwórz plik z kontem
    std::ofstream plik("konta/" + konto.imie + konto.nazwisko + ".txt");
    if (!plik) // jeżeli nie udało się otworzyć, wyświetl błąd
    {
        std::cout << "Cos poszlo nie tak, sprobuj jeszcze raz.\n";

        return;
    }
    else // jeżeli udało się otworzyć
    {
        // zapisz wszystkie dane do pliku
        plik << konto.imie << '\n';
        plik << konto.nazwisko << '\n';
        plik << konto.haslo << '\n';
        plik << konto.saldo << '\n';
        plik << konto.zebranePieniadze << '\n';
        plik << konto.zbiorkaKwota << '\n';
        plik << konto.zbiorka;

        plik.close();

        std::cout << "Konto utworzono pomyslnie.\n";
    }
}

// funkcja umożliwiająca wybranie zakładki w menu głównym
void menuWybor(Konto &konto)
{
    while (true)
    {
        // wybierz opcję
        std::string wybor{};
        std::cout << "Wybierz zakladke lub wpisz \"wyjdz\" by wylaczyc aplikacje: ";
        std::cin >> wybor;

        // jeżeli wybrano opcję "zbiorki"
        if (wybor == "zbiorki")
        {
            // jeżeli w folderze "konta" nie ma żadnych kont, wyświetl informację o braku zbiórek
            const fs::path konta{"/konta/"};
            if (fs::is_empty(konta.parent_path().filename()))
            {
                brakZbiorek(konto);
            }
            else // jeżeli w folderze "konta" są konta, wyświetl wszystkie dostępne zbiórki
            {
                wyswietlZbiorki(konto);
            }
        }
        else if (wybor == "profil") // jeżeli wybrano opcję "profil"...
        {
            // ...wyświetl opcje dostępne dla zalogowanego użytkownika
            profil(konto);
        }
        else if (wybor == "wyjdz") // jeżeli wybrano opcję "wyjdz"...
        {
            // ...wyjdz z aplikacji
            std::exit(0);
        }
        else // jeżeli podano niepoprawną opcję, poproś o ponowne podanie jej
        {
            std::cout << "Podano zla zakladke. Sprobuj jeszcze raz.\n";
        }
    }
}

// funkcja umożliwiająca wybranie opcji po wyświetleniu zbiórek
void wyswietlZbiorkiWybor(Konto &konto)
{
    while (true)
    {
        // wybranie opcji
        std::string wybor{};
        std::cout << "Wpisz \"dorzuc\" by dorzucic sie do zbiorki lub wpisz \"menu\" by wrocic do menu lub wpisz \"wyjdz\" by wylaczyc aplikacje: ";
        std::cin >> wybor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // jeżeli wybrano opcję "dorzuc"...
        if (wybor == "dorzuc")
        {
            // ...wywołaj funkcje umożliwiającą dorzucenie pieniędzy do zbiórki
            dorzucDoZbiorki(konto);
        }
        else if (wybor == "menu") // jeżeli wybrano opcję "menu"...
        {
            // ...wróć do menu głównego
            menuGlowne(konto);
        }
        else if (wybor == "wyjdz") // jeżeli wybrano opcję "wyjdz"...
        {
            // ...wyjdź z aplikacji
            std::exit(0);
        }
        else // jeżeli podano niepoprawną opcję, poproś o ponowne podanie jej
        {
            std::cout << "Podano niepoprawna opcje. Sprobuj jeszcze raz.\n";
        }
    }
}

// funkcja umożliwiająca wybranie opcji po wyświetleniu informacji o braku zbiórek
void brakZbiorekWybor(Konto &konto)
{
    while (true)
    {
        // wybranie opcji
        std::string wybor{};
        std::cout << "Wpisz \"menu\" by wrocic do menu lub wpisz \"wyjdz\" by wylaczyc aplikacje: ";
        std::cin >> wybor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // jeżeli wybrano opcję "menu"...
        if (wybor == "menu") 
        {
            // ...wróć do menu głównego
            menuGlowne(konto);
        }
        else if (wybor == "wyjdz") // jeżeli wybrano opcję "wyjdz"...
        {
            // ...wyjdź z aplikacji
            std::exit(0);
        }
        else // jeżeli podano niepoprawną opcję, poproś o ponowne podanie jej
        {
            std::cout << "Podano niepoprawna opcje. Sprobuj jeszcze raz.\n";
        }
    }
}

// funkcja umożliwiająca wybranie opcji dotyczących zalogowanego użytkownika
void profilWybor(Konto &konto)
{
    while (true)
    {
        // wybranie opcji
        std::string wybor{};
        std::cout << "Wybierz opcje lub wpisz \"menu\" by wrocic do menu lub wpisz \"wyjdz\" by wylaczyc aplikacje: ";
        std::getline(std::cin >> std::ws, wybor);

        // jeżeli wybrano opcję "doladuj konto" lub "1"...
        if (wybor == "doladuj konto" || wybor == "1")
        {
            // ...wywołaj funkcję umożliwiającą doładowanie środków na koncie
            doladujKonto(konto);
        }
        else if (wybor == "utworz zbiorke" || wybor == "2") // jeżeli wybrano opcję "utworz zbiorke" lub "2"...
        {
            // ...wywołaj funkcję umożliwiającą utworzenie zbiórki
            utworzZbiorke(konto);
        }
        else if (wybor == "usun konto" || wybor == "3") // jeżeli wybrano opcję "usun konto" lub "3"...
        {
            // ...wywołaj funkcję umożliwiającą usunięcie konta
            usunKonto(konto);
        }
        else if (wybor == "menu") // jeżeli wybrano opcję "menu"...
        {
            // ...wróć do menu głównego
            menuGlowne(konto);
        }
        else if (wybor == "wyjdz") // jeżeli wybrano opcję "wyjdz"...
        {
            // ...wyjdź z aplikacji
            std::exit(0);
        }
        else // jeżeli podano niepoprawną opcję, poproś o ponowne podanie jej
        {
            std::cout << "Podano zla opcje. Sprobuj jeszcze raz.\n";
        }
    }
}

// funkcja umożliwiająca dodanie środków na koncie
void doladujKonto(Konto &konto)
{
    while (true)
    {
        // wybranie opcji
        double kwota{};
        std::cout << "Podaj kwote jaka chcesz doladowac: ";
        std::cin >> kwota;

        // jeżeli wpisano jakieś litery, wyświetl błąd i poproś o ponowne podanie jej
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Podano nieprawidlowa liczbe. Sprobuj jeszcze raz.\n";
        }
        else // jeżeli wpisano prawidłową wartość
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // dopisz do salda podaną kwotę
            konto.saldo += kwota;

            // zapisz saldo w pliku z kontem
            std::ofstream plik("konta/" + konto.imie + konto.nazwisko + ".txt");
            if (!plik)
            {
                std::cout << "Cos poszlo nie tak, sprobuj jeszcze raz.\n";

                return;
            }
            else
            {
                plik << konto.imie << '\n';
                plik << konto.nazwisko << '\n';
                plik << konto.haslo << '\n';
                plik << konto.saldo << '\n';
                plik << konto.zebranePieniadze << '\n';
                plik << konto.zbiorkaKwota << '\n';
                plik << konto.zbiorka;

                plik.close();

                std::cout << "Srodki dodano pomyslnie.\n";

                // wyświetl profil ponownie ze zaktualizowanym saldem w nagłówku
                profil(konto);
            }
        }
    }
}

// funkcja umożliwiająca utworzenie zbiórki
void utworzZbiorke(Konto &konto)
{
    while (true)
    {
        // podaj zbieraną kwotę
        std::cout << "Wpisz zbierana kwote: ";
        std::cin >> konto.zbiorkaKwota;

        // jeżeli wpisano jakieś litery, wyświetl błąd i poproś o ponowne podanie jej
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Podano nieprawidlowa liczbe. Sprobuj jeszcze raz.\n";
        }
        else // jeżeli wpisano prawidłową wartość wyjdź z pętli
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    // podaj treść zbiórki
    std::cout << "Napisz informacje dotyczace zbiorki: ";
    std::getline(std::cin >> std::ws, konto.zbiorka);

    // zapisz treść zbiórki w pliku z kontem
    std::ofstream plik("konta/" + konto.imie + konto.nazwisko + ".txt");
    if (!plik)
    {
        std::cout << "Cos poszlo nie tak, sprobuj jeszcze raz.\n";

        return;
    }
    else
    {
        plik << konto.imie << '\n';
        plik << konto.nazwisko << '\n';
        plik << konto.haslo << '\n';
        plik << konto.saldo << '\n';
        plik << konto.zebranePieniadze << '\n';
        plik << konto.zbiorkaKwota << '\n';
        plik << konto.zbiorka;

        plik.close();

        std::cout << "Zbiorka dodana pomyslnie.\n";

        // wróć do profilu
        profil(konto);
    }
}

// funkcja umożliwiająca usunięcie konta
void usunKonto(Konto &konto)
{
    while (true)
    {
        // podaj hasło
        std::string sprawdzHaslo{podajHaslo()};

        // jeżeli podane hasło zgadza się z hasłem podanym w pliku
        if (konto.haslo == sprawdzHaslo)
        {
            int wynik = remove(("konta/" + konto.imie + konto.nazwisko + ".txt").c_str());
            // sprawdź czy usunięcie konta powiodło się
            if (wynik == 0) // jeżeli usunięto konto, wyświetl informację o usunięciu konta
            {
                std::cout << "Konto usuniete pomyslnie\n";
                break;
            }
            else // jeżeli nie usunięto konta, wyświetl błąd
            {
                std::cout << "Cos poszlo nie tak. Sprobuj jeszcze raz.\n";
            }
        }
        else // jeżeli podane hasło nie zgadza się z hasłem podanym w pliku, wyświetl błąd
        {
            std::cout << "Podano zle haslo. Spróbuj jeszcze raz.\n";
        }
    }

    // wróć do ekranu logowania
    ekranLogowania();
}

// funkcja umożliwiająca dorzucenie pieniędzy do zbiórki
void dorzucDoZbiorki(Konto &konto)
{
    // utwórz obiekt z informacjami dotyczącymi zbiórki do której chcemy się dorzucić
    Konto kontoZeZbiorki{};

    // podaj imię i nazwisko właściciela zbiórki do której chcemy się dorzucić
    kontoZeZbiorki.imie = podajImie();
    kontoZeZbiorki.nazwisko = podajNazwisko();

    // jeżeli podano imię i nazwisko zalogowanego użytkownika, wyświetl informację o braku możliwości dorzucenia się do własnej zbiórki
    if ((kontoZeZbiorki.imie == konto.imie) && (kontoZeZbiorki.nazwisko == konto.nazwisko))
    {
        std:: cout << "Nie mozna wplacic pieniedzy na wlasna zbiorke.\n";

        return;
    }

    // jeżeli konto o takim imieniu i nazwisku nie istnieje, wyświetl informację o braku takiej zbiórki
    if (!(std::ifstream("konta/" + kontoZeZbiorki.imie + kontoZeZbiorki.nazwisko + ".txt")))
    {
        std::cout << "Taka zbiorka nie istnieje\n";

        return;
    }

    // otwórz plik z kontem właściciela zbiórki
    std::ifstream plik("konta/" + kontoZeZbiorki.imie + kontoZeZbiorki.nazwisko + ".txt");
    if (!plik) // jeżeli nie udało się otworzyć pliku, wyświetl błąd
    {
        std::cout << "Cos poszlo nie tak, sprobuj jeszcze raz.\n";

        return;
    }
    else
    {
        // pobierz dane z konta właściciela zbiórki
        plik >> kontoZeZbiorki.imie;
        plik >> kontoZeZbiorki.nazwisko;
        plik >> kontoZeZbiorki.haslo;
        plik >> kontoZeZbiorki.saldo;
        plik >> kontoZeZbiorki.zebranePieniadze;
        plik >> kontoZeZbiorki.zbiorkaKwota;
        std::getline(plik >> std::ws, kontoZeZbiorki.zbiorka);

        plik.close();

        // jeżeli na tym koncie nie ma zbiórki, wyświetl informację o braku takiej zbiórki
        if (kontoZeZbiorki.zbiorka.empty())
        {
            std::cout << "Taka zbiorka nie istnieje\n";
        }
    }

    while (true)
    {
        // podaj kwotę jaką chcesz dorzucić
        double kwota{};
        std::cout << "Podaj kwote jaka chcesz wplacic: ";
        std::cin >> kwota;

        // jeżeli wpisano jakieś litery, wyświetl błąd i poproś o ponowne podanie jej
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Podano nieprawidlowa liczbe. Sprobuj jeszcze raz.\n";
        }
        else // jeżeli wpisano prawidłową wartość...
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // ...sprawdź czy posiadasz wystarczającą liczbe środków na koncie
            if (kwota > konto.saldo) // jeśli nie, wyświetl informację o braku środków na koncie
            {
                std::cout << "Nie posiadasz wystarczajacych srodkow na koncie.\n";

                continue;
            }
            else // jeśli tak...
            {
                // ...do zebranej już kwoty dopisz podaną wartość
                kontoZeZbiorki.zebranePieniadze += kwota;

                // zapisz zaktualizowaną zebraną kwotę w pliku z kontem właściciela zbiórki
                std::ofstream plik("konta/" + kontoZeZbiorki.imie + kontoZeZbiorki.nazwisko + ".txt");
                if (!plik)
                {
                    std::cout << "Cos poszlo nie tak, sprobuj jeszcze raz.\n";

                    return;
                }
                else
                {
                    plik << kontoZeZbiorki.imie << '\n';
                    plik << kontoZeZbiorki.nazwisko << '\n';
                    plik << kontoZeZbiorki.haslo << '\n';
                    plik << kontoZeZbiorki.saldo << '\n';
                    plik << kontoZeZbiorki.zebranePieniadze << '\n';
                    plik << kontoZeZbiorki.zbiorkaKwota << '\n';
                    plik << kontoZeZbiorki.zbiorka;

                    plik.close();
                }

                // od salda zalogowanego użytkownika odejmij podaną kwotę
                konto.saldo -= kwota;

                // zapisz zaktualizowane saldo w pliku z kontem zalogowanego użytkownika
                plik.open("konta/" + konto.imie + konto.nazwisko + ".txt");
                if (!plik)
                {
                    std::cout << "Cos poszlo nie tak, sprobuj jeszcze raz.\n";

                    return;
                }
                else
                {
                    plik << konto.imie << '\n';
                    plik << konto.nazwisko << '\n';
                    plik << konto.haslo << '\n';
                    plik << konto.saldo << '\n';
                    plik << konto.zebranePieniadze << '\n';
                    plik << konto.zbiorkaKwota << '\n';
                    plik << konto.zbiorka;

                    plik.close();
                }

                std::cout << "Srodki wplacono pomyslnie.\n";

                // wyświetl zbiórki ze zaktualizowanymi danymi
                wyswietlZbiorki(konto);
            }
        }
    }
}

// funkcja "zawijająca" podany tekst tak aby pasował do podanej szerokości pola tekstowego wraz z marginesami
void zawinTekst(std::string tekst, const int iloscZnakow)
{
    int dlugoscTekstu{static_cast<int>(tekst.length())}; // zapisz do zmiennej długość podanego tekstu
    int ostatniIndex{};                                  // index ostatnio wypisanego znaku
    int wypisaneZnaki{};                                 // ilość wypisanych znaków

    while (dlugoscTekstu > iloscZnakow)
    {
        // jeżeli znak na miejscu wypisanych znaków + ilości znaków w wierszu jest spacją
        if (tekst.at(wypisaneZnaki + iloscZnakow) == ' ')
        {
            // wypisz substring od ostatniego indexu do wypisanych znaków + ilości znaków w wierszu
            std::cout << "|   " << std::setw(iloscZnakow) << tekst.substr(ostatniIndex, wypisaneZnaki + iloscZnakow - ostatniIndex) << "   |\n";

            dlugoscTekstu -= iloscZnakow + 1; // od długości tekstu odejmij ilość znaków w wierszu + 1(aby nie wypisywać dodatkowej spacji na początku zdania)
            wypisaneZnaki += iloscZnakow + 1; // do wypisanych znaków dodaj ilość znaków w wierszu + 1(aby nie wypisywać dodatkowej spacji na początku zdania)
            ostatniIndex = wypisaneZnaki;     // za ostatni index przypisz index ostatnio wypisanego znaku
        }
        else // jeżeli znak na miejscu wypisanych znaków + ilości znaków w wierszu nie jest spacją
        {
            // wypisz substring od ostatniego indexu do pierwszej spacji napotkanej przed wypisanymi znakami + ilością znaków w wierszu
            std::cout << "|   " << std::setw(iloscZnakow) << tekst.substr(ostatniIndex, tekst.rfind(' ', wypisaneZnaki + iloscZnakow) - ostatniIndex) << "   |\n";

            // od długości tekstu odejmij długość substringu od ostatniego indexu do pierwszej spacji napotkanej przed wypisanymi znakami + ilością znaków w wierszu +1
            // (aby nie wypisywać dodatkowej spacji na początku zdania)
            dlugoscTekstu -= tekst.substr(ostatniIndex, tekst.rfind(' ', wypisaneZnaki + iloscZnakow) - ostatniIndex).length() + 1;
            // do wypisanych znaków dodaj długość substringu od ostatniego indexu do pierwszej spacji napotkanej przed wypisanymi znakami + ilością znaków w wierszu +1
            // (aby nie wypisywać dodatkowej spacji na początku zdania)
            wypisaneZnaki += tekst.substr(ostatniIndex, tekst.rfind(' ', wypisaneZnaki + iloscZnakow) - ostatniIndex).length() + 1;
            // za ostatni index przypisz index ostatnio wypisanego znaku
            ostatniIndex = wypisaneZnaki;
        }
    }

    // wypisz ostatnią linię tekstu
    std::cout << "|   " << std::setw(iloscZnakow) << tekst.substr(ostatniIndex) << "   |\n";
}