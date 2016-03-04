#include <iostream> 
#include <string>
#include <list> 
#include <sys/resource.h>
#include "../include/tokenizador.h"

using namespace std;

void imprimirListaSTL(const list<string>& cadena)
{
        list<string>::const_iterator itCadena;
        for(itCadena=cadena.begin();itCadena!=cadena.end();itCadena++)
        {
                cout << (*itCadena) << ", ";
        }
        cout << endl;
}

void testURL()
{
    Tokenizador a(",", true, false);
    list<string> tokens;
    string s = "p0 http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es p1 p2";
    a.Tokenizar(s, tokens);
    imprimirListaSTL(tokens);
    // La lista de tokens a devolver debería contener: 
    //" p0, http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es, p1, p2"
    a.DelimitadoresPalabra("/ ");
    a.Tokenizar(s, tokens);
    imprimirListaSTL(tokens);
    // La lista de tokens a devolver debería contener: 
    //" p0, http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es, p1, p2"
    a.DelimitadoresPalabra("/ &");
    a.Tokenizar(s, tokens);
    imprimirListaSTL(tokens);
    // La lista de tokens a devolver debería contener: 
    //" p0, http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es, p1, p2"
    a.DelimitadoresPalabra("/&");
    s = "p0 hhttp://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013 p1 p2";
    a.Tokenizar(s, tokens);
    imprimirListaSTL(tokens);
    // La lista de tokens a devolver debería contener: 
    //" p0, hhttp:, intime.dlsi.ua.es:8080, dossierct, index.jsp?lang=es, status=probable, date=22-01-2013, p1, p2"
}

