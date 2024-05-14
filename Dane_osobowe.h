#pragma once
#include <string>
using namespace std;

class Dane_osobowe {
private:
	string nazwa_uzytkownika;
	int rok_urodzenia;
public:
	Dane_osobowe() : nazwa_uzytkownika(""), rok_urodzenia(0) {} 
	Dane_osobowe(string m_nazwa_uzytkownika, int m_rok_urodzenia) : nazwa_uzytkownika(m_nazwa_uzytkownika), rok_urodzenia(m_rok_urodzenia) {}
	Dane_osobowe(const Dane_osobowe& m_dane_osobowe) : nazwa_uzytkownika(m_dane_osobowe.nazwa_uzytkownika), rok_urodzenia(m_dane_osobowe.rok_urodzenia) {}
	
	void set_nazwa_uzytkownika(string m_nazwa_uzytkownika) { nazwa_uzytkownika = m_nazwa_uzytkownika; }
	string get_nazwa_uzytkownika() { return nazwa_uzytkownika; }
	void set_rok_urodzenia(int m_rok_urodzenia) { rok_urodzenia = m_rok_urodzenia; }
	int get_rok_urodzenia() { return rok_urodzenia; }
	Dane_osobowe operator=(Dane_osobowe m_dane_osobowe) {
		if (this == &m_dane_osobowe) return *this;
		nazwa_uzytkownika = m_dane_osobowe.nazwa_uzytkownika;
		rok_urodzenia = m_dane_osobowe.rok_urodzenia;
		return *this;
	}
};