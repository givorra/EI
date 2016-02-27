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
	pasarAminuscSinAcentos(minuscSinAcentos)
	//status(NINGUNO)
{}

Tokenizador::Tokenizador():
	delimiters(",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@"),
	casosEspeciales(true),
	pasarAminuscSinAcentos(false)
	//status(NINGUNO)
{}

Tokenizador::Tokenizador(const Tokenizador& t):
	delimiters(t.delimiters),
	casosEspeciales(t.casosEspeciales),
	pasarAminuscSinAcentos(t.pasarAminuscSinAcentos)
	//status(t.status)
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
	// Limpiamos lista de tokens
	if(tokens.size() > 0)
		tokens.clear();

	if(casosEspeciales)
		tokenizarConCasosEspeciales(str, tokens);
	/*
	TCasoEspecial status = URL;
	string token;
	string::size_type lastPos = str.find_first_not_of(delimiters,0);
	string::size_type pos = str.find_first_of(delimiters,lastPos);

	while(string::npos != pos || string::npos != lastPos)
	{
		if(!casosEspeciales || !casoEspecial(str.substr(lastPos, pos+1 - lastPos), status))	// Manda token con delimitador
		{
			if(pasarAminuscSinAcentos)		// Si se convierte el string entero, solo se hace una vez
				token = getMinusSinAcentos(str.substr(lastPos, pos - lastPos));
			else
				token = str.substr(lastPos, pos - lastPos);

			tokens.push_back(token);
			lastPos = str.find_first_not_of(delimiters, pos);
			status = INIT;
		}
		pos = str.find_first_of(delimiters, lastPos);
	}*/
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
	if(!tokens.empty())
		tokens.clear();
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

void Tokenizador::DelimitadoresPalabra(const string& nuevoDelimiters)
{
	delimiters = nuevoDelimiters;
}

