#include <iostream> 
#include <string>
#include <list> 
#include "tokenizador.h"

using namespace std;

///////// ComprobaciÃ³n de que vacÃ­e la lista resultado

void imprimirListaSTL(const list<string>& cadena)
{
        list<string>::const_iterator itCadena;
        for(itCadena=cadena.begin();itCadena!=cadena.end();itCadena++)
        {
                cout << (*itCadena) << "\t";
        }
        cout << endl;
}

int
main(void)
{
	bool kCasosEspeciales = true, kpasarAminusculas = false;

	list<string> lt1, lt2;

Tokenizador a("-#", true, false); 
list<string> tokens; 

a.DelimitadoresPalabra("@.,&");
a.Tokenizar("pal1 10.35% 10,35% 23.000,3% 23¤ 23.05¤ 23,05¤ 11$ 11.05$ 3º 4ª", tokens);
// La lista de tokens a devolver deberÃ­a contener: "pal1	10.35	%	10,35	%	23.000,3	%	23	Â¤	23.05	Â¤	23,05	Â¤	11	$	11.05	$	3	Âº	4	Âª"
	imprimirListaSTL(tokens);



}
