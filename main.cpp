#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <random>
#include "Dane_osobowe.h"
#include "Ksiazka.h"
#include "Czytelnik.h"
#include "Bibliotekarz.h"
#include "Uzytkownik.h"
#include "Biblioteka.h"
#include "Constants.h"

using namespace std;

static const int rozmiar_czytelnikow = Constants::rozmiar_czytelnikow;
static const int rozmiar_bibliotekarzy = Constants::rozmiar_bibliotekarzy;
static const int rozmiar_ksiazek = Constants::rozmiar_ksiazek;

class Utilities {
public:
	static void stworz(Ksiazka**& ksiazki, const int& rozmiar);
	static void stworz(Ksiazka*& ksiazka);
	static void stworz(Czytelnik**& czytelnicy, const int& rozmiar);
	static void stworz(Bibliotekarz**& bibliotekarze, const int& rozmiar);

	static void dodaj(Ksiazka**& ksiazki, const int& rozmiar);
	static void dodaj(Czytelnik**& czytelnicy, const int& rozmiar);
	static void dodaj(Bibliotekarz**& bibliotekarze, const int& rozmiar);

	static int generuj(int przedzial_od, int przedzial_do); //generuje liczby z podanego przedzialu
	static void generuj(Czytelnik**& czytelnicy, const int& rozmiar);
	static void generuj(Dane_osobowe*& dane_osobowe);
	static void generuj(Ksiazka**& ksiazki, const int& rozmiar);
	static void generuj(Bibliotekarz**& bibliotekarze, const int& rozmiar);

	static void wczytaj_dane(Czytelnik*& czytelnik);
	static void wczytaj_dane(Bibliotekarz*& bibliotekarz);
	static void wczytaj_dane(Ksiazka*& ksiazka);

	static void usun(Ksiazka**& ksiazki, const int& rozmiar);
	static void usun(Ksiazka*& ksiazka);
	static void usun(Czytelnik**& czytelnicy, const int& rozmiar);
	static void usun(Bibliotekarz**& bibliotekarze, const int& rozmiar);

	static int wyswietl(Ksiazka**& ksiazka, const int& rozmiar); //zwraca liczbe wyswietlonych ksiazek
	static void wyswietl(Bibliotekarz**& bibliotekarze, const int& rozmiar);
	static void wyswietl(Ksiazka**& ksiazka, int& liczba_ksiazek);
	static void wyswietl(Czytelnik**& czytelnicy, const int& rozmiar);

	static int znajdz_ksiazke(Ksiazka**& ksiazki, int id, const int& rozmiar); //zwraca index elementu tablicy dla obiektu o podanym id 
	static void wypozycz_ksiazke(Biblioteka& biblioteka, int index_ksiazki, int index_czytelnika, int index_bibliotekarza, const int& rozmiar);
	static void oddaj_ksiazke(Biblioteka& biblioteka, int index_czytelnika, int index_bibliotekarza, int& wybrane_id, const int& rozmiar);
};

void stworz(Biblioteka*& biblioteka);
void usun(Biblioteka*& biblioteka);

string_view imiona[]{ "Andrzej", "Adam", "Maciek", "Robert", "Agnieszka",
	"Jadwiga", "Rozalia", "Klementyna", "Michal", "Krzysztof" };

string_view nazwiska[]{ "Kowalski", "Nowak", "Chrzan", "Marchewka", "Mieszko",
	"Chrobry", "Kielbasa", "Barabasz", "Burak", "Wozniak" };

string_view tytuly[]{ "Wladca Pierscieni", "W pustyni i w puszczy", "Buszujacy w zbozu",
	"Duma i uprzedzenie", "Harry Potter", "Lalka", "Zemsta", "Dziady", "Hrabia Monte Christo", "Diuna" };

string_view kategorie[]{ "Fantasy", "Science Fiction", "Romans", "Kryminal", "Biografia",
	"Horror", "Bajka", "Dramat", "Literatura piekna", "Literatura obca" };

