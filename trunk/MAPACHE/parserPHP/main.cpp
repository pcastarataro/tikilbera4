#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include "ProcesadorPHP.h"

using std::cout;
using std::endl;
using std::string;
using std::list;

	/*	El segundo arg corresponde al path en donde se almacenaran los archivos
	 *  temporales que genere el programa (este CGI no genera ninguno).
	 *  El tercer arg corresponde a la URI.*/
int main(int argc, char** argv) {
	setenv("URI_PARA_PARSER_PHP_ALTERNATIVO", argv[2], 1);
	
	if (argc < 3)
		cout << "PARSER_PHP: cantidad de parametros erronea: " << argc << ". Deberia ser igual a 3" << endl;
	else {
		ProcesadorPHP procesador;
		list<string> listaParams;
		string parametros(argv[2]);
		string rutaPHP;
		
		chdir("/");
		
		bool parseoParametrosOK = procesador.extraerParametrosParaElPHP(rutaPHP, parametros, listaParams);
		if (parseoParametrosOK) 
			system(procesador.armarComandoPHP(rutaPHP, listaParams).c_str());
		else cout << "error, el recurso no es .php: " << argv[2] << endl;
	}
	return 0;
}
