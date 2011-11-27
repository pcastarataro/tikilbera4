#ifndef SEPARADORESVALIDOS_H_
#define SEPARADORESVALIDOS_H_

#include "Constantes.h"
#include <list>

using std::list;
/*  Listado de los caracteres separadores para un define
 *  que el programa considera validos.
 */
class SeparadoresValidos {
private:
	list<char> listado;

public:
	/**
	 * Constructor
	 */
	SeparadoresValidos() {
		listado.push_back('/');
		listado.push_back('*');
		listado.push_back('+');
		listado.push_back('-');
		listado.push_back('=');
		listado.push_back(';');
		listado.push_back(',');
		listado.push_back('.');
		listado.push_back('%');
		listado.push_back('&');
		listado.push_back('!');
		listado.push_back(BARRA_N);
		listado.push_back('(');
		listado.push_back(')');
		listado.push_back('[');
		listado.push_back(']');
		listado.push_back('}');
		listado.push_back('{');
		listado.push_back('\\');
		listado.push_back('|');
		listado.push_back(MAYOR);
		listado.push_back(MENOR);
		listado.push_back(BARRA_R);
		listado.push_back(BLANCO);
		listado.push_back(TABULACION);
	}
	/**
	 * Decide si un separador es valido.
	 * @param car Caracter separador
	 * @return bool
	 */
	bool esSeparadorValido(char car) {
		bool encontrado = false;
		list<char>::iterator it = listado.begin();

		while (it != listado.end() && !encontrado) {
			if (*it == car)
				encontrado = true;
			else
				it++;
		}

		return encontrado;
	}
	/**
	 * Destructor
	 */
	~SeparadoresValidos() {
	}
};
#endif /* SEPARADORESVALIDOS_H_ */