int main() {

	bool program_wlaczony = true;
	int wybrana_opcja, wybrane_id;
	Biblioteka* biblioteka{ nullptr };
	biblioteka = new Biblioteka();
	//stworz(biblioteka);
	/*Utilities::stworz(biblioteka->get_bibliotekarze(), Biblioteka::rozmiar_bibliotekarzy);

	for (int i = 0; i < Biblioteka::rozmiar_bibliotekarzy; i++) {
		Utilities::stworz(biblioteka->get_bibliotekarze()[i]->get_wypozyczone_ksiazki(), Biblioteka::rozmiar_ksiazek);
	}

	Utilities::stworz(biblioteka->get_czytelnicy(), Biblioteka::rozmiar_czytelnikow);
	for (int i = 0; i < Biblioteka::rozmiar_czytelnikow; i++) {
		Utilities::stworz(biblioteka->get_czytelnicy()[i]->get_wypozyczone_ksiazki(), Biblioteka::rozmiar_ksiazek);
	}

	Utilities::stworz(biblioteka->get_ksiazki(), Biblioteka::rozmiar_ksiazek);*/
	//Biblioteka::stworz_dyrektora();

	while (program_wlaczony) {
		system("cls");
		cout << ">> BIBLIOTEKA <<" << endl;
		cout << "1: Wypozycz ksiazke" << endl;
		cout << "2: Oddaj ksiazke" << endl;
		cout << "3: Generuj dane" << endl;
		cout << "4: Wczytaj dane" << endl;
		cout << "5: Pokaz ulubione kategorie" << endl;
		cout << "6: Policz..." << endl;
		cout << "0: Wyjdz z programu" << endl;
		cin >> wybrana_opcja;
		switch (wybrana_opcja) {
		case 1: //wypozycz ksiazke
		{
			system("cls");
			cout << "Wpisz numer Id wybranej ksiazki z listy" << endl;
			int liczba_wyswietlanych = Utilities::wyswietl(biblioteka->get_ksiazki(), rozmiar_ksiazek);
			if (liczba_wyswietlanych <= 0) {
				cout << "Brak ksiazek do wyswietlenia" << endl;
				cout << "Nacisnij dowolny przycisk aby kontynuowac..." << endl;
				getchar();
				break;
			}
			cin >> wybrane_id;
			int index = Utilities::znajdz_ksiazke(biblioteka->get_ksiazki(), wybrane_id, rozmiar_ksiazek);
			if (index >= 0) {
				Utilities::wypozycz_ksiazke(*biblioteka, index, 0, 0, rozmiar_ksiazek);
				system("cls");
				cout << "Wypozyczone ksiazki czytelnika o Id: " << biblioteka->get_czytelnicy()[0]->get_id() << endl;
				Utilities::wyswietl(biblioteka->get_czytelnicy()[0]->get_wypozyczone_ksiazki(), biblioteka->get_czytelnicy()[0]->get_liczba_wypozyczonych());
				cout << "Nacisnij dowolny przycisk aby kontynuowac..." << endl;
			}
			else {
				cout << "Ksiazka o ID:  " << wybrane_id << " nie istnieje" << endl;
			}
			getchar();
			getchar();
		}
		break;
		case 2: //oddaj ksiazke
		{
			system("cls");
			if (biblioteka->get_czytelnicy()[0]->get_liczba_wypozyczonych() > 0) {
				cout << "Wybierz Id ksiazki, ktora chcesz oddac " << endl;
				Utilities::wyswietl(biblioteka->get_czytelnicy()[0]->get_wypozyczone_ksiazki(), biblioteka->get_czytelnicy()[0]->get_liczba_wypozyczonych());
				cin >> wybrane_id;
				Utilities::oddaj_ksiazke(*biblioteka, 0, 0, wybrane_id, rozmiar_ksiazek);
			}
			else {
				cout << "Brak ksiazek do wyswietlenia" << endl;
				cout << "Nacisnij dowolny przycisk aby kontynuowac..." << endl;
			}
			getchar();
			getchar();
		}
		break;
		case 3: //generuj dane
		{
			Utilities::generuj(biblioteka->get_ksiazki(), rozmiar_ksiazek);
			Utilities::generuj(biblioteka->get_czytelnicy(), rozmiar_czytelnikow);
			Utilities::generuj(biblioteka->get_bibliotekarze(), rozmiar_bibliotekarzy);
			Utilities::wyswietl(biblioteka->get_ksiazki(), rozmiar_ksiazek);
			Utilities::wyswietl(biblioteka->get_czytelnicy(), rozmiar_czytelnikow);
			Utilities::wyswietl(biblioteka->get_bibliotekarze(), rozmiar_bibliotekarzy);
			getchar();
			getchar();
		}
		break;
		case 4: //wczytaj dane
		{
			system("cls");
			cout << "Wybierz jakiego typu dane chcesz wprowadzic" << endl;
			cout << "1: Czytelnik" << endl;
			cout << "2: Bibliotekarz" << endl;
			cout << "3: Ksiazka" << endl;
			int choice;
			cin >> choice;
			cin.ignore();
			switch (choice) {
			case 1:
				Utilities::wczytaj_dane(biblioteka->get_czytelnicy()[0]);
				Utilities::wyswietl(biblioteka->get_czytelnicy(), rozmiar_czytelnikow);
				break;
			case 2:
				Utilities::wczytaj_dane(biblioteka->get_bibliotekarze()[0]);
				Utilities::wyswietl(biblioteka->get_bibliotekarze(), rozmiar_bibliotekarzy);
				break;
			case 3:
				//Utilities::wczytaj_dane(biblioteka->get_ksiazki()[0]);
				//Utilities::wczytaj_dane((*biblioteka)[0]); //uzycie operatora [] do wybrania ksiazki[0]
				cin >> biblioteka->get_ksiazki()[0];
				Utilities::wyswietl(biblioteka->get_ksiazki(), rozmiar_ksiazek);
				break;
			}
			getchar();
		}
		break;
		case 5: //pokaz ulubione kategorie
		{
			biblioteka->czytelnicy[0]->wyswietl_statystyki();
			getchar();
			getchar();
		}
		break;
		case 6:
		{
			Uzytkownik* uzytkownik[3];
			uzytkownik[0] = new Uzytkownik();
			uzytkownik[1] = new Czytelnik();
			uzytkownik[2] = new Bibliotekarz();

			for (int i = 0; i < 3; i++) {
				uzytkownik[i]->policz();
				cout << endl;
			}

			getchar();
			getchar();
		}
		break;
		case 0: //wyjdz z programu
		{
			/*Utilities::usun(biblioteka->get_bibliotekarze(), Biblioteka::rozmiar_bibliotekarzy);
			Utilities::usun(biblioteka->get_czytelnicy(), Biblioteka::rozmiar_czytelnikow);
			Utilities::usun(biblioteka->get_ksiazki(), Biblioteka::rozmiar_ksiazek);*/
			//Biblioteka::usun_dyrektora();
			delete biblioteka;
			biblioteka = nullptr;
			program_wlaczony = false;
		}
		break;
		}
	}
}

