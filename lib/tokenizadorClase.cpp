/*
 * TokenizadorClase.cpp
 *
 *  Created on: 29/01/2016
 *      Author: gir4
 */

#include "tokenizadorClase.h"

TokenizadorClase::TokenizadorClase()
{
	delimiters=",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@";
}

TokenizadorClase::~TokenizadorClase()
{
	delimiters = "";
}

TokenizadorClase& TokenizadorClase::operator= (const TokenizadorClase& t)
{
	if(this != &t)
	{
		delimiters = t.delimiters;
	}
	return (*this);
}

void TokenizadorClase::Tokenizar(const string& str, list<string>& tokens) const
{
	string::size_type lastPos = str.find_first_not_of(delimiters,0);
	string::size_type pos = str.find_first_of(delimiters,lastPos);

	while(string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

bool TokenizadorClase::Tokenizar(const string& NomFichEntr, const string& NomFichSal) const
{
	ifstream i;
	ofstream f;
	string cadena;
	list<string> tokens;
	i.open(NomFichEntr.c_str());

	if(!i)
	{
		cerr << "Error: No existe el archivo: " << NomFichEntr << endl;
		return false;
	}
	else
	{
		while(!i.eof())
		{
			cadena="";
			getline(i, cadena);
			if(cadena.length()!=0)
			{
				Tokenizar(cadena, tokens);
			}
		}
	}

	i.close();
	f.open(NomFichSal.c_str());
	list<string>::iterator itS;

	for(itS = tokens.begin(); itS != tokens.end(); itS++)
	{
		f << (*itS) << endl;
	}
	f.close();

	return true;
}

bool TokenizadorClase::TokenizarDirectorio(const string& dirAIndexar) const
{
	struct stat dir;
	// Compruebo la existencia del directorio
	int err=stat(dirAIndexar.c_str(), &dir);

	if(err==-1 || !S_ISDIR(dir.st_mode))
		return false;

	else
	{
		// Hago una lista en un fichero con find>fich
		string cmd="find "+dirAIndexar+" -follow |sort > .lista_fich";
		system(cmd.c_str());
		return TokenizarListaFicheros(".lista_fich");
	}
}

// Probar metodo
bool TokenizadorClase::TokenizarListaFicheros(const string& i) const
{
	bool result = true;
	char separator = '\n';
	istringstream buf(i);
	string token;

	while(getline(buf, token, separator))
	{
		istringstream buf2(token);
		string nombreFich;
		getline(buf2, nombreFich, '.');

		if (!Tokenizar(token, nombreFich+".tk"))
			result = false;
	}
	return result;
}

void TokenizadorClase::DelimitadoresPalabra(const string& nuevoDelimiters)
{
	delimiters = nuevoDelimiters;
}

/*void TokenizadorClase::AnyadirDelimitadoresPalabra(const string& nuevoDelimiters)
{
	string auxDelimiters = delimiters + nuevoDelimiters;
	sort(delimiters.begin(), delimiters.end());
	delimiters = "";

	char lastDelimiter = '';

	for(int i = 0; i < auxDelimiters.size(); i++)
	{
		if(auxDelimiters[i] != lastDelimiter)
			delimiters += auxDelimiters[i];

		lastDelimiter = auxDelimiters[i];
	}
}*/
void TokenizadorClase::AnyadirDelimitadoresPalabra(const string& nuevoDelimiters)
{
	//sort(nuevoDelimiters.begin(), nuevoDelimiters.end());

	char lastDelimiter = 0;

	for(int i = 0; i < nuevoDelimiters.size(); i++)
	{
		if(nuevoDelimiters[i] != lastDelimiter && !delimiters.find(nuevoDelimiters[i]))
			delimiters += nuevoDelimiters[i];

		lastDelimiter = nuevoDelimiters[i];
	}
}

string TokenizadorClase::DelimitadoresPalabra() const
{
	return delimiters;
}

ostream& operator<<(ostream& o, const TokenizadorClase& t)
{
	o << "DELIMITADORES: " << t.delimiters;
	return o;
}






