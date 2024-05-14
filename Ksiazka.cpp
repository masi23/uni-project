#include "Ksiazka.h"
#include <iostream>
using namespace std;

Ksiazka::Ksiazka() : id(0), tytul(""), autor(""), rok_wydania(0), kategoria(""), dostepnosc(true) {}

Ksiazka::Ksiazka(int m_id, string m_tytul, string m_autor, int m_rok_wydania, string m_kategoria, bool m_dostepnosc) {
	id = m_id;
	tytul = m_tytul;
	autor = m_autor;
	rok_wydania = m_rok_wydania;
	kategoria = m_kategoria;
	dostepnosc = m_dostepnosc;
}

Ksiazka::Ksiazka(const Ksiazka& m_ksiazka) {
	id = m_ksiazka.id;
	tytul = m_ksiazka.tytul;
	autor = m_ksiazka.autor;
	rok_wydania = m_ksiazka.rok_wydania;
	kategoria = m_ksiazka.kategoria;
	dostepnosc = m_ksiazka.dostepnosc;
}

Ksiazka& Ksiazka::operator=(const Ksiazka& m_ksiazka) {
	if (this == &m_ksiazka) return *this;
	id = m_ksiazka.id;
	tytul = m_ksiazka.tytul;
	autor = m_ksiazka.autor;
	rok_wydania = m_ksiazka.rok_wydania;
	kategoria = m_ksiazka.kategoria;
	dostepnosc = m_ksiazka.dostepnosc;
	return *this;
}

ostream& operator<<(ostream& out, Ksiazka*& ksiazka) { //definicja przeciazonego operatora <<
	out << "ID: " << ksiazka->get_id() << endl;
	out << "Tytul: " << ksiazka->tytul << endl;
	out << "Autor: " << ksiazka->get_autor() << endl;
	out << "Rok wydania: " << ksiazka->get_rok_wydania() << endl;
	out << "Kategoria: " << ksiazka->get_kategoria() << endl;
	out << "Dostepnosc: " << ksiazka->get_dostepnosc() << endl;
	return out;
}
