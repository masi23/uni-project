#pragma once
#include "Uzytkownik.h"
#include "Ksiazka.h"
#include <iostream>
#include <vector>

using namespace std;

struct Statystyki {
	string kategoria;
	int liczba = 0;
	void sortuj(Statystyki* m_statystyki, int m_rozmiar);
};

class Czytelnik final : public Uzytkownik {
private:
	int liczba_przeczytanych;
	int limit_ksiazek;
	vector<Ksiazka*>* przeczytane_ksiazki{ nullptr };
public:
	Czytelnik();
	Czytelnik(Dane_osobowe& m_dane_osobowe, int m_id, int m_liczba_wypozyczonych, Ksiazka**& m_wypozyczone_ksiazki, 
		int m_liczba_przeczytanych, int m_limit_ksiazek, vector<Ksiazka*>* m_przeczytane_ksiazki/*Ksiazka**& m_przeczytane_ksiazki*/);
	Czytelnik(const Czytelnik& m_czytelnik);
	~Czytelnik();
	friend ostream& operator<<(ostream& out, Czytelnik*& m_czytelnik);
	Czytelnik operator=(const Czytelnik m_czytelnik);

	void set_liczba_przeczytanych(int m_liczba_przeczytanych);
	int get_liczba_przeczytanych();
	void set_limit_ksiazek(int m_limit_ksiazek);
	int get_limit_ksiazek();
	void set_przeczytane_ksiazki(Ksiazka**& m_ksiazki, int m_liczba_przeczytanych);
	void set_przeczytana_ksiazka(Ksiazka*& m_ksiazka, int m_index);
	vector<Ksiazka*>*& get_przeczytane_ksiazki();
	void dodaj_ksiazke(Ksiazka*& m_ksiazka);
	void wyswietl_statystyki();
	void policz() override; //liczy ilosc ksiazek ktora mozna jeszcze wypozyczyc
};