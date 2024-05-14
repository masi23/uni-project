#pragma once
#include <cassert>
#include "Dane_osobowe.h"
#include "Ksiazka.h"

using namespace std;

class Uzytkownik {
private:
	int id;
	Dane_osobowe* dane_osobowe{ nullptr };
	int liczba_wypozyczonych;
	Ksiazka** wypozyczone_ksiazki{ nullptr };
public:
	Uzytkownik();
	Uzytkownik(Dane_osobowe& m_dane_osobowe, int m_id, int m_liczba_wypozyczonych, Ksiazka**& m_wypozyczone_ksiazki);
	Uzytkownik(const Uzytkownik& m_Uzytkownik);
	virtual ~Uzytkownik();

	void set_id(int id) { this->id = id; }
	int get_id() { return this->id; }
	void set_dane_osobowe(Dane_osobowe* dane_osobowe) { this->dane_osobowe = dane_osobowe; }
	Dane_osobowe*& get_dane_osobowe() { return dane_osobowe; }
	void set_liczba_wypozyczonych(int liczba_wypozyczonych) { this->liczba_wypozyczonych = liczba_wypozyczonych; }
	int& get_liczba_wypozyczonych() { return this->liczba_wypozyczonych; }
	//void set_wypozyczone_ksiazki(Ksiazka**& wypozyczone_ksiazki) { this->wypozyczone_ksiazki = wypozyczone_ksiazki; }
	void set_wypozyczona_ksiazka(Ksiazka*& wypozyczona_ksiazka, int i) { this->wypozyczone_ksiazki[i] = wypozyczona_ksiazka; }
	Ksiazka**& get_wypozyczone_ksiazki() { return this->wypozyczone_ksiazki; }

	virtual void policz();

	Uzytkownik operator=(const Uzytkownik& m_uzytkownik);
	Ksiazka*& operator[](int index);
};