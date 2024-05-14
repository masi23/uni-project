#include "Bibliotekarz.h"
#include "Ksiazka.h"
#include "Dane_osobowe.h"
#include "Uzytkownik.h"
#include "Constants.h"
using namespace std;

static int rozmiar_ksiazek = Constants::rozmiar_ksiazek;

Bibliotekarz::Bibliotekarz() : Uzytkownik(), suma_wypozyczonych(0), zaplata_za_wypozyczenie(20) {
}

Bibliotekarz::Bibliotekarz(Dane_osobowe& m_dane_osobowe, int m_id, int m_liczba_wypozyczonych, Ksiazka**& m_wypozyczone_ksiazki, int m_suma_wypozyczonych, int m_zaplata_za_wypozyczenie)
	: Uzytkownik(m_dane_osobowe, m_id, m_liczba_wypozyczonych, m_wypozyczone_ksiazki) {
	suma_wypozyczonych = m_suma_wypozyczonych;
	zaplata_za_wypozyczenie = m_zaplata_za_wypozyczenie;
}

Bibliotekarz::Bibliotekarz(const Bibliotekarz& m_bibliotekarz) : Uzytkownik(m_bibliotekarz) {
	suma_wypozyczonych = m_bibliotekarz.suma_wypozyczonych;
	zaplata_za_wypozyczenie = m_bibliotekarz.zaplata_za_wypozyczenie;
}

void Bibliotekarz::set_suma_wypozyczonych(int m_suma) { suma_wypozyczonych = m_suma; }
int Bibliotekarz::get_suma_wypozyczonych() { return suma_wypozyczonych; }

void Bibliotekarz::set_zaplata_za_wypozyczenie(int m_zaplata) { zaplata_za_wypozyczenie = m_zaplata; }
int Bibliotekarz::get_zaplata_za_wypozyczenie() { return zaplata_za_wypozyczenie; }

void Bibliotekarz::policz() {
	int wynagrodzenie;
	wynagrodzenie = suma_wypozyczonych * zaplata_za_wypozyczenie;
	cout << "Nalezne wynagrodzenie to: " << suma_wypozyczonych << "zl" << endl;
}

Bibliotekarz::~Bibliotekarz() {}