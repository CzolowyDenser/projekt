// kolow fortuny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <windows.h>

using namespace std;



int main()
{

	string haslo;
	string hasloKropki;
	string random;
	string kategoria;
	string graczOne;
	string graczTwo;
	string nagroda;
	int nrHasla = 0;
	int dlHasla = 0;
	int nrNagrody = 0;
	
	srand(time(NULL));
//wczytanie imion graczy
	cout << "KOLO FORTUNY v0.1\n\n";
	cout << "Podaj imie pierwszego gracza:\n";
	getline(cin, graczOne);

	cout << "Podaj imie drugiego gracza:\n";
	getline(cin, graczTwo);
	Sleep(800);
	system("cls");
	cout << "\nWitamy\n" << graczOne << " rozpoczyna kolejke.\n\nHaslo z kategori: \n";


	
//wylosowanie hasla i kategori z pliku
	ifstream plik("hasla.txt");
	nrHasla = (rand() % 5) + 1;
	for (int i = 1; i < nrHasla; i++)
		{
			getline(plik, random);
		}
//wczytanie	hasla i kategori do osobnych zmiennych
	plik >> kategoria;
	plik >> haslo;
	plik.close();
	cout << kategoria<<endl;
//podmiana hasla na kropki
	dlHasla = haslo.size();
	hasloKropki.append(dlHasla, '.');

//losowanie nagrody z pliku	
	cout << "Nacisnij ENTER aby zakrecic kolem" << endl;
	cin.get();
	ifstream prize("nagrody.txt");
	nrNagrody = (rand() % 12) + 1;
	for (int i = 1; i < nrNagrody; i++)
	{
		prize >> nagroda;
	}
	prize.close();
	cout << "Wylosowales/as " << nagroda << endl;



	
	cout << endl;

	


	
	cin.get();
	cin.get();
	return 0;
}