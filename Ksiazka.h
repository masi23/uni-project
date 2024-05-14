#pragma once
#include <iostream>
#include <string>
//#include "Biblioteka.h"
using namespace std;

class Ksiazka {
private:
	//friend class Biblioteka;
	mutable int id;
	mutable string tytul;
	mutable string autor;
	mutable int rok_wydania;
	mutable string kategoria;
	mutable bool dostepnosc = false;
public:
	Ksiazka();
	Ksiazka(int m_id, string m_tytul, string m_autor, int m_rok_wydania, string m_kategoria, bool m_dostepnosc);
	Ksiazka(const Ksiazka& m_ksiazka);
	void set_id(int id) { this->id = id; }
	int get_id() { return this->id; }
	int get_id() const { return id; }
	void set_tytul(string tytul) { this->tytul = tytul; }
	string get_tytul() { return this->tytul; }
	string get_tytul() const { return tytul; }
	void set_autor(string autor) { this->autor = autor; }
	string get_autor() { return this->autor; }
	string get_autor() const { return autor; }
	void set_rok_wydania(int rok_wydania) { this->rok_wydania = rok_wydania; }
	int get_rok_wydania() { return this->rok_wydania; }
	int get_rok_wydania() const { return rok_wydania; }
	void set_kategoria(string kategoria) { this->kategoria = kategoria; }
	string get_kategoria() { return this->kategoria; }
	string get_kategoria() const { return kategoria; }
	void set_dostepnosc(bool dostepnosc) { this->dostepnosc = dostepnosc; }
	bool get_dostepnosc() { return this->dostepnosc; }
	bool get_dostepnosc() const { return dostepnosc; }

	Ksiazka& operator=(const Ksiazka& m_ksiazka);

	friend ostream& operator<<(ostream& out, Ksiazka*& ksiazka);

	friend istream& operator>>(istream& in, Ksiazka*& ksiazka) {
		string input;
		cout << "Wpisz dane ksiazki wedlug ponizszego schematu" << endl;
		cout << "ID; Tytul; Autor; Rok_wydania; Kategoria;" << endl;
		cin >> input;
		string bufor[5];
		int j = 0;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] != ';') {
				if ((j == 0 || j == 3) && !isdigit(input[i]) && !isspace(input[i])) {
					cout << "Wprowadzono niepoprawne dane" << endl;
					getchar();
					return in;
				}
				if ((j == 1 || j == 2 || j == 4) && isdigit(input[i])) {
					cout << "Wprowadzono niepoprawne dane" << endl;
					getchar();
					return in;
				}
				bufor[j] += input[i];
			}
			else if (j < 4) {
				j++;
			}
			if (isspace(bufor[j][0])) bufor[j].erase(0, 1);
		}
		if (!bufor[0].empty()) ksiazka->set_id(stoi(bufor[0]));
		if (!bufor[1].empty()) ksiazka->set_tytul(bufor[1]);
		if (!bufor[2].empty()) ksiazka->set_autor(bufor[2]);
		if (!bufor[3].empty()) ksiazka->set_rok_wydania(stoi(bufor[3]));
		if (!bufor[4].empty()) ksiazka->set_kategoria(bufor[4]);
		return in;
	}

};