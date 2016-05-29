// kolow fortuny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <cctype>

using namespace std;

const int n = 30;										//ilosc nagrod
const int p = 5;										//ilosc pytan
const int r = 3;										//ilosc rund
int k = 0;				
string sprawdzHaslo;									

void kolejkaGraczaPierwszego(string, string&, int, string);
void kolejkaGraczaDrugiego(string, string&, int, string);
int nagrodaa();
void wyswietlRanking();
void zasady();
void wczytajGraczy();


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
		cout << "3. Zasady gry." << endl;
		cout << "4. Wyjscie" << endl;
		int menu = 0;	
		while (!(cin>>menu)|| menu>4 )
			{
				cin.clear();
				cin.ignore();
				cout << "Zla wartosc" << endl;
				cout << "Wybierz jeszcze raz: ";
			}
		
		switch (menu)
		{
		case 1:
		{
			wczytajGraczy();
			cout << "\nWitamy\n" << jeden.imie << " rozpoczyna kolejke.\n\n\n\t\t\tHaslo z kategori: \n\n";
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
				getline(plik, haslo);
				haslo.erase(0, 1);
				plik.close();
				cout << "\t\t\t\t" << kategoria << "\n\n\n";
				hasloKropki.clear();
				hasloKropki = haslo;
				dlHasla = haslo.size();																				
				for (int i = 0; i <= dlHasla; i++)																	//podmiana hasla na kropki
				{
					
					if (hasloKropki[i] == ' ')
						hasloKropki[i] = '-';
					else
						hasloKropki[i] = '.';
				}
				for (int i = 0; i <= dlHasla; i++)																
				{

					if (haslo[i] == ' ')
						haslo[i] = '-';
				}

				do
				{
					if (k == 0)
					{
						kolejkaGraczaPierwszego(haslo, hasloKropki, dlHasla, kategoria);

						if (haslo == hasloKropki || haslo == sprawdzHaslo)
							break;
					}
					if (k == 1) kolejkaGraczaDrugiego(haslo, hasloKropki, dlHasla, kategoria);

				} while (haslo != hasloKropki);

			}
			system("cls");
			if (jeden.pieniadze > dwa.pieniadze)
			{
				cout << "Koniec gry!" << endl;
				cout << "Wygrywa " << jeden.imie<< " z wynikiem: " << jeden.pieniadze << "\nGratulacje!";
			}
			else
				if (jeden.pieniadze < dwa.pieniadze)
				{
					cout << "Koniec gry!" << endl;
					cout << "Wygrywa " << dwa.imie<< " z wynikiem: "<< dwa.pieniadze << "\nGratulacje!";
				}
				else
					if (jeden.pieniadze == dwa.pieniadze)
						cout << "REMIS!" << endl;
			cout << "\nZa chwile zobaczysz ranking graczy.";
			Sleep(6000);
			

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
		{
			zasady();
			break;
		}
		case 4:
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

void kolejkaGraczaPierwszego(string hasloo, string& hasloKropkii, int dlHaslaa, string kat)
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
					k = 1;
					break;
				}
			w = 0;
			cout << endl;
			cout << endl;
			cout  << "\t\t\t" << kat<<"  " << hasloKropkii << "\n\n";
			cout << jeden.imie << " podaj litere. Aby wprowadzic cale haslo podaj 0." << endl;
			cin >> litera;
			cout << endl;
			cin.sync();
			cin.clear();
			cin.get();
			if (litera == 'a' || litera == 'e' || litera == 'y' || litera == 'u' || litera == 'i' || litera == 'o')
			{
				if (jeden.pieniadze < 50)
				{
					cout << "Nie mozesz podac samogloski. Brak srodkow na koncie. Tracisz kolejke." << endl;
					k = 1;
					break;
				}
				cout << "Podales samogloske. Koszt 50" << endl;
				jeden.pieniadze -= 50;
			}
			if (litera == '0')
			{
				cout << "Podaj cale haslo:" << endl;
				getline(cin, sprawdzHaslo);
				if (sprawdzHaslo == hasloo)
				{
					int c = 0;
					cout << "HASLO PRAWIDLOWE" << endl;
					hasloKropkii = hasloo;
					for (int i = 0; i <= dlHaslaa; i++)
					{
						if (isalpha(hasloo[i]))
							c++;
					}
					jeden.pieniadze += (c * 50);
					cout << "Twoj stan konta " << jeden.pieniadze << endl;
					break;
				}
				else
				{
					cout << "HASLO NIE PRAWIDLOWE" << endl;
					k = 1;
					break;
				}
			}


			for (int i = 0; i <= dlHaslaa; i++)
				{
					if (hasloo[i] == litera)
					{
						hasloKropkii[i] = litera;
						w = 1;
						jeden.pieniadze += pula;
						cout << "BRAWO! Twoj stan konta: " << jeden.pieniadze << "\n\n";
					}	
				}
			cout << "\t\t\t" << kat<<"  " << hasloKropkii << "\n\n";
			if (w == 0)
			{
				cout << "Brak podanej litery :(" << endl;
				k = 1;
				Sleep(2000);
				system("cls");
				break;
			}
			if (hasloKropkii == hasloo || sprawdzHaslo == hasloo)
				w = 0;

		} while (w==1);
		
	}

