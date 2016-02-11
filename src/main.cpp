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

	Tokenizador t;
	string s1;

	// **************************** PRUEBA DE PASAR A MINUSCULAS *******************************/
	/*

	ifstream myfile ("test.txt");
	getline(myfile,s1);
	myfile.close();

	string auxtoken = tc.getMinusSinAcentos(s1);

	cout << s1 << "\n" << auxtoken << "\n";
	*/
	// **************************** PRUEBA DE PASAR A MINUSCULAS *******************************/
	cout << t.DelimitadoresPalabra() << endl;
	t.DelimitadoresPalabra("/.:;&+M");
	cout << t.DelimitadoresPalabra() << endl;
}

