import <iostream>;
import <string>;
import <string_view>;
import <random>;
import <cassert>;

using namespace std;

const int rozmiar_bibliotekarzy = 3;
const int rozmiar_ksiazek = 5;
const int rozmiar_czytelnikow = 5;
const int rozmiar_random = 10;

class Dane_osobowe {
	string nazwa_uzytkownika;
	int rok_urodzenia;
public:
	Dane_osobowe(const Dane_osobowe&); //deklaracja konstruktora kopiujacego
	Dane_osobowe(string = "", int = 0);
	void set_nazwa_uzytkownika(string nazwa_uzytkownika) { this->nazwa_uzytkownika = nazwa_uzytkownika; }
	string get_nazwa_uzytkownika() { return nazwa_uzytkownika; }
	void set_rok_urodzenia(int rok_urodzenia) { this->rok_urodzenia = rok_urodzenia; }
	int get_rok_urodzenia() { return rok_urodzenia; }
	Dane_osobowe operator=(Dane_osobowe dane) { //operator przypisania, potrzebny do operatora przypisania w klasie Czytelnik
		nazwa_uzytkownika = dane.nazwa_uzytkownika;
		rok_urodzenia = dane.rok_urodzenia;
	}
};
Dane_osobowe::Dane_osobowe(const Dane_osobowe& dane) : nazwa_uzytkownika(dane.nazwa_uzytkownika), rok_urodzenia(dane.rok_urodzenia) {} //definicja konstruktora kopiujacego
Dane_osobowe::Dane_osobowe(string nazwa_uzytkownika_, int rok_urodzenia_) : nazwa_uzytkownika(nazwa_uzytkownika_), rok_urodzenia(rok_urodzenia_) {} //lista inicjalizacyjna

//START KLASA BIBLIOTEKA
class Biblioteka {
	friend class Utilities;
	//zagniezdzone klasy
	//START KSIAZKA
	class Ksiazka {
		friend class Biblioteka;
		mutable int id;
		mutable string tytul;
		mutable string autor;
		mutable int rok_wydania;
		mutable string kategoria;
		mutable bool dostepnosc = false;
	public:
		Ksiazka(int = 0, string = "", string = "", int = 0, string = "", bool = false);
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
		
		friend ostream& operator<<(ostream& out, Ksiazka*& ksiazka) { //definicja przeciazonego operatora <<
			out << "ID: " << ksiazka->id << endl;
			out << "Tytul: " << ksiazka->tytul << endl;
			out << "Autor: " << ksiazka->autor << endl;
			out << "Rok wydania: " << ksiazka->rok_wydania << endl;
			out << "Kategoria: " << ksiazka->kategoria << endl;
			out << "Dostepnosc: " << ksiazka->dostepnosc << endl;
			return out;
		}

