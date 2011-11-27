#ifndef IFDEFANIDADOS_H_
#define IFDEFANIDADOS_H_

#include "Constantes.h"
#include "Utilitarias.h"
#include "FlagsDePrograma.h"

/*  La estructura se cargara con 2 chars simbolicos: COMPILAR y NO_COMPILAR.
 *  Cada vez que se procese un ifdef o ifndef,indiceIfdefActual aumentara en 1.
 *  Cada vez que se procese un endif, indiceIfdefActual disminuira en 1.
 *  Hay un limite para la cantidad de ifdef/ifndef que se pueden almacenar
 */
class IfDefAnidados {
private:
	char tablaIfdef[ANIDAMIENTO_MAX];
	int indiceIfdefActual;
	/**
	 * Verifica que la profundidad de anidamiento no supere el maximo permitido.
	 * @param flags Si se superara el maximo, se setea el flag correspondiente.
	 * @return void
	 */
	void chequearProfundidadDeAnidamiento(FlagsDePrograma& flags) {
		if (indiceIfdefActual >= ANIDAMIENTO_MAX)
			flags.statusDelPrograma = ERROR_PROGRAMA;
	}
public:
	/**
	 * Constructor
	 */
	IfDefAnidados() {
		indiceIfdefActual = 0;
		tablaIfdef[0] = COMPILAR;
	}
	/**
	 * Determina si la ultima anidacion corresponde a COMPILAR.
	 * @return bool
	 */
	bool compilar() {
		return (tablaIfdef[indiceIfdefActual] == COMPILAR);
	}
	/**
	 * Anida en la estructura el codigo para COMPILAR o NO_COMPILAR
	 * @param codigo_A_Anidar Su valor puede ser COMPILAR o NO_COMPILAR solamente.
	 * @return void
	 */
	void anidar(char codigo_A_Anidar, FlagsDePrograma& flags) {
		indiceIfdefActual++;
		setValorAnidado(indiceIfdefActual, codigo_A_Anidar);
		chequearProfundidadDeAnidamiento(flags);
	}
	/**
	 * Ignora el valor de la ultima anidacion y disminuye en uno el valor de indiceIfdefActual.
	 * @return void
	 */
	void desanidar() {
		indiceIfdefActual--;
	}
	/**
	 * Invierte el valor de la ultima anidacion.
	 * @return void
	 */
	void invertirUltimoValorAnidado() {
		if (getUltimoValorAnidado() == COMPILAR)
			setValorAnidado(indiceIfdefActual, NO_COMPILAR);
		else
			setValorAnidado(indiceIfdefActual, COMPILAR);
	}
	/**
	 * Devuelve el valor de la ultima anidacion.
	 * @return char
	 */
	char getUltimoValorAnidado() {
		return tablaIfdef[indiceIfdefActual];
	}
	/**
	 * Cambia el valor de una anidacion, en la posicion pasada como parametro.
	 * @param pos Posicion en la que se realizara el cambio.
	 * @param c Codigo correspondiente a COMPILACION o NO_COMPILACION.
	 * @return void
	 */
	void setValorAnidado(int pos, char c) {
		tablaIfdef[pos] = c;
	}

	/**
	 * Destructor
	 */
	~IfDefAnidados() {
	}
};
#endif /* IFDEFANIDADOS_H_ */
