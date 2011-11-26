/*
 * ProcesadorTipoEstatico.h
 *
 *  Created on: 09/11/2011
 *      Author: pablo
 */

#ifndef PROCESADORTIPOESTATICO_H_
#define PROCESADORTIPOESTATICO_H_

#include "IProcesador.h"
#include "Configuracion.h"

/**
 * Clase encargada de procesar aquellos tipos que son estaticos.
 */
class ProcesadorTipoEstatico: public IProcesador {
private:
	const Configuracion& config;
public:
	/**
	 * Constructor
	 * @param c es la configuracion del servidor.
	 */
	ProcesadorTipoEstatico(const Configuracion& c);

	/**
	 * Destructor
	 */
	virtual ~ProcesadorTipoEstatico();

	/**
	 * Implementa el metodo procesar para el tipo estatico.
	 * @param pedido es el pedido a procesar. Ya se sabe que es de tipo estatico
	 * @return response generado por el pedido
	 */
	HTTP_Response* procesar(HTTP_Request* pedido);
};

#endif /* PROCESADORTIPOESTATICO_H_ */
