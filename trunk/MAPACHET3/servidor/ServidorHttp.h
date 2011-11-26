/*
 * ServidorHttp.h
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#ifndef SERVIDORHTTP_H_
#define SERVIDORHTTP_H_

#include "Thread.h"
#include "TCPSocket.h"
#include "Configuracion.h"
#include "ManejadorClienteHTTP.h"
#include "AdministradorClientes.h"
#include <list>

/**
 * Clase encargada de simular un servidor HTTP
 * Un servidor HTTP tiene como funcion escuchar y responder
 * peticiones que respetan el protocolo.
 */
class ServidorHttp: public Thread {
private:
	const Configuracion& config;
	TCPSocket socketHTTP;
	AdministradorClientes* administradorClientes;
	bool reiniciando;
public:
	/**
	 * Contructor
	 * @param c es la configuracion que utilizara el servidor.
	 */
	ServidorHttp(const Configuracion& c , bool reiniciando = false);

	/**
	 * Destructor
	 */
	virtual ~ServidorHttp();

	/**
	 * Empieza a ejecutar el servidor HTTP.
	 */
	void run();

	/**
	 * Detiene al servidor HTTP.
	 */
	void apagar();
};

#endif /* SERVIDORHTTP_H_ */
