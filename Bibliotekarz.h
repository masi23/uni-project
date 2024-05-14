#pragma once
#include <cassert>
#include "Ksiazka.h"
#include "Constants.h"
#include "Dane_osobowe.h"
#include "Uzytkownik.h"

using namespace std;

class Bibliotekarz final : public Uzytkownik{
private:
	int suma_wypozyczonych;
	int zaplata_za_wypozyczenie;
public:
	Bibliotekarz();
	Bibliotekarz(Dane_osobowe& m_dane_osobowe, int m_id, int m_liczba_wypozyczonych, Ksiazka**& m_wypozyczone_ksiazki, 
		int m_suma_wypozyczonych, int m_zaplata_za_wypozyczenie);
	Bibliotekarz(const Bibliotekarz& m_bibliotekarz);
	void set_suma_wypozyczonych(int m_suma);
	int get_suma_wypozyczonych();
	void set_zaplata_za_wypozyczenie(int m_zaplata);
	int get_zaplata_za_wypozyczenie();
	void policz() override; 

	~Bibliotekarz();

	//Ksiazka*& operator[](int index) {
	//	assert(index >= 0 && index < Constants::rozmiar_ksiazek);
	//	return wydane_ksiazki[index];
	//}
};