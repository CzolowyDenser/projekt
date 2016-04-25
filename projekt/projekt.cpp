// kolow fortuny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <fstream>


using namespace std;



int main()
{

	string haslo;
	string random;
	string kategoria;
	string graczOne;
	string graczTwo;
	int nrHasla = 0;
	int dlHasla = 0;
	int i = 0;
	int l = 1;
	srand(time(NULL));

	cout << "KOLO FORTUNY v0.1\n\n";
	cout << "Podaj imie pierwszego gracza:\n";
	getline(cin, graczOne);

	cout << "Podaj imie drugiego gracza:\n";
	getline(cin, graczTwo);

	cout << "\nWitamy\n" << graczOne << " rozpoczyna kolejke.\n\nHaslo z kategori: \n";



	ifstream plik("hasla.txt");
	nrHasla = (rand() % 5) + 1;
	for (int i = 1; i < nrHasla; i++)
	{
		getline(plik, random);
	}
	
	
	plik >> kategoria;
	
	plik >> haslo;
		//getline(plik, kategoria);
	

	cout << kategoria;
	cout << endl;
	cout << haslo;


	
	/*while (isupper(kategoria.at(i)))
	{
		cout << kategoria.at(i);

		i++;
	}
	if (isspace(kategoria.at(i)))
	{
		i++;
		do
		{
			haslo.at(l) = kategoria.at(i);
			i++;
			l++;
		} while (!kategoria.at(i) == '.');

	}

	cout << endl << haslo;

	cout << endl;
*/
	cin.get();
	cin.get();
	return 0;
}