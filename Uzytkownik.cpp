#include <cassert>
#include "Uzytkownik.h"
#include "Ksiazka.h"
#include "Constants.h"
using namespace std;

static int rozmiar_czytelnikow = Constants::rozmiar_czytelnikow;
static int rozmiar_bibliotekarzy = Constants::rozmiar_bibliotekarzy;
static int rozmiar_ksiazek = Constants::rozmiar_ksiazek;

Uzytkownik::Uzytkownik() : id(0), liczba_wypozyczonych(0) {
	dane_osobowe = new Dane_osobowe;
	wypozyczone_ksiazki = new Ksiazka * [rozmiar_ksiazek];
	for (int i = 0; i < rozmiar_ksiazek; i++) {
		wypozyczone_ksiazki[i] = new Ksiazka();
	}
}

Uzytkownik::Uzytkownik(Dane_osobowe& m_dane_osobowe, int m_id, int m_liczba_wypozyczonych, Ksiazka**& m_wypozyczone_ksiazki) {
	id = m_id;
	dane_osobowe = new Dane_osobowe(m_dane_osobowe);
	liczba_wypozyczonych = m_liczba_wypozyczonych;
	wypozyczone_ksiazki = new Ksiazka * [rozmiar_ksiazek];
	for (int i = 0; i < rozmiar_ksiazek; i++) {
		wypozyczone_ksiazki[i] = new Ksiazka(*m_wypozyczone_ksiazki[i]);
	}
}

Uzytkownik::Uzytkownik(const Uzytkownik& m_Uzytkownik) {
	id = m_Uzytkownik.id;
	delete dane_osobowe;
	dane_osobowe = new Dane_osobowe(*m_Uzytkownik.dane_osobowe);
	liczba_wypozyczonych = m_Uzytkownik.liczba_wypozyczonych;
	if (wypozyczone_ksiazki != nullptr) {
		for (int i = 0; i < rozmiar_ksiazek; i++) {
			delete wypozyczone_ksiazki[i];
			wypozyczone_ksiazki[i] = nullptr;
		}
		delete[] wypozyczone_ksiazki;
		wypozyczone_ksiazki = nullptr;
	}
	wypozyczone_ksiazki = new Ksiazka * [rozmiar_ksiazek];
	for (int i = 0; i < rozmiar_ksiazek; i++) {
		wypozyczone_ksiazki[i] = new Ksiazka(*m_Uzytkownik.wypozyczone_ksiazki[i]);
	}

}

Uzytkownik::~Uzytkownik() {
	delete dane_osobowe;
	dane_osobowe = nullptr;
	for (int i = 0; i < rozmiar_ksiazek; i++) {
		wypozyczone_ksiazki[i] = nullptr;
	}
	delete[] wypozyczone_ksiazki;
	wypozyczone_ksiazki = nullptr;
}

void Uzytkownik::policz() {
	cout << "Nie ma tu nic do liczenia." << endl;
}

Uzytkownik Uzytkownik::operator=(const Uzytkownik& m_uzytkownik) {
	if (this == &m_uzytkownik) return *this;
	id = m_uzytkownik.id;
	*dane_osobowe = *(m_uzytkownik.dane_osobowe);
	liczba_wypozyczonych = m_uzytkownik.liczba_wypozyczonych;
	wypozyczone_ksiazki = m_uzytkownik.wypozyczone_ksiazki;
	return *this;
}

Ksiazka*& Uzytkownik::operator[](int index) {
	assert(index >= 0 && index < Constants::rozmiar_ksiazek);
	return wypozyczone_ksiazki[index];
}