/*
 * tokenizador.cpp
 *
 *  Created on: 29/01/2016
 *      Author: gir4
 */

#include "tokenizador.h"

/*
 * Tokenizador.cpp
 *
 *  Created on: 29/01/2016
 *      Author: gir4
 */

Tokenizador::Tokenizador(const string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos):
	delimiters(delimitadoresPalabra),
	casosEspeciales(kcasosEspeciales),
	pasarAminuscSinAcentos(minuscSinAcentos),
	status(NINGUNO)
{}

Tokenizador::Tokenizador():
	delimiters(",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@"),
	casosEspeciales(true),
	pasarAminuscSinAcentos(false),
	status(NINGUNO)
{}

Tokenizador::Tokenizador(const Tokenizador& t):
	delimiters(t.delimiters),
	casosEspeciales(t.casosEspeciales),
	pasarAminuscSinAcentos(t.pasarAminuscSinAcentos),
	status(t.status)
{}

Tokenizador::~Tokenizador()
{
	delimiters = "";
}

Tokenizador& Tokenizador::operator= (const Tokenizador& t)
{
	if(this != &t)
	{
		delimiters 				= t.delimiters;
		casosEspeciales 		= t.casosEspeciales;
		pasarAminuscSinAcentos 	= t.pasarAminuscSinAcentos;
	}
	return (*this);
}

void Tokenizador::Tokenizar(const string& str, list<string>& tokens) const
{
	string token;
	string::size_type lastPos = str.find_first_not_of(delimiters,0);
	string::size_type pos = str.find_first_of(delimiters,lastPos);

	while(string::npos != pos || string::npos != lastPos)
	{
		if(!casosEspeciales || !casoEspecial(str.substr(lastPos, pos+1 - lastPos)))	// Manda token con delimitador
		{
			if(pasarAminuscSinAcentos)		// Si se duplica el while se puede realizar una sola vez la comprobación
				token = getMinusSinAcentos(str.substr(lastPos, pos - lastPos));
			else
				token = str.substr(lastPos, pos - lastPos);

			tokens.push_back(token);
			lastPos = str.find_first_not_of(delimiters, pos);
		}
		pos = str.find_first_of(delimiters, lastPos);
	}
}


bool Tokenizador::Tokenizar(const string& NomFichEntr, const string& NomFichSal) const
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

bool Tokenizador::TokenizarDirectorio(const string& dirAIndexar) const
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
bool Tokenizador::TokenizarListaFicheros(const string& i) const
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

inline void Tokenizador::DelimitadoresPalabra(const string& nuevoDelimiters)
{
	delimiters = nuevoDelimiters;
}

void Tokenizador::AnyadirDelimitadoresPalabra(const string& nuevoDelimiters)
{
	sort(nuevoDelimiters.begin(), nuevoDelimiters.end());

	char lastDelimiter = 0;

	for(int i = 0; i < nuevoDelimiters.size(); i++)
	{
		if(nuevoDelimiters[i] != lastDelimiter && !delimiters.find(nuevoDelimiters[i]))
			delimiters += nuevoDelimiters[i];

		lastDelimiter = nuevoDelimiters[i];
	}
}

inline string Tokenizador::DelimitadoresPalabra() const
{
	return delimiters;
}

ostream& operator<<(ostream& o, const Tokenizador& t)
{
	o << "DELIMITADORES: " << t.delimiters << " TRATA CASOS ESPECIALES: " << t.casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << t.pasarAminuscSinAcentos;
	return o;
}

//if(!casosEspeciales || casoEspecial(c))
inline void Tokenizador::CasosEspeciales(const bool& nuevoCasosEspeciales)
{
	casosEspeciales = nuevoCasosEspeciales;
}

inline bool Tokenizador::CasosEspeciales()
{
	return casosEspeciales;
}

inline void Tokenizador::PasarAminuscSinAcentos(const bool& nuevoPasarAminuscSinAcentos)
{
	pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

inline bool Tokenizador::PasarAminuscSinAcentos()
{
	return pasarAminuscSinAcentos;
}

string Tokenizador::getMinusSinAcentos(const string& token) const
{
	string auxToken = "";

	for(int i = 0; i < token.size(); i++)
	{
		switch((unsigned char)token[i])
		{	// Codifiacion ISO-8859
			case 225: case 193:
				auxToken += 'a';
				break;
			case 233: case 201:
				auxToken += 'e';
				break;
			case 237: case 205:
				auxToken += 'i';
				break;
			case 243: case 211:
				auxToken += 'o';
				break;
			case 250: case 218:
				auxToken += 'u';
				break;
			default:
				if(token[i] >= 'A' && token[i] <= 'Z')
					auxToken += tolower(token[i]);
				else
					auxToken += token[i];
				break;
		}
	}

	return auxToken;
}

bool Tokenizador::casoEspecial(const string& token) const
{/*
	switch(status)
	{
		case NINGUNO:
			if(token.substr(0, 5) == "http:" || token.substr(0, 6) == "https:" || token.substr(0, 5) == "ftp:")
			{
				status = URL;
				//specialCaseToken = "";
				return true;
			}

			break;
		case URL:
			if(urlDelimiters.find(token[token.length()-1]))
				return true;
			else
			{
				status = NINGUNO;
				return false;
			}
			break;
		case REAL:
			break;
		case EMAIL:
			break;
	}

	return false;
	*/
}











