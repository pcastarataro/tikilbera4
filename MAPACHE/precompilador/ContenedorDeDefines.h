#ifndef CONTENEDORDEDEFINES_H_
#define CONTENEDORDEDEFINES_H_

#include "Constantes.h"
#include "Utilitarias.h"
#include <string.h>

	/*  Entidad que almacena, establece, y devuelve define`s.
	 *  Se hace uso de lo que podemos considerar como una matriz bidimensional
	 *  de punteros a cadenas (de long "LONGITUD_VALOR_DEFINE")
	 *  con CANT_MAX_DEFINES filas y 2 columnas,
	 *  una correspondiente al nombre del define
	 *  y otra al valor del mismo.
	 *  Se garantiza que todas las cadenas almacenadas terminan en NULL,
	 *  por lo que se puede utilizar sobre ellos, de forma segura,
	 *  las funciones strcat, strcpy, etc.
	 *  */
class ContenedorDeDefines {
private:
	Utilitarias util;
	char matrizDeDefines[CANT_MAX_DEFINES][2][LONGITUD_VALOR_DEFINE];
	int indexMatrizDefines;
	int indiceDeLosDefinesDentroDeLaMatriz;
	int indiceDeLosValoresDentroDeLaMatriz;
public:
	/**
	 * Constructor
	 */
	ContenedorDeDefines() {
		int a = 0;
		char* aux = (char*)"init";
		int sizeAux = strlen(aux);

		indexMatrizDefines = -1;
		indiceDeLosDefinesDentroDeLaMatriz = 0;
		indiceDeLosValoresDentroDeLaMatriz = 1;

		for (a = 0; a < CANT_MAX_DEFINES; a++) 
			setDefineYSuValor(aux, sizeAux, aux, sizeAux, a);
	}
	/**./Precompilador.cpp:20:  Lines should be <= 80 characters long  [whitespace/line_length] [2]
	 *
	 * Devuelve un puntero a una cadena con el nombre del define.
	 * @param indice Posicion del nombre del define dentro de la matriz.
	 * @return char*
	 */
	char* getDefine(int indice) {
		return matrizDeDefines[indice][indiceDeLosDefinesDentroDeLaMatriz];
	}
	/**
	 * Devuelve un puntero a una cadena con el valor del define.
	 * @param indice Posicion del valor del define dentro de la matriz.
	 * @return char*
	 */
	char* getValorDefine(int indice) {
		return matrizDeDefines[indice][indiceDeLosValoresDentroDeLaMatriz];
	}
	/**
	 * Setea un nombre de define y su valor en la estructura, en la posicion indice.
	 * @param newDefine nombre del define.
	 * @param largo del nombre del define.
	 * @param newVdefine valor del define.
	 * @param largo del valor del define.
	 * @param indice Posicion del define dentro de la matriz.
	 * @return void
	 */
	void setDefineYSuValor(char* newDefine,
			int sizeDefine,	char* newVdefine, int sizeVdefine, int indice) {
		char* define = getDefine(indice);
		char* vDefine = getValorDefine(indice);
		
		util.copiarCadenaYAgregarNullAlFinal(define, newDefine, sizeDefine);
		util.copiarCadenaYAgregarNullAlFinal(vDefine, newVdefine, sizeVdefine);
	}
	/**
	 * Busca un nombre de define determinado en la estructura.
	 * @param buscado nombre del define buscado.
	 * @param size longitud del nombre del define buscado.
	 * @return true Si lo halla y false en caso contrario.
	 */
	bool existeEsteDefine(char* buscado, int size) {
		int k = -1;
		bool salir = false;
		bool encontrado = false;
	
		while (!salir && !encontrado) {
			k++;
			
			if (strncmp(buscado, getDefine(k), size) == 0) {
				encontrado = true;
				salir = true;
			} else if (k >= indexMatrizDefines)
				salir = true;
		}
		return encontrado;
	}
	/**
	 * Incrementa en uno el valor de indexMatrizDefines.
	 * @return void
	 */
	void incrementarIndex() {indexMatrizDefines++;}
	/**
	 * Devuelve el valor de indexMatrizDefines.
	 * @return int
	 */	
	int getIndexActual() {return indexMatrizDefines;}
	/**
	 * Destructor
	 */
	~ContenedorDeDefines() {}
};

#endif /* CONTENEDORDEDEFINES_H_ */
