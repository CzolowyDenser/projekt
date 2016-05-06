// kolow fortuny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <windows.h>


const int n = 12;
const int p = 5;

using namespace std;

void kolejkaGraczaPierwszego(string, string&, int);
void kolejkaGraczaDrugiego(string, string&, int);
int nagrodaa();

struct gracz
{
	string imie;
	int pieniadze;
}jeden, dwa;


int main()
{

	string haslo;
	string hasloKropki;
	string random;
	string kategoria;
	
	int nrHasla = 0;
	int dlHasla = 0;
	
	
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

	

	ifstream plik("hasla.txt");																			//wylosowanie hasla i kategori z pliku
	nrHasla = (rand() % p) + 1;
	for (int i = 1; i < nrHasla; i++)
		{
			getline(plik, random);
		}


	plik >> kategoria;																					//wczytanie	hasla i kategori do osobnych zmiennych
	plik >> haslo;
	plik.close();
	cout << kategoria<<endl;
		

	dlHasla = haslo.size();																				//podmiana hasla na kropki
	hasloKropki.append(dlHasla, '.');



	do
	{
		kolejkaGraczaPierwszego(haslo, hasloKropki, dlHasla);

		if (haslo == hasloKropki)
			break;

		kolejkaGraczaDrugiego(haslo, hasloKropki, dlHasla);

	} while (haslo != hasloKropki);

	
	cin.get();
	cin.get();
	return 0;
}
int nagrodaa()
	{	
		int nrNagrody = 0;
		int nagroda = 0;
		cout << "Nacisnij ENTER aby zakrecic kolem" << endl;
		cin.get();
		ifstream prize("nagrody.txt");
		nrNagrody = (rand() % n) + 1;
		for (int i = 1; i < nrNagrody; i++)
		{
			prize >> nagroda;
		}
		prize.close();
		cout << "Wylosowales/as " << nagroda << ". ";
		return nagroda;
	}

void kolejkaGraczaPierwszego(string hasloo, string& hasloKropkii, int dlHaslaa)
	{
		char litera;
		int pula;
		bool w = 0;
		do
		{
			pula = nagrodaa();
			w = 0;
			cout << endl;
			cout << jeden.imie << " podaj litere." << endl;
			cin >> litera;
			cin.get();

			for (int i = 0; i <= dlHaslaa; i++)
				{
					if (hasloo[i] == litera)
					{
						hasloKropkii[i] = litera;
						w = 1;
						jeden.pieniadze +=pula ;
						cout << "Twoj stan konta: " << jeden.pieniadze << endl;
					}	
				}
			cout << hasloKropkii << endl;
			if (hasloKropkii == hasloo)
				break;

		} while (w==1);

	}


void kolejkaGraczaDrugiego(string hasloo, string& hasloKropkii, int dlHaslaa)
{
	char litera;
	bool w = 0;
	do
	{
		
		w = 0;
		cout << endl;
		cout << dwa.imie << " podaj litere." << endl;
		cin >> litera;
		cin.get();

		for (int i = 0; i <= dlHaslaa; i++)
		{
			if (hasloo[i] == litera)
			{
				hasloKropkii[i] = litera;
				w = 1;
				dwa.pieniadze += nagrodaa();
				cout << "Twoj stan konta: " << dwa.pieniadze << endl;
			}
		}
		cout << hasloKropkii << endl;
		if (hasloKropkii == hasloo)
			break;
	} while (w == 1);

}