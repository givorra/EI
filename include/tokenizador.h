/*
 * tokenizador.h
 *
 *  Created on: 29/01/2016
 *      Author: gir4
 */

#ifndef TOKENIZADOR_H_
#define TOKENIZADOR_H_

#include <iostream>
#include <ostream>
#include <list>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

enum TCasoEspecial  {NINGUNO, URL, REAL, EMAIL, ACRONIMO};

const string iden1URL = "http:";
const string iden1URL = "https:";
const string urlDelimiters = "_:/.?&-=#@";

class Tokenizador {
	friend ostream& operator<<(ostream&, const Tokenizador&);
	/* cout << “DELIMITADORES: “ << delimiters << “ TRATA CASOS ESPECIALES:
	“ << casosEspeciales << “ PASAR A MINUSCULAS Y SIN ACENTOS: “ <<pasarAminuscSinAcentos;
*/

private:
	/* Delimitadores de términos. Aunque se modifique la forma de almacenamiento interna para mejorar la eficiencia, este
	campo debe permanecer para indicar el orden en que se introdujeron los delimitadores*/
	string delimiters;
	// Si true detectará palabras compuestas y casos especiales
	bool casosEspeciales;
	// Si true pasará el to
	bool pasarAminuscSinAcentos;

	TCasoEspecial status;
	string specialCaseToken;

	string getMinusSinAcentos(const string& token) const;
	bool casoEspecial(const string& token) const;

public:

	// Inicializa delimiters a delimitadoresPalabra; casosEspeciales a kcasosEspeciales; pasarAminuscSinAcentos a minuscSinAcentos
	Tokenizador(const string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos);
	// Inicializa delimiters=",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@";	casosEspeciales a true; pasarAminuscSinAcentos a false
	Tokenizador();
	// Constructor de copia
	Tokenizador(const Tokenizador&);
	// Inicializa variable privada delimiters a delimitadoresPalabra
	Tokenizador(const string& delimitadoresPalabra);

	// Cambia la variable privada “casosEspeciales”
	void CasosEspeciales (const bool& nuevoCasosEspeciales);
	// Devuelve el contenido de la variable privada “casosEspeciales”
	bool CasosEspeciales ();
	/* Cambia la variable privada “pasarAminuscSinAcentos”. Atención al
	formato de codificación del corpus (comando “file” de Linux). Para la
	corrección de la práctica se utilizará el formato actual (ISO-8859).
	*/
	void PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos);

	// Devuelve el contenido de la variable privada “pasarAminuscSinAcentos”
	bool PasarAminuscSinAcentos ();


	Tokenizador& operator= (const Tokenizador&); // Construye una copia

	// Tokeniza str devolviendo el resultado en tokens. La lista tokens se
	// vaciará antes de almacenar el resultado de la tokenización
	void Tokenizar(const string& str, list<string>& tokens) const;

	// Tokeniza el fichero i guardando la salida en el fichero f (una
	//palabra en cada línea del fichero). Devolverá true si se realiza la
	//tokenización de forma correcta enviando a cerr el mensaje
	//correspondiente (p.ej. que no exista el archivo i)
	bool Tokenizar (const string& i, const string& f) const;

	// Tokeniza el fichero i guardando la salida en un fichero de nombre i
	//añadiéndole extensión .tk (sin eliminar previamente la extensión de i
	//por ejemplo, del archivo pp.txt se generaría el resultado en pp.txt.tk),
	//y que contendrá una palabra en cada línea del fichero. Devolverá true si
	//de realiza la tokenización de forma correcta enviando a cerr el mensaje
	//correspondiente (p.ej. que no exista el archivo i)
	bool Tokenizar (const string & i) const;

	/* Tokeniza el fichero i que contiene un nombre de fichero por línea
	guardando la salida en un fichero cuyo nombre será el de entrada
	añadiéndole extensión .tk, y que contendrá una palabra en cada línea del
	fichero. Devolverá true si se realiza la tokenización de forma correcta
	de todos los archivos que contiene i; devolverá false en caso contrario
	enviando a cerr el mensaje correspondiente (p.ej. que no exista el
	archivo i, o bien enviando a “cerr” los archivos de i que no existan)*/
	bool TokenizarListaFicheros (const string& i) const;

	/* Tokeniza todos los archivos que contenga el directorio i, incluyendo
	los de los subdirectorios, guardando la salida en ficheros cuyo nombre
	será el de entrada añadiéndole extensión .tk, y que contendrá una
	palabra en cada línea del fichero. Devolverá true si se realiza la
	tokenización de forma correcta de todos los archivos; devolverá false en
	caso contrario enviando a cerr el mensaje correspondiente (p.ej. que no
	exista el directorio i, o los ficheros que no se hayan podido tokenizar)*/
	bool TokenizarDirectorio (const string& i) const;

	// Cambia “delimiters” por “nuevoDelimiters”
	void DelimitadoresPalabra(const string& nuevoDelimiters);

	/* Añade al final de “delimiters” los nuevos delimitadores que aparezcan
	en “nuevoDelimiters” (no se almacenarán caracteres repetidos)*/
	void AnyadirDelimitadoresPalabra(const string& nuevoDelimiters);

	// Devuelve “delimiters”
	string DelimitadoresPalabra() const;

};

#endif /* TOKENIZADOR_H_ */
