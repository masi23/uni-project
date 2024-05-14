#include "Czytelnik.h"
#include "Ksiazka.h"
#include "Dane_osobowe.h"
#include <cassert>
#include <iostream>
#include "Constants.h"
#include <string>
#include <vector>
using namespace std;

Czytelnik::Czytelnik() : Uzytkownik(), liczba_przeczytanych(0), limit_ksiazek(3) {
	
}

Czytelnik::Czytelnik(Dane_osobowe& m_dane_osobowe, int m_id, int m_liczba_wypozyczonych, Ksiazka**& m_wypozyczone_ksiazki,
	int m_liczba_przeczytanych, int m_limit_ksiazek, vector<Ksiazka*>* m_przeczytane_ksiazki/*Ksiazka**& m_przeczytane_ksiazki*/) 
	: Uzytkownik(m_dane_osobowe, m_id, m_liczba_wypozyczonych, m_wypozyczone_ksiazki)  {
	liczba_przeczytanych = m_liczba_przeczytanych;
	limit_ksiazek = m_limit_ksiazek;
	przeczytane_ksiazki = new vector<Ksiazka*>;
	for (int i = 0; i < liczba_przeczytanych; i++) {
		przeczytane_ksiazki->push_back(new Ksiazka(*m_przeczytane_ksiazki->at(i)));
	}
}

Czytelnik::Czytelnik(const Czytelnik& m_czytelnik) : Uzytkownik(m_czytelnik) {
	liczba_przeczytanych = m_czytelnik.liczba_przeczytanych;
	limit_ksiazek = m_czytelnik.limit_ksiazek;
	przeczytane_ksiazki = new vector<Ksiazka*>;
	for (int i = 0; i < liczba_przeczytanych; i++) {
		przeczytane_ksiazki->push_back(new Ksiazka(*m_czytelnik.przeczytane_ksiazki->at(i)));
	}
}

Czytelnik::~Czytelnik() {
	for (int i = 0; i < liczba_przeczytanych; i++) {
		delete przeczytane_ksiazki->at(i);
	}
	delete przeczytane_ksiazki;
	przeczytane_ksiazki = nullptr;
}


ostream& operator<<(ostream& out, Czytelnik*& m_czytelnik) {
	for (int i = 0; i < m_czytelnik->liczba_przeczytanych; i++) {
		out << m_czytelnik->przeczytane_ksiazki->at(i) << endl;
	}
	return out;
}

Czytelnik Czytelnik::operator=(const Czytelnik m_czytelnik) {
	if (this == &m_czytelnik) return *this;
	for (int i = 0; i < liczba_przeczytanych; i++) {
		delete przeczytane_ksiazki->at(i);
		przeczytane_ksiazki->at(i) = nullptr;
	}
	delete przeczytane_ksiazki;
	przeczytane_ksiazki->clear();
	Uzytkownik::operator=(m_czytelnik);
	liczba_przeczytanych = m_czytelnik.liczba_przeczytanych;
	przeczytane_ksiazki = new vector<Ksiazka*>;
	for (int i = 0; i < liczba_przeczytanych; i++) {
		przeczytane_ksiazki->push_back(new Ksiazka(*m_czytelnik.przeczytane_ksiazki->at(i)));
	}
	liczba_przeczytanych = m_czytelnik.liczba_przeczytanych;
	return *this;
}

void Czytelnik::set_liczba_przeczytanych(int m_liczba_przeczytanych) { liczba_przeczytanych = m_liczba_przeczytanych; }

int Czytelnik::get_liczba_przeczytanych() { return liczba_przeczytanych; }

void Czytelnik::set_limit_ksiazek(int m_limit_ksiazek) { limit_ksiazek = m_limit_ksiazek; }

int Czytelnik::get_limit_ksiazek() { return limit_ksiazek; }

void Czytelnik::set_przeczytane_ksiazki(Ksiazka**& m_ksiazki, int m_liczba_przeczytanych) {
	assert(m_liczba_przeczytanych <= liczba_przeczytanych);
	if (przeczytane_ksiazki == nullptr) {
		przeczytane_ksiazki = new vector<Ksiazka*>;
	}
	for (int i = 0; i < m_liczba_przeczytanych; i++) {
		przeczytane_ksiazki->push_back(m_ksiazki[i]);
	}
}

