#include "headers/wygladAplikacji.h"
#include <iostream>
#include <windows.h>
#include <cmath>

int main()
{
    // wlączenie konsoli w trybie pełnoekranowym
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    // ustalenie wymiarów consoli (w znakach)
    int znakiNaWiersz = 142;
    int znakiNaKolumne = 44;

    // pobranie danych monitora
    HWND aktywneOkno = GetActiveWindow();
    HMONITOR aktywnyMonitor = MonitorFromWindow(aktywneOkno, MONITOR_DEFAULTTONEAREST);
    MONITORINFO monitorInfo{};
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(aktywnyMonitor, &monitorInfo);

    // zmiana czcionki aby miala odpowiednie wymiary zależne od rozdzielczosci monitora
    int wyswietlSzerokosc = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
    int wyswietlWysokosc = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
    CONSOLE_FONT_INFOEX cfi{};
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = static_cast<short>(std::round((float)wyswietlSzerokosc / znakiNaWiersz));
    cfi.dwFontSize.Y = static_cast<short>(std::round((float)wyswietlWysokosc / znakiNaKolumne));
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    // wywołanie pierwszej funkcji
    ekranLogowania();

    return 0;
}