/*-------------STWORZ-------------*/
void stworz(Biblioteka*& biblioteka) {
	biblioteka = new Biblioteka;
}

void Utilities::stworz(Ksiazka*& ksiazka) {
	ksiazka = new Ksiazka;
}

void Utilities::stworz(Ksiazka**& ksiazki, const int& rozmiar)
{
	ksiazki = new Ksiazka * [rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		ksiazki[i] = new Ksiazka;
	}
}

void Utilities::stworz(Czytelnik**& czytelnicy, const int& rozmiar)
{
	Dane_osobowe dane;
	czytelnicy = new Czytelnik * [rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		czytelnicy[i] = new Czytelnik;
		czytelnicy[i]->get_dane_osobowe() = new Dane_osobowe(dane); //uzycie konstruktora kopiujacego
	}
}

void Utilities::stworz(Bibliotekarz**& bibliotekarze, const int& rozmiar)
{
	bibliotekarze = new Bibliotekarz * [rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		bibliotekarze[i] = new Bibliotekarz;
		bibliotekarze[i]->set_dane_osobowe(new Dane_osobowe);
	}
}

/*-------------USUN-------------*/
void usun(Biblioteka*& biblioteka) {
	delete biblioteka;
	biblioteka = nullptr;
}

void Utilities::usun(Ksiazka*& ksiazka) {
	delete ksiazka;
	ksiazka = nullptr;
}

void Utilities::usun(Ksiazka**& ksiazki, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		delete ksiazki[i];
		ksiazki[i] = nullptr;
	}
	delete[] ksiazki;
	ksiazki = nullptr;
}

void Utilities::usun(Czytelnik**& czytelnicy, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		delete czytelnicy[i];
		czytelnicy[i] = nullptr;
	}
	delete[] czytelnicy;
	czytelnicy = nullptr;
}

