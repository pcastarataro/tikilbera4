#ifndef UTILITARIAS_H_
#define UTILITARIAS_H_

#include "Constantes.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>

using std::string;

/**
 * Conjunto de funciones auxiliares de manejo de cadenas y chars
 */
class Utilitarias {
public:
	/**
	 * Constructor
	 */
	Utilitarias() {
	}
	/**
	 * Destructor
	 */
	~Utilitarias() {
	}
	/**
	 * Copia el contenido de la segunda cadena en la primera y agrega un caracter nulo al final.
	 * @param char1 Cadena de caracteres.
	 * @param char2 Cadena de caracteres.
	 * @param sizeCh2 Longitud de char2.
	 * @return int Largo de la cadena.
	 */
	void copiarCadenaYAgregarNullAlFinal(char* char1, char* char2, int sizeCh2) {
		strncpy(char1, char2, sizeCh2);
		char1[sizeCh2] = (int) NULL;
	}
	/**
	 * Esta funcion se diferencia de strlen en que determina el fin de la cadena
	 * cuando encuentra alguno de los caracteres dentro de vectorDeTopes.
	 * @param cadena Cadena de caracteres sobre la que se quiere calcular el largo.
	 * @param vectorDeTopes Vector de caracteres que se consideran finalizadores de cadena.
	 * @param sizeVec Cantidad de caracteres dentro de vectorDeTopes.
	 * @return int Largo de la cadena.
	 */
	int getLargoCadena(char* cadena, char* vectorDeTopes, int sizeVec) {
		int contador = 0;
		string cadenaStr(cadena);
		size_t longMenor = 10000000;
		size_t longAux = -1;

		while (contador < sizeVec) {
			longAux = cadenaStr.find(vectorDeTopes[contador], 0);

			if (longAux < longMenor && longAux != cadenaStr.npos)
				longMenor = longAux;

			contador++;
		}

		return longMenor;
	}

	/**
	 * Determina si la cadena de caracteres puede ser interpretada como un numero.
	 * @param c Cadena de caracteres.
	 * @return bool
	 */
	bool esNumero(char* c) {
		int integer = atoi(c);
		bool retorno = false;

		if (integer == 0) {
			if (*c != '0')
				retorno = false;
			else
				retorno = true;
		} else
			retorno = true;
		return retorno;
	}
};
#endif /* UTILITARIAS_H_ */