void testNUMEROS()
{
    Tokenizador a(",", true, false);
    list<string> lt1;
    a.DelimitadoresPalabra("@.,&");
    a.Tokenizar("pal1 10.000,34 10,000.34 10.000.123.456.789.009,34 10,000,123,456,789,009.34 20.03 40,03 2005 10. 20, 10.0 20,0 La 20,12.456,7.8.9,", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "pal1 10.000,34 10,000.34 10.000.123.456.789.009,34 10,000,123,456,789,009.34 20.03 40,03 2005 10 20 10.0 20,0 La 20,12.456,7.8.9"
    a.Tokenizar(".34 ,56", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "0.34 0,56"
    //a.Tokenizar("pal1 10.35% 10,35% 23.000,3% 23,5€ 23.05€ 23,05€ 11.1$ 11.05$ 3.4º 4,3ª", lt1);
    //imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "pal1 10.35 % 10,35 % 23.000,3 % 23,5 € 23.05 € 23,05 € 11.1 $ 11.05 $ 3.4 º 4.3 ª"
    a.Tokenizar("pal1 10.00a 10.000.a.000 10/12/85 1,23E+10", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener (no extraería números sino acrónimos): "pal1 10.00a 10.000.a.000 10/12/85 1 23E+10"
    a.Tokenizar("pal1&10.00@10.000&abc@10/12/85", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener (extraería un email): "pal1 10.00 10.000 abc@10/12/85"
    a.Tokenizar(".34@@&,56", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "0.34 0,56"
    a.Tokenizar("...10.000.a.000 ,,23.05 10/12/85 1,23E+10", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener (extraería un acrónimo): "10.000.a.000 23.05 10/12/85 1 23E+10"
    a.DelimitadoresPalabra("");
    a.Tokenizar("...10.000.a.000 ,,23.05 10/12/85 1,23E+10", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "...10.000.a.000 ,,23.05 10/12/85 1,23E+10"
    a.DelimitadoresPalabra(".,");
    a.Tokenizar(".........31....... ,,,,,,,54,,,,,,,", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devovler deber�a contener "31, 54,"
}

void testEMAIL()
{

    Tokenizador a(",", true, false);
    list<string> tokens;
    a.DelimitadoresPalabra("@.&");
    a.Tokenizar("catedraTelefonicaUA@iuii.ua.es p1 p2", tokens);
    // La lista de tokens a devolver debería contener: "catedraTelefonicaUA@iuii.ua.es, p1, p2"
    imprimirListaSTL(tokens);
    a.Tokenizar("pal1 @iuii.ua.es p1 p2", tokens);
    // La lista de tokens a devolver debería contener: "pal1, iuii.ua.es, p1, p2"
    imprimirListaSTL(tokens);
    a.Tokenizar("pal1 cat@iuii.ua.es@cd p1 p2", tokens);
    // La lista de tokens a devolver debería contener: "pal1, cat, iuii.ua.es@cd, p1, p2"
    imprimirListaSTL(tokens);
    a.DelimitadoresPalabra("&.");
    a.Tokenizar("catedraTelefonicaUA@iuii.ua.es p1 p2", tokens);
    // La lista de tokens a devolver debería contener: "catedraTelefonicaUA@iuii.ua.es, p1, p2"
    imprimirListaSTL(tokens);
    a.Tokenizar("pal1 @iuii.ua.es p1 p2", tokens);
    // La lista de tokens a devolver debería contener: "pal1, @iuii.ua.es, p1, p2"
    imprimirListaSTL(tokens);
    a.Tokenizar("pal1&@iuii.ua.es p1 p2", tokens);
    // La lista de tokens a devolver debería contener: "pal1, @iuii.ua.es, p1, p2"
    imprimirListaSTL(tokens);
    a.Tokenizar("pal1&catedra@iuii.ua.es p1 p2", tokens);
    // La lista de tokens a devolver debería contener: "pal1, catedra@iuii.ua.es, p1, p2"
    imprimirListaSTL(tokens);
    a.Tokenizar("pal1 cat@iuii.ua.es@cd p1 p2", tokens);
    // La lista de tokens a devolver debería contener: "pal1, cat@iuii.ua.es@cd, p1, p2"
    imprimirListaSTL(tokens);
}

void testACRONIMOS()
{

    Tokenizador a(",", true, false);
    list<string> lt1;
    a.DelimitadoresPalabra("@.&");
    a.Tokenizar("U.S.A p1 e.g. p2. La", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "U.S.A, p1, e.g, p2, La"
    a.Tokenizar("U..S.A p1 e..g. p2. La", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "U, S.A, p1, e, g, p2, La"

    a.Tokenizar("...U.S.A p1 e..g. p2. La", lt1);
    imprimirListaSTL(lt1);

    // La lista de tokens a devolver debería contener: "U.S.A, p1, e, g, p2, La"
    a.Tokenizar("Hack.4.Good p1 ", lt1);
    imprimirListaSTL(lt1);

    // La lista de tokens a devolver debería contener: "Hack.4.Good, p1" 

    a.DelimitadoresPalabra("");
    a.Tokenizar("U.S.A .U.S.A .p1 p1 e.g. p2. La", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "U.S.A, U.S.A, .p1, p1, e.g, p2., La"

    a.Tokenizar("U..S.A p1 e..g. p2. La", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "U..S.A, p1, e..g., p2., La"
    a.Tokenizar("...U.S.A p1 e..g. p2. La", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "...U.S.A, p1, e..g., p2., La"

    a.Tokenizar("a&U.S.A p1 e.g. p2. La", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "a&U.S.A, p1, e.g, p2., La"
    a.DelimitadoresPalabra("&");
    a.Tokenizar("a&U.S.A p1 e.g. p2. La", lt1);
    imprimirListaSTL(lt1);
    // La lista de tokens a devolver debería contener: "a, U.S.A, p1, e.g, p2., La"
}

void
testGUIONES()
{
	Tokenizador a("-#", true, false);
	list<string> tokens;
	a.Tokenizar("MS-DOS p1 p2 UN-DOS-TRES", tokens);
	imprimirListaSTL(tokens);
	// La lista de tokens a devolver debería contener: "MS-DOS, p1, p2, UN-DOS-TRES"
	a.Tokenizar("pal1 -MS-DOS p1 p2", tokens);
	imprimirListaSTL(tokens);
	// La lista de tokens a devolver debería contener: "pal1, MS-DOS, p1, p2"
	a.Tokenizar("pal1 MS-DOS#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);
	// La lista de tokens a devolver debería contener: "pal1, MS-DOS, p3, p1, p2"
	a.Tokenizar("pal1#MS-DOS#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);
	// La lista de tokens a devolver debería contener: "pal1, MS-DOS, p3, p1, p2"
	a.DelimitadoresPalabra("/ ");
	a.Tokenizar("MS-DOS p1 p2", tokens);
	imprimirListaSTL(tokens);
	// La lista de tokens a devolver debería contener: "MS-DOS, p1, p2"
	a.Tokenizar("pal1 -MS-DOS p1 p2", tokens);
	imprimirListaSTL(tokens);
	// La lista de tokens a devolver debería contener: "pal1, -MS-DOS, p1, p2"
	a.Tokenizar("pal1 MS-DOS#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);
	// La lista de tokens a devolver debería contener: "pal1, MS-DOS#p3, p1, p2"
	a.Tokenizar("pal1#MS-DOS#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);
	// La lista de tokens a devolver debería contener: "pal1#MS-DOS#p3, p1, p2"
        a.Tokenizar("--HO -A--", tokens);
        imprimirListaSTL(tokens);
        // "--HO, -A--"
        a.DelimitadoresPalabra("-");
        a.Tokenizar("R-- -A-- --A-- --A", tokens);
        imprimirListaSTL(tokens);
        // "R A A A"
}

int
main(void)
{
    testURL();
    testNUMEROS();
    testEMAIL();
    testACRONIMOS();
    testGUIONES();
}