void Utilities::usun(Bibliotekarz**& bibliotekarze, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		delete bibliotekarze[i];
		bibliotekarze[i] = nullptr;
	}
	delete[] bibliotekarze;
	bibliotekarze = nullptr;
}



/*-------------DODAJ-------------*/
void Utilities::dodaj(Ksiazka**& ksiazki, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		ksiazki[i]->set_id(i);
		ksiazki[i]->set_tytul("Wladca Pierscieni");
		ksiazki[i]->set_autor("J.R.R. Tolkien");
		ksiazki[i]->set_rok_wydania(2012);
		ksiazki[i]->set_kategoria("Fantasy");
		ksiazki[i]->set_dostepnosc(true);
	}
}

void Utilities::dodaj(Czytelnik**& czytelnicy, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		czytelnicy[i]->set_id(1);
		czytelnicy[i]->get_dane_osobowe()->set_nazwa_uzytkownika("Andrzej");
		czytelnicy[i]->get_dane_osobowe()->set_rok_urodzenia(2000);
		czytelnicy[i]->set_liczba_przeczytanych(0);
		czytelnicy[i]->set_liczba_wypozyczonych(0);
	}
}

void Utilities::dodaj(Bibliotekarz**& bibliotekarze, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		bibliotekarze[i]->set_id(i);
		bibliotekarze[i]->get_dane_osobowe()->set_nazwa_uzytkownika("Mariusz");
		bibliotekarze[i]->get_dane_osobowe()->set_rok_urodzenia(1999);
		bibliotekarze[i]->set_liczba_wypozyczonych(0);
	}
}

/*-------------GENERUJ-------------*/
int Utilities::generuj(int przedzial_od, int przedzial_do) {
	random_device rd;
	default_random_engine dfe(rd());
	uniform_int_distribution<int> dist(przedzial_od, przedzial_do);
	return dist(dfe);
}

void Utilities::generuj(Dane_osobowe*& dane_osobowe) {
	int i, j;
	i = generuj(0, 9);
	j = generuj(0, 9);
	string nazwa = string(imiona[i]) + " " + string(nazwiska[i]);
	dane_osobowe->set_nazwa_uzytkownika(nazwa);
	int rok;
	rok = generuj(1920, 2006);
	dane_osobowe->set_rok_urodzenia(rok);
}

void Utilities::generuj(Ksiazka**& ksiazki, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		delete ksiazki[i];
	}
	delete[] ksiazki;
	ksiazki = new Ksiazka * [rozmiar];
	for (int i = 0; i < rozmiar; i++) ksiazki[i] = new Ksiazka;

	int m, n, k, t;
	int* zajete_id = new int[rozmiar];
	int temp_id;
	bool powtorzenie;

	for (int i = 0; i < rozmiar; i++) {
		do {
			temp_id = generuj(0, 99);
			powtorzenie = false;
			for (int j = 0; j < rozmiar; j++) {
				if (zajete_id[j] == temp_id) {
					powtorzenie = true;
					break;
				}
			}
		} while (powtorzenie);
		zajete_id[i] = temp_id;
		ksiazki[i]->set_id(temp_id);
		t = generuj(0, 9);
		m = generuj(0, 9);
		n = generuj(0, 9);
		k = generuj(0, 9);
		ksiazki[i]->set_tytul(string(tytuly[t]));
		ksiazki[i]->set_autor(string(imiona[m]) + " " + string(nazwiska[n]));
		ksiazki[i]->set_kategoria(string(kategorie[k]));
		ksiazki[i]->set_rok_wydania(generuj(1900, 2024));
		ksiazki[i]->set_dostepnosc(true);
	}
	delete[] zajete_id;
	zajete_id = nullptr;
}

void Utilities::generuj(Czytelnik**& czytelnicy, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		delete czytelnicy[i];
	}
	delete[] czytelnicy;
	czytelnicy = new Czytelnik * [rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		czytelnicy[i] = new Czytelnik;
	}
	int* zajete_id = new int[rozmiar];
	int temp_id;
	bool powtorzenie;
	for (int i = 0; i < rozmiar; i++) {
		do {
			temp_id = generuj(0, 99);
			powtorzenie = false;
			for (int j = 0; j < sizeof(zajete_id); j++) {
				if (zajete_id[j] == temp_id) {
					powtorzenie = true;
					break;
				}
			}
		} while (powtorzenie);
		zajete_id[i] = temp_id;
		czytelnicy[i]->set_id(temp_id);
		generuj(czytelnicy[i]->get_dane_osobowe());
		czytelnicy[i]->set_liczba_przeczytanych(0);
		czytelnicy[i]->set_liczba_wypozyczonych(0);
	}
	delete[] zajete_id;
	zajete_id = nullptr;
}