		friend istream& operator>>(istream& in, Ksiazka*& ksiazka) { //definicja przeciazonego operatora >> 
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
	//END KSIAZKA
	//START CZYTELNIK
	class Czytelnik {
		friend class Biblioteka;
		int id;
		Dane_osobowe* dane_osobowe{ nullptr };
		int przeczytane_ksiazki;
		int liczba_wypozyczonych;
		Ksiazka** wypozyczone_ksiazki{ nullptr };
	public:
		~Czytelnik();
		Czytelnik(int = 0, Dane_osobowe* = nullptr, int = 0, int = 0, Ksiazka** = nullptr);
		void set_id(int id) { this->id = id; }
		int get_id() { return this->id; }
		void set_dane_osobowe(Dane_osobowe* dane_osobowe) { this->dane_osobowe = dane_osobowe; }
		Dane_osobowe*& get_dane_osobowe() { return dane_osobowe; }
		void set_przeczytane_ksiazki(int przeczytanie_ksiazki) { this->przeczytane_ksiazki = przeczytane_ksiazki; }
		int get_przeczytane_ksiazki() { return this->przeczytane_ksiazki; }
		void set_liczba_wypozyczonych(int liczba_wypozyczonych) { this->liczba_wypozyczonych = liczba_wypozyczonych; }
		int& get_liczba_wypozyczonych() { return this->liczba_wypozyczonych; }
		//void set_wypozyczone_ksiazki(Ksiazka**& wypozyczone_ksiazki) { this->wypozyczone_ksiazki = wypozyczone_ksiazki; }
		void set_wypozyczona_ksiazka(Ksiazka*& wypozyczona_ksiazka, int i) { this->wypozyczone_ksiazki[i] = wypozyczona_ksiazka; }
		Ksiazka**& get_wypozyczone_ksiazki() { return this->wypozyczone_ksiazki; }
		Czytelnik operator=(Czytelnik czytelnik) { //operator przypisania, przyda sie w przyszlych aktualizacjach
			id = czytelnik.id;
			*dane_osobowe = *(czytelnik.dane_osobowe); //uzycie przeciazonego operatora przypisania
			przeczytane_ksiazki = czytelnik.przeczytane_ksiazki;
			liczba_wypozyczonych = czytelnik.liczba_wypozyczonych;
			wypozyczone_ksiazki = czytelnik.wypozyczone_ksiazki; //zwykle przypisanie wartosci wskaznika 
		}

		Ksiazka*& operator[](int index) {
			assert(index >= 0 && index < rozmiar_ksiazek);
			return wypozyczone_ksiazki[index];
		}
	};
	//END CZYTELNIK
	//START BIBLIOTEKARZ
	class Bibliotekarz {
		friend class Biblioteka;
		int id;
		Dane_osobowe* dane_osobowe{ nullptr };
		Ksiazka** wydane_ksiazki{ nullptr };
		int liczba_wydanych;
	public:
		~Bibliotekarz();
		Bibliotekarz(int = 0, Dane_osobowe* = nullptr, Ksiazka** = nullptr, int = 0);
		void set_id(int id) { this->id = id; }
		int get_id() { return this->id; }
		void set_dane_osobowe(Dane_osobowe* dane_osobowe) { this->dane_osobowe = dane_osobowe; }
		Dane_osobowe*& get_dane_osobowe() { return this->dane_osobowe; }
		void set_wydana_ksiazka(Ksiazka*& wydana_ksiazka, int i) { this->wydane_ksiazki[i] = wydana_ksiazka; }
		Ksiazka**& get_wydane_ksiazki() { return this->wydane_ksiazki; }
		void set_liczba_wydanych(int liczba_wydanych) { this->liczba_wydanych = liczba_wydanych; }
		int get_liczba_wydanych() { return this->liczba_wydanych; }

		Ksiazka*& operator[](int index) { //operator indeksowania
			assert(index >= 0 && index < rozmiar_ksiazek);
			return wydane_ksiazki[index];
		}
	};
	//END BIBLIOTEKARZ
	// START DYREKTOR
	class Dyrektor {
		friend class Biblioteka;
		string imie;
		string nazwisko;
	public:
		Dyrektor(string imie = "Mateusz", string nazwisko = "Zwierzchowski") : imie(imie), nazwisko(nazwisko) {}
	};
	// END DYREKTOR
	//prywatne pola klasy Biblioteka
	int liczba_czytelnikow;
	int liczba_bibliotekarzy;
	int liczba_ksiazek;
	Czytelnik** czytelnicy{ nullptr };
	Bibliotekarz** bibliotekarze{ nullptr };
	Ksiazka** ksiazki{ nullptr };
	static Dyrektor* dyrektor;
public:
	void set_liczba_czytelnikow(int liczba_czytelnikow) { this->liczba_czytelnikow = liczba_czytelnikow; }
	int get_liczba_czytelnikow() { return this->liczba_czytelnikow; }
	void set_liczba_bibliotekarzy(int liczba_bibliotekarzy) { this->liczba_bibliotekarzy = liczba_bibliotekarzy; }
	int get_liczba_bibliotekarzy() { return this->liczba_bibliotekarzy; }
	void set_liczba_ksiazek(int liczba_ksiazek) { this->liczba_ksiazek = liczba_ksiazek; }
	int get_liczba_ksiazek() { return this->liczba_ksiazek; }
	void set_czytelnik(Czytelnik*& czytelnik, int i) { this->czytelnicy[i] = czytelnik; }
	Czytelnik**& get_czytelnicy() { return this->czytelnicy; }
	void set_bibliotekarz(Bibliotekarz*& bibliotekarz, int i) { this->bibliotekarze[i] = bibliotekarz; }
	Bibliotekarz**& get_bibliotekarze() { return this->bibliotekarze; }
	void set_ksiazka(Ksiazka*& ksiazka, int i) { this->ksiazki[i] = ksiazka; }
	Ksiazka**& get_ksiazki() { return this->ksiazki; }
	Ksiazka*& get_ksiazka() { return ksiazki[0]; }
	//static Dyrektor*& get_dyrektor() { return dyrektor; }
	//static void stworz_dyrektora() { dyrektor = new Dyrektor; }
	//static void usun_dyrektora() { delete dyrektor; }
	Ksiazka*& operator[] (int index) { //przeciazenie operatora [] w celu wybrania elementu tablicy ksiazki
		assert(index >= 0 && index < rozmiar_ksiazek);
		return ksiazki[index];
	}

	//metody klasy Biblioteka
	void wypozycz_ksiazke(int index_ksiazki, int index_czytelnika, int index_bibliotekarza, const int& rozmiar);
	void oddaj_ksiazke(int index_czytelnika, int index_bibliotekarza, int& wybrane_id, const int& rozmiar);
};
//END KLASA BIBLIOTEKA

class Utilities {
public:
	static void stworz(Biblioteka::Ksiazka**& ksiazki, const int& rozmiar);
	static void stworz(Biblioteka::Ksiazka*& ksiazka);
	static void stworz(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar);
	static void stworz(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar);

