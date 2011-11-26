#ifndef PROCESADORPHP_H_
#define PROCESADORPHP_H_

#include <list>
#include <iterator>
#include <string>
#include <iostream>

using std::iterator;
using std::list;
using std::string;

class ProcesadorPHP {
public:
	/**
	 * Constructor
	 */
	ProcesadorPHP() {}
	/**
	 * Genera el comando para que sea ejecutado en una terminal.
	 * @param rutaPHP Ruta del archivo .php.
	 * @param listaParams Lista de strings. Cada string es un parametro.
	 * return string Comando generado.
	 */
	string armarComandoPHP(const string rutaPHP, std::list<string> listaParams);
	/**
	 * Parsea la cadena parametros y agrega cada ocurrencia a listaParams.
	 * Tambien parsea la ruta del PHP.
	 * @param rutaPHP
	 * @param parametros
	 * @param listaParams
	 * return false Si el parseo determina que no se trataba de un archivo .php. 
	 */
	bool extraerParametrosParaElPHP(string& rutaPHP, const string parametros, list<string>& listaParams);
	/**
	 * Destructor
	 */
	~ProcesadorPHP() {}
};

#endif /*PROCESADORPHP_H_*/
