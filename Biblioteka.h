#pragma once
#include <cassert>
#include <iostream>;
#include <string>
#include "Dane_osobowe.h"
#include "Czytelnik.h"
#include "Ksiazka.h"
#include "Bibliotekarz.h"
#include "Constants.h"

using namespace std;

class Biblioteka {
private:
	friend class Utilities;
	friend class Uzytkownik;
	friend void Bibliotekarz::policz();
public:
	class Dyrektor;
	int liczba_czytelnikow;
	int liczba_bibliotekarzy;
	int liczba_ksiazek;
	Czytelnik** czytelnicy{ nullptr };
	Bibliotekarz** bibliotekarze{ nullptr };
	Ksiazka** ksiazki{ nullptr };
	static Dyrektor dyrektor;
	
	//metody
	Biblioteka();
	Biblioteka(int m_liczba_czytelnikow, int m_liczba_bibliotekarzy, int m_liczba_ksiazek, Czytelnik**& czytelnicy, Bibliotekarz**& bibliotekarze, Ksiazka**& ksiazki);
	Biblioteka(const Biblioteka& m_biblioteka);
	~Biblioteka();
	Biblioteka& operator=(const Biblioteka& m_biblioteka);

	int get_liczba_czytelnikow() { return this->liczba_czytelnikow; }
	void set_liczba_czytelnikow(int liczba_czytelnikow) { this->liczba_czytelnikow = liczba_czytelnikow; }
	int get_liczba_bibliotekarzy() { return this->liczba_bibliotekarzy; }
	void set_liczba_bibliotekarzy(int liczba_bibliotekarzy) { this->liczba_bibliotekarzy = liczba_bibliotekarzy; }
	int get_liczba_ksiazek() { return this->liczba_ksiazek; }
	void set_liczba_ksiazek(int liczba_ksiazek) { this->liczba_ksiazek = liczba_ksiazek; }
	Czytelnik**& get_czytelnicy() { return this->czytelnicy; }
	void set_czytelnik(Czytelnik*& czytelnik, int i) { this->czytelnicy[i] = czytelnik; }
	Bibliotekarz**& get_bibliotekarze() { return this->bibliotekarze; }
	void set_bibliotekarz(Bibliotekarz*& bibliotekarz, int i) { this->bibliotekarze[i] = bibliotekarz; }
	Ksiazka**& get_ksiazki() { return this->ksiazki; }
	void set_ksiazka(Ksiazka*& ksiazka, int i) { this->ksiazki[i] = ksiazka; }
	Ksiazka*& get_ksiazka() { return ksiazki[0]; }

	Ksiazka*& operator[] (int index) { //przeciazenie operatora [] dla tablicy typu Ksiazka
		assert(index >= 0 && index < Constants::rozmiar_ksiazek);
		return ksiazki[index];
	}
	
};