	static void dodaj(Biblioteka::Ksiazka**& ksiazki, const int& rozmiar);
	static void dodaj(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar);
	static void dodaj(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar);

	static int generuj(int przedzial_od, int przedzial_do); //generuje liczby z podanego przedzialu
	static void generuj(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar);
	static void generuj(Dane_osobowe*& dane_osobowe);
	static void generuj(Biblioteka::Ksiazka**& ksiazki, const int& rozmiar);
	static void generuj(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar);

	static void wczytaj_dane(Biblioteka::Czytelnik*& czytelnik);
	static void wczytaj_dane(Biblioteka::Bibliotekarz*& bibliotekarz);
	static void wczytaj_dane(Biblioteka::Ksiazka*& ksiazka);

	static void usun(Biblioteka::Ksiazka**& ksiazki, const int& rozmiar);
	static void usun(Biblioteka::Ksiazka*& ksiazka);
	static void usun(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar);
	static void usun(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar);

	static int wyswietl(Biblioteka::Ksiazka**& ksiazka, const int& rozmiar); //zwraca liczbe wyswietlonych ksiazek
	static void wyswietl(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar);
	static void wyswietl(Biblioteka::Ksiazka**& ksiazka, int& liczba_ksiazek);
	static void wyswietl(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar);

