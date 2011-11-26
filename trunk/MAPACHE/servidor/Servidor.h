/*
 * Servidor.h
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "Configuracion.h"

/**
 * Una vez que se tiene una configuración válida, esta clase es la encargada de correr un
 * servidor con esa configuración.
 */
class Servidor {
private:
	const Configuracion& config;
	bool reiniciando;
public:
	/**
	 * Contructor
	 * @param c es una configuración con la que se desea armar el servidor.
	 * @param reiniciando igual a true indica que se esta reiniciando el servidor. Si es falso entonces solo inicia.
	 */
	Servidor(const Configuracion& c , bool reiniciando = false);

	/**
	 * Destructor
	 */
	virtual ~Servidor();

	/**
	 * Comienza con la ejecución del servidor.
	 * @return 0 si tuvo exito, 1 si no pudo conectar el socket.
	 */
	int start();
};

#endif /* SERVIDOR_H_ */
