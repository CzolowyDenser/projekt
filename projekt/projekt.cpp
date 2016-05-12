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

const int n = 30;										//ilosc nagrod
const int p = 5;										//ilosc pytan
const int r = 4;										//ilosc rund

void kolejkaGraczaPierwszego(string, string&, int);
void kolejkaGraczaDrugiego(string, string&, int);
int nagrodaa();
void wyswietlRanking();


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
	
	int nrHasla[r + 1] = { 0 };
	int dlHasla = 0;
	
	
	srand(time(NULL));

	
	do
	{
		system("cls");
		cout << "KOLO FORTUNY v0.5\n\n\n";
		cout << "1. Rozpocznij gre" << endl;
		cout << "2. Sprawdz tabele wynikow" << endl;
		cout << "3. Wyjscie" << endl;
		int menu = 0;
		cin >> menu;
		switch (menu)
		{
		case 1:
		{
			system("cls");
			cin.get();
			cout << "Podaj imie pierwszego gracza:\n";																//wczytanie imion graczy
			getline(cin, jeden.imie);
			cout << "Podaj imie drugiego gracza:\n";
			getline(cin, dwa.imie);
			Sleep(800);
			system("cls");
			cout << "\nWitamy\n" << jeden.imie << " rozpoczyna kolejke.\n\nHaslo z kategori: \n";
			int b = 1;
			for (b = 1; b <= r; b++)
			{
				ifstream plik("hasla.txt");																			//wylosowanie hasla i kategori z pliku
				nrHasla[b] = (rand() % p) + 1;
				nrHasla[0] = nrHasla[b];

					if (b > 1)																						//sprawdzenie powtarzalnosci hasla
							for (int i = 1; i < b; i++)
								if (nrHasla[i] == nrHasla[0])
									do
									{
										nrHasla[b] = (rand() % p) + 1;
										nrHasla[0] = nrHasla[b];
									} while (nrHasla[i] == nrHasla[0]);

				for (int i = 1; i < nrHasla[b]; i++)
				{
					getline(plik, random);
				}

				kategoria.clear();
				haslo.clear();
				plik >> kategoria;																					//wczytanie	hasla i kategori do osobnych zmiennych
				plik >> haslo;
				plik.close();
				cout << kategoria << endl;
				hasloKropki.clear();
				hasloKropki = haslo;
				dlHasla = haslo.size();																				
				for (int i = 0; i <= dlHasla; i++)																	//podmiana hasla na kropki
				{
					if (hasloKropki[i] == '-');
					else
						hasloKropki[i] = '.';

				}

				do
				{
					kolejkaGraczaPierwszego(haslo, hasloKropki, dlHasla);

					if (haslo == hasloKropki)
						break;

					kolejkaGraczaDrugiego(haslo, hasloKropki, dlHasla);

				} while (haslo != hasloKropki);

			}

			ofstream ranko("ranking.txt", ios::app);
			ranko << jeden.pieniadze << " " << jeden.imie << endl;
			ranko << dwa.pieniadze << " " << dwa.imie << endl;
			ranko.close();

			wyswietlRanking();
			break;
		}
		case 2:
		{
			wyswietlRanking();
			break;
		}
		case 3:
			exit(0);
		}
	} while (true);
	return 0;
}
int nagrodaa()
	{	
		int nrNagrody = 0;
		int nagroda = 0;
		cout << "nacisnij ENTER aby zakrecic kolem" << endl;
		cin.get();
		ifstream prize("nagrody.txt");
		nrNagrody = (rand() % n) + 1;
		for (int i = 1; i < nrNagrody; i++)
		{
			prize >> nagroda;
		}
		prize.close();
		if (nagroda == 0)	cout << "BANKRUT! Tracisz kolejke" << endl;
		else cout << "Wylosowales/as " << nagroda << ". ";
		return nagroda;
	}

void kolejkaGraczaPierwszego(string hasloo, string& hasloKropkii, int dlHaslaa)
	{
		char litera;
		int pula;
		bool w = 0;
		do
		{
			cout << jeden.imie << " ";
			pula = nagrodaa();
			if (pula == 0)
				{
					jeden.pieniadze = 0;
					break;
				}
			w = 0;
			cout << endl;
			cout << jeden.imie << " podaj litere." << endl;
			cin >> litera;
			cout << endl;
			cin.get();

			for (int i = 0; i <= dlHaslaa; i++)
				{
					if (hasloo[i] == litera)
					{
						hasloKropkii[i] = litera;
						w = 1;
						jeden.pieniadze += pula;
						cout << "BRAWO! Twoj stan konta: " << jeden.pieniadze << endl;
			
					}	
				}
			cout << hasloKropkii << endl;
			if (hasloKropkii == hasloo)
				w=0;

		} while (w==1);

	}

void kolejkaGraczaDrugiego(string hasloo, string& hasloKropkii, int dlHaslaa)
{
	char litera;
	int pula;
	bool w = 0;
	do
	{
		cout << dwa.imie << " ";
		pula = nagrodaa();
		if (pula == 0)
		{
			dwa.pieniadze = 0;
			break;
		}
		w = 0;
		cout << endl;
		cout << dwa.imie << " podaj litere." << endl;
		cin >> litera;
		cout << endl;
		cin.get();

		for (int i = 0; i <= dlHaslaa; i++)
		{
			if (hasloo[i] == litera)
			{
				hasloKropkii[i] = litera;
				w = 1;
				dwa.pieniadze += pula;
				cout << "BRAWO! Twoj stan konta: " << dwa.pieniadze << endl;
			}
		}
		cout << hasloKropkii << endl;
		if (hasloKropkii == hasloo)
			w=0;
	} while (w == 1);

}

void wyswietlRanking()
{
	struct gracz
	{
		string imie;
		int pieniadze;
	};
	string test;
	int b = 0;

	system("cls");

	ifstream rank("ranking.txt");
	do
	{
		getline(rank, test);
		b++;
	} while (!rank.eof());
	b--;
	rank.close();

	gracz* tab = new gracz[b];

	ifstream ranking("ranking.txt");
	for (int i = 0; i < b; i++)
	{
		ranking >> tab[i].pieniadze;
		getline(ranking, tab[i].imie);
	}

	for (int i = 0; i < b; i++)
	{
		for (int j = 0; j < b - 1; j++)
		{
			if (tab[j].pieniadze < tab[j + 1].pieniadze)
				swap(tab[j], tab[j + 1]);
		}
	}

	for (int i = 0; i < b; i++)
		cout << i + 1 << "." << tab[i].imie << " " << tab[i].pieniadze << endl;

	delete [] tab;
	cin.get();
	cin.get();
}

