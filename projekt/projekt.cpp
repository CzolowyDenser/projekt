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

void kolejkaGraczaPierwszego(string, string);
int nagrodaa();

struct gracz
{
	string imie;
	int pieniadze;
}jeden, dwa;


int nrNagrody = 0;
int dlHasla = 0;

int main()
{

	string haslo;
	string hasloKropki;
	string random;
	string kategoria;
	
	int nrHasla = 0;
	
	
	
	srand(time(NULL));
//wczytanie imion graczy
	cout << "KOLO FORTUNY v0.1\n\n";
	cout << "Podaj imie pierwszego gracza:\n";
	getline(cin, jeden.imie);

	cout << "Podaj imie drugiego gracza:\n";
	getline(cin, dwa.imie);
	Sleep(800);
	system("cls");
	cout << "\nWitamy\n" << jeden.imie << " rozpoczyna kolejke.\n\nHaslo z kategori: \n";

	
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




	kolejkaGraczaPierwszego(haslo, hasloKropki);
	


	
	cin.get();
	cin.get();
	return 0;
}
int nagrodaa()
	{
		int nagroda = 0;
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
		return nagroda;
	}

void kolejkaGraczaPierwszego(string hasloo, string hasloKropkii)
	{
		char litera;
		bool w = 0;
		do
		{
			jeden.pieniadze+= nagrodaa();
			w = 0;
			cout << "Podaj litere." << endl;
			cin >> litera;
			cin.get();

			for (int i = 0; i <= dlHasla; i++)
				{
					if (hasloo[i] == litera)
					{
						hasloKropkii[i] = litera;
						w = 1;
					}	
				}
			cout << hasloKropkii << endl;
			cout << jeden.pieniadze<<endl;

		} while (w==1);

	}