void Tokenizador::AnyadirDelimitadoresPalabra(const string& nuevoDelimiters)
{
	//sort(nuevoDelimiters.begin(), nuevoDelimiters.end());

	char lastDelimiter = 0;

	for(int i = 0; i < nuevoDelimiters.size(); i++)
	{
		if(nuevoDelimiters[i] != lastDelimiter && delimiters.find(nuevoDelimiters[i]) != string::npos)
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

void Tokenizador::tokenizarConCasosEspeciales(const string& str, list<string>& tokens) const
{
	TCasoEspecial status = URL;
	string::size_type pos = 0;
	string::size_type npos = 0;
	bool exit 					= false;
	bool addCero 				= false;
	bool specialRealDelimiter 	= false;
	int nLeftPointAcronim 		= 0;
	int nRigthPointAcronim 		= 0;
	int nRigthGuionGuion 		= 0;

	while(!exit)
	{
		char c = str[npos];
		switch(status)
		{
			case URL:
			{
				if((pos + 5 < str.length() && str[pos] == 'h' && str[pos+1] == 't' && str[pos+2] == 't' && str[pos+3] == 'p' &&
						(str[pos+4] == ':' || (pos + 6 < str.length() && str[pos+4] == 's' && str[pos+5] == ':'))) ||
				   (pos + 4 < str.length() && str[pos] == 'f' && str[pos+1] == 't' && str[pos+2] == 'p' && str[pos+3] == ':'))
				{
					status = URL1;
					npos = str.find_first_of(':', pos);
				}
				else if(c != '.' && c != ',' && isDelimiter(c))	// Si el primer caracter analizado es un delimitador, lo saltamos
					++pos;
				else
					status = REAL;
				break;
			}
			case URL1:
			{
				while(true)
				{
					npos = str.find_first_of(getDelimiters(), npos+1);
					if(urlDelimiters.find(str[npos]) == string::npos || str[npos] == '\0')	// Si encuentra un delimitador que no es de URL o se acaba el string...
						break;
				}
				status = TOKENIZAR;
				break;
			}

			// Cuando se asigne un estado terminal, hacer también las particularidades de ese estado
			case REAL:
			{
				npos = pos;
				c = str[npos];
				if(c == '.' || c == ',')
					status = REAL1;	// AÑADIR 0
				else if(c >= '0' && c <= '9')
					status = REAL2;
				else
					status = EMAIL;
				break;
			}
			case REAL1:
				if(c >= '0' && c <= '9')
				{
					addCero = true;
					status = REAL2;
				}
				else
					status = EMAIL;
				break;
			case REAL2:
				if(c == '.' || c == ',')
					status = REAL3;
				else if(isDelimiter(c))
					status = TOKENIZARREAL;
				else if(findRealDelimiters(c))
				{
					specialRealDelimiter = true;
					status = REAL5;
				}
				else if(c < '0' || c > '9')
					status = EMAIL;
				break;
			case REAL3:
				if(c >= '0' && c <= '9')
					status = REAL2;
				else if(isDelimiter(c))
				{
					// status = REAL4
					status = TOKENIZARREAL;
					--npos;
				}
				else
					status = EMAIL;
				break;
			case REAL5:
				if(isDelimiter(c))
				{
					//status = REAL6;
					status = TOKENIZARREAL;
					--npos;
				}
				else
					status = EMAIL;
				break;
			case EMAIL:
				npos = pos;
				c = str[npos];
				if(c == '@')
					status = EMAIL2;
				else if(isDelimiter(c))		// PROBAR ESTO
					status = ACRONIMO;
				else
					status = EMAIL1;
				break;
			case EMAIL1:
				if(c == '@')
					status = EMAIL2;
				else if(emailDelimiters.find(c) != string::npos)
				{}	// Para excluir los emailDelimiter y mantenerse en el estado
				else if(isDelimiter(c))
					status = ACRONIMO;
				break;
			case EMAIL2:
				if(c == '@')
					status = ACRONIMO;
				else if(emailDelimiters.find(c) != string::npos)
					status = EMAIL3;
				else if(isDelimiter(c))
					status = EMAIL3;
				break;
			case EMAIL3:
				if(c == '@')
					status = ACRONIMO;
				else if(emailDelimiters.find(c) != string::npos)
				{}
				else if(isDelimiter(c))
					status = TOKENIZAR;
				break;
			case ACRONIMO:
				npos = pos;
				c = str[npos];
				if(c == '.')
				{
					++nLeftPointAcronim;
					status = ACRONIMO1;
				}
				else if(isDelimiter(c))
					status = GUION;
				else
					status = ACRONIMO2;
				break;
			case ACRONIMO1:
				if(isDelimiter(c) || c == '.')
					status = GUION;
				//else if(c == '.')
				//	++nLeftPointAcronim;
				else
					status = ACRONIMO2;
				break;
			case ACRONIMO2:
				if(c == '.')
				{
					++nRigthPointAcronim;
					status = ACRONIMO6;
				}
				else if(isDelimiter(c))
					status = GUION;
				break;
			case ACRONIMO3:
				if(c == '.')
				{
					++nRigthPointAcronim;
					status = ACRONIMO4;
				}
				else if(!isDelimiter(c))
				{
					--nRigthPointAcronim;;
					status = ACRONIMO5;
				}
				else	// Delimitador
				{
					status = TOKENIZARACRONIMO;
				}
				break;
			case ACRONIMO4:
				if(c == '.')
					++nRigthPointAcronim;
				else if(isDelimiter(c))
					status = TOKENIZARACRONIMO;
				else
					status = GUION;
				break;
			case ACRONIMO5:
				if(c == '.')
				{
					++nRigthPointAcronim;
					status = ACRONIMO3;
				}
				else if(isDelimiter(c))
					status = TOKENIZARACRONIMO;

				break;
			case ACRONIMO6:
				if(c == '.' || isDelimiter(c))
					status = GUION;
				else
				{
					--nRigthPointAcronim;
					status = ACRONIMO5;
				}
				break;
			case GUION:
				npos = pos;
				c = str[npos];
				if(isDelimiter(c))
					status = NORMAL;
				else
					status = GUION1;
				break;
			case GUION1:
				//if(c != '-' && isDelimiter(c))
				if(c == '-')
					status = GUION2;
				else if(isDelimiter(c))
					status = NORMAL;
				break;
			case GUION2:
				if(c == '-' || isDelimiter(c))
					status = NORMAL;
				else
					status = GUION3;
				break;
			case GUION3:
				if(c == '-')
				{
					++nRigthGuionGuion;
					status = GUION4;
				}
				else if(isDelimiter(c))
					status = TOKENIZARGUION;
				break;
			case GUION4:
				if(c == '-')
				{
					++nRigthGuionGuion;
					status = GUION5;
				}
				else if(isDelimiter(c))
					status = TOKENIZARGUION;
				else
				{
					--nRigthGuionGuion;
					status = GUION3;
				}
				break;
			case GUION5:
				if(c == '-')
					++nRigthGuionGuion;
				else if(isDelimiter(c))
					status = TOKENIZARGUION;
				else
					status = NORMAL;
				break;
			case NORMAL:
				if(!isDelimiter(str[pos]))
				{
					npos = str.find_first_of(getDelimiters(), pos);
					status = TOKENIZAR;
					break;
				}
				else
					++pos;
		}
		if(status == TOKENIZAR)
		{
			tokens.push_back(str.substr(pos, npos-pos));
			cout <<"--"+tokens.back() << endl;

			status 					= URL;
			pos 					= npos+1;
			addCero 				= false;
			specialRealDelimiter 	= false;
			nLeftPointAcronim 		= 0;
			nRigthPointAcronim 		= 0;
			nRigthGuionGuion		= 0;

			//if(str[npos] == '\0')
			if(npos >= str.length())
				exit = true;
		}
		else if(status == TOKENIZARREAL)
		{

			if(addCero)
			{
				tokens.push_back("0"+str.substr(pos, npos-pos));
			}
			else
				tokens.push_back(str.substr(pos, npos-pos));
			cout <<"--"+tokens.back() << endl;

			if(specialRealDelimiter == true)	// Si ha encontrado un realDelimiter retrocede una posicion para prodesarlo a parte
				--npos;

			status 					= URL;
			pos 					= npos+1;
			addCero 				= false;
			specialRealDelimiter 	= false;
			nLeftPointAcronim 		= 0;
			nRigthPointAcronim 		= 0;
			nRigthGuionGuion		= 0;


			if(str[npos] == '\0')
				exit = true;
		}
		else if(status == TOKENIZARACRONIMO)
		{
			tokens.push_back(str.substr(pos+nLeftPointAcronim, (npos-nRigthPointAcronim) - (pos+nLeftPointAcronim)));
			cout <<"--"+tokens.back() << endl;

			status 					= URL;
			pos 					= npos+1;
			addCero 				= false;
			specialRealDelimiter 	= false;
			nLeftPointAcronim 		= 0;
			nRigthPointAcronim 		= 0;
			nRigthGuionGuion		= 0;

			if(str[npos] == '\0')
				exit = true;
		}
		else if(status == TOKENIZARGUION)
		{
			tokens.push_back(str.substr(pos, (npos-nRigthGuionGuion) - pos));
			cout <<"--"+tokens.back() << endl;

			status 					= URL;
			pos 					= npos+1;
			addCero 				= false;
			specialRealDelimiter 	= false;
			nLeftPointAcronim 		= 0;
			nRigthPointAcronim 		= 0;
			nRigthGuionGuion		= 0;

			if(str[npos] == '\0')
				exit = true;

		}
		if(npos != string::npos)
			++npos;
	}
}

string Tokenizador::getDelimiters() const
{
	return " "+delimiters;
}

bool Tokenizador::isDelimiter(char c) const
{
	if(c == '\0')
		return true;
	else if(c == ' ')
		return true;
	else if(delimiters.find(c) != string::npos)
		return true;
	else
		return false;
}

bool Tokenizador::findRealDelimiters(char c) const
{
	//if(c == '€')
	//	return true;
	if(realDelimiters.find(c) != string::npos)
		return true;
	else
		return false;
}












