#include <iostream> 
#include <string>
#include <list> 
#include <sys/resource.h>
#include "tokenizador.h"

using namespace std;

///////// Comprobación de que vacíe la lista resultado

void imprimirListaSTL(const list<string>& cadena)
{
        list<string>::const_iterator itCadena;
        for(itCadena=cadena.begin();itCadena!=cadena.end();itCadena++)
        {
                cout << (*itCadena) << ", ";
        }
        cout << endl;
}

double getcputime(void) {
struct timeval tim;
struct rusage ru;
getrusage(RUSAGE_SELF, &ru);
tim=ru.ru_utime;
double t=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
tim=ru.ru_stime;
t+=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
return t;
}


int
main(void)
{
	bool kCasosEspeciales = true, kpasarAminusculas = false;

	list<string> lt1, lt2;

	Tokenizador a("-#", true, false);
	list<string> tokens;

	//a.Tokenizar("@alu.ua.es", tokens);

	//a.Tokenizar("src/tokenizador11.cpp", "salidaprueba.txt");

	a.TokenizarListaFicheros("aux/archivo/listaFicheros.txt.corto");
	long double init=getcputime();
	//a.TokenizarDirectorio("aux/archivo/corpus/");
	long double end=getcputime();

	cout << "Ha tardado " << end-init<<endl;
}