void Utilities::generuj(Bibliotekarz**& bibliotekarze, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) delete bibliotekarze[i];
	delete[] bibliotekarze;
	bibliotekarze = new Bibliotekarz * [rozmiar];
	for (int i = 0; i < rozmiar; i++) bibliotekarze[i] = new Bibliotekarz;
	int* zajete_id;
	zajete_id = new int[rozmiar];
	int temp_id;
	bool powtorzenie;
	for (int i = 0; i < rozmiar; i++) {
		do {
			temp_id = generuj(0, 99);
			powtorzenie = false;
			for (int j = 0; j < sizeof(zajete_id); j++) {
				if (zajete_id[j] == temp_id) {
					powtorzenie = true;
					break;
				}
			}
		} while (powtorzenie);
		zajete_id[i] = temp_id;
		bibliotekarze[i]->set_id(temp_id);
		generuj(bibliotekarze[i]->get_dane_osobowe());
		bibliotekarze[i]->set_liczba_wypozyczonych(0);
	}
	delete[] zajete_id;
	zajete_id = nullptr;
}

/*-------------WCZYTAJ DANE-------------*/
void Utilities::wczytaj_dane(Czytelnik*& czytelnik) {
	string input;
	cout << "Wpisz dane czytelnika wedlug ponizszego schematu" << endl;
	cout << "ID; Nazwa_czytelnika; Rok_urodzenia;" << endl;
	getline(cin, input);
	string bufor[3];
	int j = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ';') {
			if ((j == 0 || j == 2) && !isdigit(input[i]) && !isspace(input[i])) {
				cout << "Wprowadzono niepoprawne dane" << endl;
				getchar();
				return;
			}
			if (j == 1 && isdigit(input[i])) {
				cout << "Wprowadzono niepoprawne dane" << endl;
				getchar();
				return;
			}
			bufor[j] += input[i];

		}
		else if (j < 2) {
			j++;
		}
		if (isspace(bufor[j][0])) bufor[j].erase(0, 1);
	}
	if (!bufor[0].empty()) czytelnik->set_id(stoi(bufor[0]));
	if (!bufor[1].empty()) czytelnik->get_dane_osobowe()->set_nazwa_uzytkownika(bufor[1]);
	if (!bufor[2].empty()) czytelnik->get_dane_osobowe()->set_rok_urodzenia(stoi(bufor[2]));
}

void Utilities::wczytaj_dane(Bibliotekarz*& bibliotekarz) {
	string input;
	cout << "Wpisz dane bibliotekarza wedlug ponizszego schematu" << endl;
	cout << "ID; Nazwa_bibliotekarza; Rok_urodzenia;" << endl;
	getline(cin, input);
	string bufor[3];
	int j = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ';') {
			if ((j == 0 || j == 2) && !isdigit(input[i]) && !isspace(input[i])) {
				cout << "Wprowadzono niepoprawne dane" << endl;
				getchar();
				return;
			}
			if (j == 1 && isdigit(input[i])) {
				cout << "Wprowadzono niepoprawne dane" << endl;
				getchar();
				return;
			}
			bufor[j] += input[i];
		}
		else if (j < 2) {
			j++;
		}
		if (isspace(bufor[j][0])) bufor[j].erase(0, 1);
	}
	if (!bufor[0].empty()) bibliotekarz->set_id(stoi(bufor[0]));
	if (!bufor[1].empty()) bibliotekarz->get_dane_osobowe()->set_nazwa_uzytkownika(bufor[1]);
	if (!bufor[2].empty()) bibliotekarz->get_dane_osobowe()->set_rok_urodzenia(stoi(bufor[2]));
}