void kolejkaGraczaDrugiego(string hasloo, string& hasloKropkii, int dlHaslaa, string kat)
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
			k = 0;
			break;
		}
		w = 0;
		cout << endl;
		cout << endl;
		cout <<  "\t\t\t" << kat<<"  " << hasloKropkii << "\n\n";
		cout << dwa.imie << " podaj litere. Aby wprowadzic cale haslo podaj 0." << endl;
		cin >> litera;
		cout << endl;
		cin.sync();
		cin.clear();
		cin.get();
		if (litera == 'a' || litera == 'e' || litera == 'y' || litera == 'u' || litera == 'i' || litera == 'o')
		{
			if (dwa.pieniadze < 50)
			{
				cout << "Nie mozesz podac samogloski. Brak srodkow na koncie. Tracisz kolejke." << endl;
				k = 0;
				break;
			}
			cout << "Podales samogloske. Koszt 50" << endl;
			dwa.pieniadze -= 50;
		}

		if (litera == '0')
		{
			cout << "Podaj cale haslo:" << endl;
			getline(cin, sprawdzHaslo);
			if (sprawdzHaslo == hasloo)
			{
				int c = 0;
				cout << "HASLO PRAWIDLOWE" << endl;
				hasloKropkii = hasloo;
				for (int i = 0; i <= dlHaslaa; i++)
				{
					if (isalpha(hasloo[i]))
						c++;
				}
				dwa.pieniadze += (c * 50);
				cout << "Twoj stan konta " << dwa.pieniadze << endl;
				break;
			}
			else
			{
				cout << "HASLO NIE PRAWIDLOWE" << endl;
				k = 0;
				break;
			}
		}
		for (int i = 0; i <= dlHaslaa; i++)
		{
			if (hasloo[i] == litera)
			{
				hasloKropkii[i] = litera;
				w = 1;
				dwa.pieniadze += pula;
				cout << "BRAWO! Twoj stan konta: " << dwa.pieniadze << "\n\n";
			}
		}
		cout << "\t\t\t" << kat<< "  "<< hasloKropkii << "\n\n";
		if (w == 0)
		{
			cout << "Brak podanej litery :(" << endl;
			k = 0;
			Sleep(2000);
			system("cls");
			break;
		}
		if (hasloKropkii == hasloo || sprawdzHaslo == hasloo)
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
	int b = -1;

	system("cls");

	ifstream rank("ranking.txt");
	do
	{
		getline(rank, test);
		b++;
	} while (!rank.eof());
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
void zasady()
{
	system("cls");
	cout << "1. Gra przeznaczona dla dwoch graczy." << endl << endl;;
	cout << "2. Spolgloski mozna podawac, a samogloski sie kupuje." << endl << endl;
	cout << "3. Koszt samogloski 50." << endl << endl;
	cout << "4. Jesli podasz samogloske, a nie masz wystarczajacej ilosci pieniedzy na koncie " << endl;
	cout << "   stracisz kolejke." << endl << endl;
	cout << "5. Przy podawaniu calego hasla nagroda to 50 za kazda litere hasla." << endl << endl;
	cout << "6. Aby podac haslo w calosci nalezy zamiast litery wpisac 0 (zero)." << endl << endl;
	cout << "7. Jesli haslo zawiera spacje zastap ja myslnikiem '-'." << endl << endl;
	cin.get();
	cin.get();
}
void wczytajGraczy()
{
	system("cls");
	cin.get();
	cout << "Podaj imie pierwszego gracza:\n";																//wczytanie imion graczy
	getline(cin, jeden.imie);
	cout << "Podaj imie drugiego gracza:\n";
	getline(cin, dwa.imie);
	Sleep(800);
	system("cls");
}