	static int znajdz_ksiazke(Biblioteka::Ksiazka**& ksiazki, int id, const int& rozmiar); //zwraca index elementu tablicy dla obiektu o podanym id 
};

//globalne operatory


//definicje konstruktorow
Biblioteka::Ksiazka::Ksiazka(int id, string tytul, string autor, int rok_wydania, string kategoria, bool dostepnosc) {
	this->id = id;
	this->tytul = tytul;
	this->autor = autor;
	this->rok_wydania = rok_wydania;
	this->kategoria = kategoria;
	this->dostepnosc = dostepnosc;
}

Biblioteka::Czytelnik::Czytelnik(int id, Dane_osobowe* dane_osobowe, int przeczytane_ksiazki, int liczba_wypozyczonych, Ksiazka** wypozyczone_ksiazki) {
	this->id = id;
	this->dane_osobowe = dane_osobowe;
	this->przeczytane_ksiazki = przeczytane_ksiazki;
	this->liczba_wypozyczonych = liczba_wypozyczonych;
	this->wypozyczone_ksiazki = wypozyczone_ksiazki;
}

Biblioteka::Bibliotekarz::Bibliotekarz(int id, Dane_osobowe* dane_osobowe, Ksiazka** wydane_ksiazki, int liczba_wydanych) {
	this->id = id;
	this->dane_osobowe = dane_osobowe;
	this->wydane_ksiazki = wydane_ksiazki;
	this->liczba_wydanych = liczba_wydanych;
}

//definicje destruktorow
Biblioteka::Czytelnik::~Czytelnik() {
	delete dane_osobowe;
	dane_osobowe = nullptr;
	for (int i = 0; i < rozmiar_ksiazek; i++) {
		delete wypozyczone_ksiazki[i];
	}
	delete[] wypozyczone_ksiazki;
}

Biblioteka::Bibliotekarz::~Bibliotekarz() {
	delete dane_osobowe;
	dane_osobowe = nullptr;
	for (int i = 0; i < rozmiar_ksiazek; i++) {
		delete wydane_ksiazki[i];
	}
	delete[] wydane_ksiazki;
}

void stworz(Biblioteka*& biblioteka);
void usun(Biblioteka*& biblioteka);

string_view imiona[rozmiar_random]{ "Andrzej", "Adam", "Maciek", "Robert", "Agnieszka",
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
	stworz(biblioteka);
	Utilities::stworz(biblioteka->get_bibliotekarze(), rozmiar_bibliotekarzy);

	for (int i = 0; i < rozmiar_bibliotekarzy; i++) {
		Utilities::stworz(biblioteka->get_bibliotekarze()[i]->get_wydane_ksiazki(), rozmiar_ksiazek);
	}

	Utilities::stworz(biblioteka->get_czytelnicy(), rozmiar_czytelnikow);
	for (int i = 0; i < rozmiar_czytelnikow; i++) {
		Utilities::stworz(biblioteka->get_czytelnicy()[i]->get_wypozyczone_ksiazki(), rozmiar_ksiazek);
	}

	Utilities::stworz(biblioteka->get_ksiazki(), rozmiar_ksiazek);
	//Biblioteka::stworz_dyrektora();

	while (program_wlaczony) {
		system("cls");
		cout << ">> BIBLIOTEKA <<" << endl;
		cout << "1: Wypozycz ksiazke" << endl;
		cout << "2: Oddaj ksiazke" << endl;
		cout << "3: Generuj dane" << endl;
		cout << "4: Wczytaj dane" << endl;
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
				getchar();
				break;
			}
			cin >> wybrane_id;
			int index = Utilities::znajdz_ksiazke(biblioteka->get_ksiazki(), wybrane_id, rozmiar_ksiazek);
			if (index >= 0) {
				biblioteka->wypozycz_ksiazke(index, 0, 0, rozmiar_ksiazek);
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
				biblioteka->oddaj_ksiazke( 0, 0, wybrane_id, rozmiar_ksiazek);
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
		case 0: //wyjdz z programu
		{
			Utilities::usun(biblioteka->get_bibliotekarze(), rozmiar_bibliotekarzy);
			Utilities::usun(biblioteka->get_czytelnicy(), rozmiar_czytelnikow);
			Utilities::usun(biblioteka->get_ksiazki(), rozmiar_ksiazek);
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

void Utilities::stworz(Biblioteka::Ksiazka*& ksiazka) {
	ksiazka = new Biblioteka::Ksiazka;
}

void Utilities::stworz(Biblioteka::Ksiazka**& ksiazki, const int& rozmiar)
{
	ksiazki = new Biblioteka::Ksiazka * [rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		ksiazki[i] = new Biblioteka::Ksiazka;
	}
}

void Utilities::stworz(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar)
{
	Dane_osobowe dane;
	czytelnicy = new Biblioteka::Czytelnik * [rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		czytelnicy[i] = new Biblioteka::Czytelnik;
		czytelnicy[i]->get_dane_osobowe() = new Dane_osobowe(dane); //uzycie konstruktora kopiujacego
	}
}

void Utilities::stworz(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar)
{
	bibliotekarze = new Biblioteka::Bibliotekarz * [rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		bibliotekarze[i] = new Biblioteka::Bibliotekarz;
		bibliotekarze[i]->set_dane_osobowe(new Dane_osobowe);
	}
}

/*-------------DODAJ-------------*/
void Utilities::dodaj(Biblioteka::Ksiazka**& ksiazki, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		ksiazki[i]->set_id(i);
		ksiazki[i]->set_tytul("Wladca Pierscieni");
		ksiazki[i]->set_autor("J.R.R. Tolkien");
		ksiazki[i]->set_rok_wydania(2012);
		ksiazki[i]->set_kategoria("Fantasy");
		ksiazki[i]->set_dostepnosc(true);
	}
}

void Utilities::dodaj(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		czytelnicy[i]->set_id(1);
		czytelnicy[i]->get_dane_osobowe()->set_nazwa_uzytkownika("Andrzej");
		czytelnicy[i]->get_dane_osobowe()->set_rok_urodzenia(2000);
		czytelnicy[i]->set_przeczytane_ksiazki(0);
		czytelnicy[i]->set_liczba_wypozyczonych(0);
	}
}

void Utilities::dodaj(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		bibliotekarze[i]->set_id(i);
		bibliotekarze[i]->get_dane_osobowe()->set_nazwa_uzytkownika("Mariusz");
		bibliotekarze[i]->get_dane_osobowe()->set_rok_urodzenia(1999);
		bibliotekarze[i]->set_liczba_wydanych(0);
	}
}/*-------------GENERUJ-------------*/
int Utilities::generuj(int przedzial_od, int przedzial_do) {
	random_device rd;
	default_random_engine dfe(rd());
	uniform_int_distribution<int> dist(przedzial_od, przedzial_do);
	return dist(dfe);
}

void Utilities::generuj(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar) {
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
		czytelnicy[i]->set_id(temp_id);
		generuj(czytelnicy[i]->get_dane_osobowe());
		czytelnicy[i]->set_przeczytane_ksiazki(0);
		czytelnicy[i]->set_liczba_wypozyczonych(0);
	}
	delete[] zajete_id;
	zajete_id = nullptr;
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

void Utilities::generuj(Biblioteka::Ksiazka**& ksiazki, const int& rozmiar) {
	int m, n, k, t;
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
		ksiazki[i]->set_id(temp_id);
		//ksiazki[i]->id = temp_id;
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

void Utilities::generuj(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar) {
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
		bibliotekarze[i]->set_liczba_wydanych(0);
	}
	delete[] zajete_id;
	zajete_id = nullptr;
}

/*-------------WCZYTAJ DANE-------------*/
void Utilities::wczytaj_dane(Biblioteka::Czytelnik*& czytelnik) {
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

void Utilities::wczytaj_dane(Biblioteka::Bibliotekarz*& bibliotekarz) {
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

void Utilities::wczytaj_dane(Biblioteka::Ksiazka*& ksiazka) {
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


/*-------------USUN-------------*/
void Utilities::usun(Biblioteka::Ksiazka*& ksiazka) {
	delete ksiazka;
	ksiazka = nullptr;
}

void Utilities::usun(Biblioteka::Ksiazka**& ksiazki, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		delete ksiazki[i];
		ksiazki[i] = nullptr;
	}
	delete[] ksiazki;
	ksiazki = nullptr;
}

void usun(Biblioteka*& biblioteka) {
	delete biblioteka;
	biblioteka = nullptr;
}

void Utilities::usun(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		delete czytelnicy[i];
		czytelnicy[i] = nullptr;
	}
	delete[] czytelnicy;
	czytelnicy = nullptr;
}

void Utilities::usun(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		delete bibliotekarze[i];
		bibliotekarze[i] = nullptr;
	}
	delete[] bibliotekarze;
	bibliotekarze = nullptr;
}

/*-------------FUNKCJONALNOSCI-------------*/

int Utilities::znajdz_ksiazke(Biblioteka::Ksiazka**& ksiazki, int id, const int& rozmiar) {
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

void Biblioteka::wypozycz_ksiazke(int index_ksiazki, int index_czytelnika, int index_bibliotekarza, const int& rozmiar) {
	if (ksiazki[index_ksiazki]->get_dostepnosc()) {
		if (czytelnicy[index_czytelnika]->get_liczba_wypozyczonych() == rozmiar || bibliotekarze[index_bibliotekarza]->get_liczba_wydanych() == rozmiar) {
			cout << "Wypozyczono maksymalna liczbe ksiazek" << endl;
			return;
		}
		else {
			int i = 0 + czytelnicy[index_czytelnika]->get_liczba_wypozyczonych();
			int j = 0 + bibliotekarze[index_bibliotekarza]->get_liczba_wydanych();
			ksiazki[index_ksiazki]->set_dostepnosc(false);
			if (czytelnicy[index_czytelnika]->get_wypozyczone_ksiazki()[i] == nullptr) Utilities::stworz(czytelnicy[index_czytelnika]->get_wypozyczone_ksiazki()[i]);
			czytelnicy[index_czytelnika]->set_wypozyczona_ksiazka(ksiazki[index_ksiazki], i);
			czytelnicy[index_czytelnika]->set_liczba_wypozyczonych(czytelnicy[index_czytelnika]->get_liczba_wypozyczonych() + 1);
			if (bibliotekarze[index_bibliotekarza]->get_wydane_ksiazki()[j] == nullptr) Utilities::stworz(bibliotekarze[index_bibliotekarza]->get_wydane_ksiazki()[j]);
			bibliotekarze[index_bibliotekarza]->set_wydana_ksiazka(ksiazki[index_ksiazki], j);
			bibliotekarze[index_bibliotekarza]->set_liczba_wydanych(bibliotekarze[index_bibliotekarza]->get_liczba_wydanych() + 1);
		}
	}
	else {
		cout << "Ksiazka juz wypozyczona" << endl;
		return;
	}
}

void Biblioteka::oddaj_ksiazke(int index_czytelnika, int index_bibliotekarza,int& wybrane_id, const int& rozmiar) {
	int index_c = Utilities::znajdz_ksiazke(czytelnicy[index_czytelnika]->get_wypozyczone_ksiazki(), wybrane_id, rozmiar);
	int index_b = Utilities::znajdz_ksiazke(bibliotekarze[index_bibliotekarza]->get_wydane_ksiazki(), wybrane_id, rozmiar);
	int index_k = Utilities::znajdz_ksiazke(ksiazki, wybrane_id, rozmiar);
	if (index_c < 0 || index_b < 0 || index_k < 0) {
		cout << "Ksiazka o ID " << wybrane_id << " nie istnieje" << endl;
		return;
	}
	else {
		Ksiazka* ksiazka_null{ nullptr };
		czytelnicy[index_czytelnika]->set_wypozyczona_ksiazka(ksiazka_null, index_c);
		czytelnicy[index_czytelnika]->set_wypozyczona_ksiazka(czytelnicy[index_czytelnika]->get_wypozyczone_ksiazki()[czytelnicy[index_czytelnika]->get_liczba_wypozyczonych() - 1], index_c); //przesuwa ostatnia ksiazke w zwolnione miejsce tablicy
		czytelnicy[index_czytelnika]->set_wypozyczona_ksiazka(ksiazka_null, czytelnicy[index_czytelnika]->get_liczba_wypozyczonych() - 1);
		czytelnicy[index_czytelnika]->set_liczba_wypozyczonych(czytelnicy[index_czytelnika]->get_liczba_wypozyczonych() - 1);
		bibliotekarze[index_bibliotekarza]->set_wydana_ksiazka(ksiazka_null, index_b);
		bibliotekarze[index_bibliotekarza]->set_wydana_ksiazka(bibliotekarze[index_bibliotekarza]->get_wydane_ksiazki()[bibliotekarze[index_bibliotekarza]->get_liczba_wydanych() - 1], index_c); //przesuwa ostatnia ksiazke w zwolnione miejsce tablicy
		bibliotekarze[index_bibliotekarza]->set_wydana_ksiazka(ksiazka_null, bibliotekarze[index_bibliotekarza]->get_liczba_wydanych() - 1);
		bibliotekarze[index_bibliotekarza]->set_liczba_wydanych(bibliotekarze[index_bibliotekarza]->get_liczba_wydanych() - 1);
		ksiazki[index_k]->set_dostepnosc(true);
		cout << "Pomyslnie oddano ksiazke" << endl;
		cout << "Nacisnij dowolny przycisk aby kontynuowac..." << endl;
	}
}

int Utilities::wyswietl(Biblioteka::Ksiazka**& ksiazka, const int& rozmiar) { //zwraca liczbe wyswietlonych ksiazek
	system("cls");
	cout << "Lista ksiazek" << endl;
	int counter = 0;
	for (int i = 0; i < rozmiar; i++) {
		if (ksiazka[i]->get_dostepnosc() == false) continue;
		cout << "-----------------------------------" << endl;
		cout << ksiazka[i]; //uzycie przeciazonego operatora <<
		/*cout << "Id: " << ksiazka[i]->get_id() << endl;
		cout << "Tytul: " << ksiazka[i]->get_tytul() << endl;
		cout << "Autor: " << ksiazka[i]->get_autor() << endl;
		cout << "Kategoria: " << ksiazka[i]->get_kategoria() << endl;
		cout << "Rok wydania: " << ksiazka[i]->get_rok_wydania() << endl;
		cout << "Dostepnosc: " << ksiazka[i]->get_dostepnosc() << endl;*/
		counter++;
	}
	return counter;
}

void Utilities::wyswietl(Biblioteka::Ksiazka**& ksiazka, int& liczba_ksiazek) {
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

void Utilities::wyswietl(Biblioteka::Bibliotekarz**& bibliotekarze, const int& rozmiar) {
	cout << "Lista bibliotekarzy" << endl;
	for (int i = 0; i < rozmiar; i++) {
		cout << "-----------------------------------" << endl;
		cout << "Id: " << bibliotekarze[i]->get_id() << endl;
		cout << "Nazwa bibliotekarza: " << bibliotekarze[i]->get_dane_osobowe()->get_nazwa_uzytkownika() << endl;
		cout << "Rok urodzenia: " << bibliotekarze[i]->get_dane_osobowe()->get_rok_urodzenia() << endl;
	}
}

void Utilities::wyswietl(Biblioteka::Czytelnik**& czytelnicy, const int& rozmiar) {
	cout << "Lista czytelnikow" << endl;
	for (int i = 0; i < rozmiar; i++) {
		cout << "-----------------------------------" << endl;
		cout << "Id: " << czytelnicy[i]->get_id() << endl;
		cout << "Nazwa czytelnika: " << czytelnicy[i]->get_dane_osobowe()->get_nazwa_uzytkownika() << endl;
		cout << "Rok urodzenia: " << czytelnicy[i]->get_dane_osobowe()->get_rok_urodzenia() << endl;
	}
}
