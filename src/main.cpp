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

void printTokens(list<string>& tokens)
{
	int tam = tokens.size();
	for(int i = 0; i < tam; i++)
	{
		cout << tokens.front() <<"\n";
		tokens.pop_front();
	}
}

int main()
{
	// He comentado el metodo de tokenizar para que no de error.

	//Tokenizador a("@.&", true, false);
	//string s1 = "@.&";
	list<string> lt1;
	//list<string> tokens;
	int tam;

	/* +++++++++++++++++++++++++++++ TEST GUIONES ++++++++++++++++++++++++++++++++++++++++++*/

	Tokenizador a("-#", true, false);
	list<string> tokens;
	a.Tokenizar("MS-DOS p1 p2 UN-DOS-TRES", tokens);
	// La lista de tokens a devolver debería contener: "MS-DOS, p1, p2, UN-DOS-TRES"
	a.Tokenizar("pal1 -MS-DOS p1 p2", tokens);
	// La lista de tokens a devolver debería contener: "pal1, MS-DOS, p1, p2"
	a.Tokenizar("pal1 MS-DOS#p3 p1 p2", tokens);
	// La lista de tokens a devolver debería contener: "pal1, MS-DOS, p3, p1, p2"
	a.Tokenizar("pal1#MS-DOS#p3 p1 p2", tokens);
	// La lista de tokens a devolver debería contener: "pal1, MS-DOS, p3, p1, p2"
	a.DelimitadoresPalabra("/ ");
	a.Tokenizar("MS-DOS p1 p2", tokens);
	// La lista de tokens a devolver debería contener: "MS-DOS, p1, p2"
	a.Tokenizar("pal1 -MS-DOS p1 p2", tokens);
	// La lista de tokens a devolver debería contener: "pal1, -MS-DOS, p1, p2"
	a.Tokenizar("pal1 MS-DOS#p3 p1 p2", tokens);
	// La lista de tokens a devolver debería contener: "pal1, MS-DOS#p3, p1, p2"
	a.Tokenizar("pal1#MS-DOS#p3 p1 p2", tokens);
	// La lista de tokens a devolver debería contener: "pal1#MS-DOS#p3, p1, p2"
	/* +++++++++++++++++++++++++++++ TEST GUIONES ++++++++++++++++++++++++++++++++++++++++++*/

	/* +++++++++++++++++++++++++++++ TEST ACRONIMOS ++++++++++++++++++++++++++++++++++++++++++*/
/*
	a.DelimitadoresPalabra("@.&");

	a.Tokenizar("U.S.A p1 e.g. p2. La", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "U.S.A, p1, e.g, p2, La"
	a.Tokenizar("U..S.A p1 e..g. p2. La", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "U, S.A, p1, e, g, p2, La"
	a.Tokenizar("...U.S.A p1 e..g. p2. La", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "U.S.A, p1, e, g, p2, La"
	a.Tokenizar("Hack.4.Good p1", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "Hack.4.Good, p1"
	a.DelimitadoresPalabra("");
	a.Tokenizar("U.S.A .U.S.A .p1 p1 e.g. p2. La", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "U.S.A, U.S.A, .p1, p1, e.g, p2., La"
	a.Tokenizar("U..S.A p1 e..g. p2. La", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "U..S.A, p1, e..g., p2.,	La"
	a.Tokenizar("...U.S.A p1 e..g. p2. La", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "...U.S.A, p1, e..g., p2.,La"
	a.Tokenizar("a&U.S.A p1 e.g. p2. La", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "a&U.S.A, p1, e.g, p2., La"
	a.DelimitadoresPalabra("&");
	a.Tokenizar("a&U.S.A p1 e.g. p2. La", lt1);
	printTokens(lt1);
	// La lista de tokens a devolver debería contener: "a, U.S.A, p1, e.g, p2.,	La"	 */
	/* +++++++++++++++++++++++++++++ TEST ACRONIMOS ++++++++++++++++++++++++++++++++++++++++++*/

	/* +++++++++++++++++++++++++++++ TEST EMAIL ++++++++++++++++++++++++++++++++++++++++++*/
	/*
	a.DelimitadoresPalabra("@.&");
	a.Tokenizar("catedraTelefonicaUA@iuii.ua.es p1 p2", tokens);
	printTokens(tokens);
	// La lista de tokens a devolver debería contener:"catedraTelefonicaUA@iuii.ua.es, p1, p2"
	a.Tokenizar("pal1 @iuii.ua.es p1 p2", tokens);
	printTokens(tokens);
	a.Tokenizar("pal1 cat@iuii.ua.es@cd p1 p2", tokens);
	printTokens(tokens);
	// La lista de tokens a devolver debería contener: "pal1, cat, iuii.ua.es@cd,p1, p2"
	a.DelimitadoresPalabra("&.");
	a.Tokenizar("catedraTelefonicaUA@iuii.ua.es p1 p2", tokens);
	printTokens(tokens);

	// La lista de tokens a devolver debería contener:"catedraTelefonicaUA@iuii.ua.es, p1, p2"
	a.Tokenizar("pal1 @iuii.ua.es p1 p2", tokens);
	printTokens(tokens);

	// La lista de tokens a devolver debería contener: "pal1, @iuii.ua.es, p1, p2"
	a.Tokenizar("pal1&@iuii.ua.es p1 p2", tokens);
	printTokens(tokens);
	// La lista de tokens a devolver debería contener: "pal1, @iuii.ua.es, p1, p2"
	a.Tokenizar("pal1&catedra@iuii.ua.es p1 p2", tokens);
	printTokens(tokens);
	// La lista de tokens a devolver debería contener: "pal1, catedra@iuii.ua.es,p1, p2"
	a.Tokenizar("pal1 cat@iuii.ua.es@cd p1 p2", tokens);
	printTokens(tokens);
	// La lista de tokens a devolver debería contener: "pal1, iuii.ua.es, p1, p2"
	*/
	// ++++++++++++++++++++++++++++ TEST EMAIL +++++++++++++++++++++++++++++++++++++ */
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
	}
	// La lista de tokens a devolver debería contener (no extraería números sino acrónimos): "pal1 10.00a 10.000.a.000 10/12/85 1,23E+10"
	a.Tokenizar("pal1&10.00@10.000&abc@10/12/85", lt1);
	tam = lt1.size();
	for(int i = 0; i < tam; i++)
	{
		cout << lt1.front() <<", ";
		lt1.pop_front();
	}
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

