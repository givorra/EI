/*
 * main.cpp
 *
 *  Created on: 29/01/2016
 *      Author: gir4
 */
#include "tokenizador.h"

using namespace std;

#include <iostream>
#include <fstream>

int main()
{
	// He comentado el metodo de tokenizar para que no de error.

	Tokenizador a("@.&", true, false);
	//string s1 = "@.&";
	list<string> lt1;
	int tam;

	// **************************** PRUEBA DE PASAR A MINUSCULAS *******************************/
	/*

	ifstream myfile ("test.txt");
	getline(myfile,s1);
	myfile.close();

	string auxtoken = tc.getMinusSinAcentos(s1);

	cout << s1 << "\n" << auxtoken << "\n";
	*/
	// **************************** PRUEBA DE PASAR A MINUSCULAS *******************************/
	//cout << t.DelimitadoresPalabra() << endl;
	//t.DelimitadoresPalabra("/.:;&+M");
	//cout << t.DelimitadoresPalabra() << endl;
	//a.DelimitadoresPalabra(s1);

	/*
	string s = "pepe";
	string::size_type p = 0;
	a.Tokenizar("https:gacelIvor_:/.?&-=#@ra/rodriguez?=tokens ftp:asdn/&_:/.?&-=#@ http:_:/.?&-=#@pomf_:/.?&-=#@pa asd", lt1);
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<", ";
		lt1.pop_front();
	}

	a.DelimitadoresPalabra("@.,&");
	a.Tokenizar("pal1 10.000,34 10,000.34 10.000.123.456.789.009,34 10,000,123,456,789,009.34 20.03 40,03 2005 10. 20, 10.0 20,0 La 20,12.456,7.8.9,", lt1);
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<endl;
		lt1.pop_front();
	}*/
	// La lista de tokens a devolver debería contener: "pal1 10.000,34 10,000.34 10.000.123.456.789.009,34 10,000,123,456,789,009.34 20.03 40,03 2005 10 20 10.0 20,0 La 20,12.456,7.8.9"
	//a.Tokenizar(".34 ,56", lt1);
	// La lista de tokens a devolver debería contener: "0.34	0,56"
	/*a.Tokenizar("pal1 10.35% 10,35% 23.000,3% 23,5€ 23.05€ 23,05€ 11.1$ 11.05$ 3.4o 4,3a", lt1);
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<" ";
		lt1.pop_front();
	}

	// La lista de tokens a devolver debería contener: "pal1 10.35 % 10,35 % 23.000,3 %	23,5 € 23.05 € 23,05 € 11.1	$ 11.05 $ 3.4 o 4.3 a"
	a.Tokenizar("pal1 10.00a 10.000.a.000 10/12/85 1,23E+10", lt1);
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<", ";
		lt1.pop_front();
	}*/
	// La lista de tokens a devolver debería contener (no extraería números sino acrónimos): "pal1 10.00a 10.000.a.000 10/12/85 1,23E+10"
	a.Tokenizar("pal1&10.00@10.000&abc@10/12/85", lt1);
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<", ";
		lt1.pop_front();
	}/*
	// La lista de tokens a devolver debería contener (extraería un email): "pal1 10.00 10.000 abc@10/12/85"
	a.Tokenizar(".34@@&,56", lt1);
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<", ";
		lt1.pop_front();
	}
	// La lista de tokens a devolver debería contener: "0.34 0,56"
	a.Tokenizar("...10.000.a.000 ,,23.05 10/12/85 1,23E+10", lt1);
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<", ";
		lt1.pop_front();
	}
	// La lista de tokens a devolver debería contener (extraería un acrónimo): "10.000.a.000 23.05 10/12/85 1 23E+10"
	a.DelimitadoresPalabra("");
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<", ";
		lt1.pop_front();
	}
	a.Tokenizar("...10.000.a.000 ,,23.05 10/12/85 1,23E+10", lt1);
	// La lista de tokens a devolver debería contener: "...10.000.a.000	,,23.05	10/12/85 1,23E+10"
	 * */
}