void Czytelnik::set_przeczytana_ksiazka(Ksiazka*& m_ksiazka, int m_index) {
	assert(m_index < liczba_przeczytanych);
	if (przeczytane_ksiazki->at(m_index) == nullptr) {
		przeczytane_ksiazki->push_back(new Ksiazka(*m_ksiazka));
	}
	else {
		*przeczytane_ksiazki->at(m_index) = *m_ksiazka;
	}
}

vector<Ksiazka*>*& Czytelnik::get_przeczytane_ksiazki() {
	return przeczytane_ksiazki;
}

void Czytelnik::dodaj_ksiazke(Ksiazka*& m_ksiazka) {
	vector<Ksiazka*>* tmp_ksiazki = new vector<Ksiazka*>;
	for (int i = 0; i < liczba_przeczytanych; i++) {
		tmp_ksiazki->push_back(new Ksiazka(*przeczytane_ksiazki->at(i)));
	}
	tmp_ksiazki->push_back(new Ksiazka(*m_ksiazka));
	for (int i = 0; i < liczba_przeczytanych; i++) {
		delete przeczytane_ksiazki->at(i);
	}
	delete przeczytane_ksiazki;
	przeczytane_ksiazki = tmp_ksiazki;
	liczba_przeczytanych++;
}

void Czytelnik::wyswietl_statystyki() {
	if (liczba_przeczytanych < 1) {
		cout << "Brak danych. Wypozycz jakas ksiazke" << endl;
		return;
	}
	Statystyki* statystyki = new Statystyki[liczba_przeczytanych];
	int i = 0; //iteracja po ksiazkach 
	int j = 0; //iteracja po statystykach

	while (i < liczba_przeczytanych) {
		bool znaleziono = false;
		if (i == 0) {
			statystyki[0].kategoria = przeczytane_ksiazki->at(i)->get_kategoria();
			statystyki[0].liczba += 1;
			j++;
			i++;
			continue;
		}
		for (int k = 0; k < j; k++) {
			if (statystyki[k].kategoria == przeczytane_ksiazki->at(i)->get_kategoria()) {
				znaleziono = true;
				statystyki[k].liczba += 1;
				break;
			}
		}

		if (!znaleziono) {
			statystyki[j].kategoria = przeczytane_ksiazki->at(i)->get_kategoria();
			statystyki[j].liczba += 1;
			j++;
		}
		i++;
	}

	statystyki->sortuj(statystyki, j);

	cout << "Twoje ulubione kategorie to: " << endl;
	int k = 0;
	for (k; k < j; k++) {
		cout << statystyki[k].kategoria << endl;
		cout << "Przeczytano: " << statystyki[k].liczba << endl << endl;
		if (k == 2) break;
	}
	while (statystyki[k].liczba == statystyki[k + 1].liczba) {
		k++;
		cout << statystyki[k].kategoria << endl;
		cout << "Przeczytano: " << statystyki[k].liczba << endl << endl;
	}
	delete[] statystyki;
	statystyki = nullptr;
}

void Czytelnik::policz() {
	int ilosc;
	ilosc = limit_ksiazek - this->get_liczba_wypozyczonych();
	if (ilosc == 0) {
		cout << "Wykorzystales swoj limit. Nie mozesz wypozyczyc wiecej ksiazek" << endl;
		cout << "Sprobuj najpierw cos zwrocic" << endl;
	}
	else {
		cout << "Mozesz wypozyczyc jeszcze " << ilosc << " ksiazek" << endl;
		cout << "Do dziela! " << endl;
	}
}

//Biblioteka::Ksiazka*& Czytelnik::operator[](int index) {
//	assert(index >= 0 && index < Biblioteka::rozmiar_ksiazek);
//	return wypozyczone_ksiazki[index];
//}

void Statystyki::sortuj(Statystyki* m_statystyki, int m_rozmiar) {
	for (int i = 0; i < m_rozmiar; i++) {
		for (int j = 0; j < m_rozmiar - i; j++) {
			if (m_statystyki[j].liczba < m_statystyki[j + 1].liczba) {
				Statystyki tmp_statystyki;
				tmp_statystyki.kategoria = m_statystyki[j].kategoria;
				tmp_statystyki.liczba = m_statystyki[j].liczba;
				m_statystyki[j] = m_statystyki[j + 1];
				m_statystyki[j + 1] = tmp_statystyki;
			}
		}
	}
}