void Utilities::wczytaj_dane(Ksiazka*& ksiazka) {
	string input;
	cout << "Wpisz dane ksiazki wedlug ponizszego schematu" << endl;
	cout << "ID; Tytul; Autor; Rok_wydania; Kategoria;" << endl;
	getline(cin, input);
	string bufor[5];
	int j = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ';') {
			if ((j == 0 || j == 3) && !isdigit(input[i]) && !isspace(input[i])) {
				cout << "Wprowadzono niepoprawne dane" << endl;
				getchar();
				return;
			}
			if ((j == 1 || j == 2 || j == 4) && isdigit(input[i])) {
				cout << "Wprowadzono niepoprawne dane" << endl;
				getchar();
				return;
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
}


/*-------------FUNKCJONALNOSCI-------------*/
int Utilities::znajdz_ksiazke(Ksiazka**& ksiazki, int id, const int& rozmiar) {
	bool znaleziono = false;
	int index;
	for (int i = 0; i < rozmiar; i++) {
		if (ksiazki[i]) {
			if (ksiazki[i]->get_id() == id) {
				index = i;
				znaleziono = true;
				break;
			}
		}
		if (znaleziono) break;
	}
	if (!znaleziono) index = -1;
	return index;
}



int Utilities::wyswietl(Ksiazka**& ksiazka, const int& rozmiar) { //zwraca liczbe wyswietlonych ksiazek
	system("cls");
	cout << "Lista ksiazek" << endl;
	int counter = 0;
	for (int i = 0; i < rozmiar; i++) {
		if (ksiazka[i]->get_dostepnosc() == false) continue;
		cout << "-----------------------------------" << endl;
		cout << ksiazka[i];
		counter++;
	}
	return counter;
}

void Utilities::wyswietl(Ksiazka**& ksiazka, int& liczba_ksiazek) {
	cout << "Lista ksiazek" << endl;
	for (int i = 0; i < liczba_ksiazek; i++) {
		cout << "-----------------------------------" << endl;
		cout << "Id: " << ksiazka[i]->get_id() << endl;
		cout << "Tytul: " << ksiazka[i]->get_tytul() << endl;
		cout << "Autor: " << ksiazka[i]->get_autor() << endl;
		cout << "Kategoria: " << ksiazka[i]->get_kategoria() << endl;
		cout << "Rok wydania: " << ksiazka[i]->get_rok_wydania() << endl;
		cout << "Dostepnosc: " << ksiazka[i]->get_dostepnosc() << endl;
	}
}

void Utilities::wyswietl(Bibliotekarz**& bibliotekarze, const int& rozmiar) {
	cout << "Lista bibliotekarzy" << endl;
	for (int i = 0; i < rozmiar; i++) {
		cout << "-----------------------------------" << endl;
		cout << "Id: " << bibliotekarze[i]->get_id() << endl;
		cout << "Nazwa bibliotekarza: " << bibliotekarze[i]->get_dane_osobowe()->get_nazwa_uzytkownika() << endl;
		cout << "Rok urodzenia: " << bibliotekarze[i]->get_dane_osobowe()->get_rok_urodzenia() << endl;
	}
}

void Utilities::wyswietl(Czytelnik**& czytelnicy, const int& rozmiar) {
	cout << "Lista czytelnikow" << endl;
	for (int i = 0; i < rozmiar; i++) {
		cout << "-----------------------------------" << endl;
		cout << "Id: " << czytelnicy[i]->get_id() << endl;
		cout << "Nazwa czytelnika: " << czytelnicy[i]->get_dane_osobowe()->get_nazwa_uzytkownika() << endl;
		cout << "Rok urodzenia: " << czytelnicy[i]->get_dane_osobowe()->get_rok_urodzenia() << endl;
	}
}

void Utilities::wypozycz_ksiazke(Biblioteka& biblioteka, int index_ksiazki, int index_czytelnika, int index_bibliotekarza, const int& rozmiar) {
	Ksiazka* ksiazka_ptr = biblioteka.ksiazki[index_ksiazki];
	Czytelnik* czytelnik_ptr = biblioteka.czytelnicy[index_czytelnika];
	Bibliotekarz* bibliotekarz_ptr = biblioteka.bibliotekarze[index_bibliotekarza];

	if (czytelnik_ptr->get_liczba_wypozyczonych() >= czytelnik_ptr->get_limit_ksiazek()) {
		system("cls");
		cout << "Nie mozna wypozyczyc wiecej ksiazek" << endl;
		cout << "Sprobuj najpierw cos zwrocic" << endl << endl;
		cout << "Nacisnij dowolny przycisk aby kontynuowac..." << endl;
		getchar();
		getchar();
		return;
	}

	if (ksiazka_ptr->get_dostepnosc() == true) {
		if (czytelnik_ptr->get_liczba_wypozyczonych() == rozmiar || bibliotekarz_ptr->get_liczba_wypozyczonych() == rozmiar) {
			cout << "Wypozyczono maksymalna liczbe ksiazek" << endl;
			return;
		}
		else {
			int i = 0 + czytelnik_ptr->get_liczba_wypozyczonych();
			int j = 0 + bibliotekarz_ptr->get_liczba_wypozyczonych();
			ksiazka_ptr->set_dostepnosc(false);
			if (czytelnik_ptr->get_wypozyczone_ksiazki()[i] != nullptr)
				delete czytelnik_ptr->get_wypozyczone_ksiazki()[i];

			czytelnik_ptr->set_wypozyczona_ksiazka(ksiazka_ptr, i);
			czytelnik_ptr->set_liczba_wypozyczonych(czytelnik_ptr->get_liczba_wypozyczonych() + 1);
			czytelnik_ptr->dodaj_ksiazke(ksiazka_ptr);
			if (bibliotekarz_ptr->get_wypozyczone_ksiazki()[j] != nullptr)
				delete bibliotekarz_ptr->get_wypozyczone_ksiazki()[j];
			bibliotekarz_ptr->set_wypozyczona_ksiazka(ksiazka_ptr, j);
			bibliotekarz_ptr->set_liczba_wypozyczonych(bibliotekarz_ptr->get_liczba_wypozyczonych() + 1);
		}
	}
	else {
		cout << "Ksiazka juz wypozyczona" << endl;
		return;
	}
}

void Utilities::oddaj_ksiazke(Biblioteka& biblioteka, int index_czytelnika, int index_bibliotekarza, int& wybrane_id, const int& rozmiar) {
	Czytelnik* czytelnik_ptr = biblioteka.czytelnicy[index_czytelnika];
	Bibliotekarz* bibliotekarz_ptr = biblioteka.bibliotekarze[index_bibliotekarza];

	int index_c = Utilities::znajdz_ksiazke(czytelnik_ptr->get_wypozyczone_ksiazki(), wybrane_id, rozmiar);
	int index_b = Utilities::znajdz_ksiazke(bibliotekarz_ptr->get_wypozyczone_ksiazki(), wybrane_id, rozmiar);
	int index_k = Utilities::znajdz_ksiazke(biblioteka.ksiazki, wybrane_id, rozmiar);
	if (index_c < 0 || index_b < 0 || index_k < 0) {
		cout << "Ksiazka o ID " << wybrane_id << " nie istnieje" << endl;
		return;
	}
	else {
		Ksiazka* ksiazka_null{ nullptr };
		czytelnik_ptr->set_wypozyczona_ksiazka(ksiazka_null, index_c);
		czytelnik_ptr->set_wypozyczona_ksiazka(czytelnik_ptr->get_wypozyczone_ksiazki()[czytelnik_ptr->get_liczba_wypozyczonych() - 1], index_c); //przesuwa ostatnia ksiazke w zwolnione miejsce tablicy
		czytelnik_ptr->set_wypozyczona_ksiazka(ksiazka_null, czytelnik_ptr->get_liczba_wypozyczonych() - 1);
		czytelnik_ptr->set_liczba_wypozyczonych(czytelnik_ptr->get_liczba_wypozyczonych() - 1);
		bibliotekarz_ptr->set_wypozyczona_ksiazka(ksiazka_null, index_b);
		bibliotekarz_ptr->set_wypozyczona_ksiazka(bibliotekarz_ptr->get_wypozyczone_ksiazki()[bibliotekarz_ptr->get_liczba_wypozyczonych() - 1], index_c); //przesuwa ostatnia ksiazke w zwolnione miejsce tablicy
		bibliotekarz_ptr->set_wypozyczona_ksiazka(ksiazka_null, bibliotekarz_ptr->get_liczba_wypozyczonych() - 1);
		bibliotekarz_ptr->set_liczba_wypozyczonych(bibliotekarz_ptr->get_liczba_wypozyczonych() - 1);
		biblioteka.ksiazki[index_k]->set_dostepnosc(true);
		cout << "Pomyslnie oddano ksiazke" << endl;
		cout << "Nacisnij dowolny przycisk aby kontynuowac..." << endl;
	}
}