#pragma once
#include "Biblioteka.h"
using namespace std;

class Biblioteka::Dyrektor {
	friend class Biblioteka;
	string imie;
	string nazwisko;
public:
	Dyrektor(string imie = "John", string nazwisko = "Smith") : imie(imie), nazwisko(nazwisko) {}
};