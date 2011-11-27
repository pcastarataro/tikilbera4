#ifndef FLAGSDEPROGRAMA_H_
#define FLAGSDEPROGRAMA_H_

#include "Constantes.h"
/**
 * Representa el estado de las variadas banderas que tiene el programa.
 */
class FlagsDePrograma {
public:
	bool statusDelPrograma;
	bool comentarioAbierto;
	bool todaviaTieneComentarios;
	bool comentarioAbiertoEnLineaActual;
	/**
	 * Constructor
	 */
	FlagsDePrograma() {
		statusDelPrograma = OK_PROGRAMA;
		comentarioAbierto = false;
		todaviaTieneComentarios = false;
		comentarioAbiertoEnLineaActual = false;
	}
	/**
	 * Determina si la linea en proceso esta totalmente comentada.
	 * @return bool
	 */
	bool lineaNoEstaTotalmenteComentada() {
		return (!comentarioAbierto || comentarioAbiertoEnLineaActual);
	}
	/**
	 * Destructor
	 */
	~FlagsDePrograma() {
	}
};
#endif /* FLAGSDEPROGRAMA_H_ */
