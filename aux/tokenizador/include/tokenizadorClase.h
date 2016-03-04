/*
 * TokenizadorClase.h
 *
 *  Created on: 29/01/2016
 *      Author: gir4
 */

#ifndef TOKENIZADORCLASE_H_
#define TOKENIZADORCLASE_H_

#include <iostream>
#include <ostream>
#include <list>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class TokenizadorClase {
	friend ostream& operator<<(ostream&, const TokenizadorClase&);
	// cout << “DELIMITADORES: “ << delimiters;

private:
	string delimiters;

public:
	// Constructor de copia
	TokenizadorClase(const TokenizadorClase&);
	// Inicializa variable privada delimiters a delimitadoresPalabra
	TokenizadorClase(const string& delimitadoresPalabra);
	// Inicializa delimiters=",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@"
	TokenizadorClase();
	// Inicializa variable privada delimiters a delimitadoresPalabra
	~TokenizadorClase(); // Delimiters = ""

	TokenizadorClase& operator= (const TokenizadorClase&); // Construye una copia

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

#endif /* TOKENIZADORCLASE_H_ */
