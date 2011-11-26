/*
 * ManejadorClienteHTTP.h
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#ifndef MANEJADORCLIENTEHTTP_H_
#define MANEJADORCLIENTEHTTP_H_

#include "Thread.h"
#include "TCPSocket.h"
#include "Configuracion.h"
#include "HTTP_Request.h"
#include "HTTP_Response.h"

/**
 * Clase encargada de manejar un cliente durante el proceso del HTTP
 */
class ManejadorClienteHTTP: public Thread {
private:
	TCPSocket* sockCliente;
	const Configuracion& config;
	int offsetInicioSegundos;
protected:
	void run();
public:
	/**
	 * Constructor
	 * @sock es el socket del cliente entrante al servidor ya conectado.
	 * @c es la configuracion asociada al servidor
	 */
	ManejadorClienteHTTP(TCPSocket* sock , const Configuracion& c);

	/**
	 * Destructor
	 */
	virtual ~ManejadorClienteHTTP();

	/**
	 * Envia una respuesta al cliente asociado al manejador.
	 * Este metodo es utilizado cuando este hilo de ejecucion esta detenido.
	 * @param respuesta es la respuesta que se desea enviar
	 */
	void enviarMsg(HTTP_Response* respuesta);

	/**
	 * Devuelve el ip del cliente conectado.
	 */
	std::string getIpCliente() const;

	/**
	 * Detiene la ejecucion del manejador.
	 */
	void apagar();

	/**
	 * Devuelve el offset en segundos del cliente asociado al menajedador
	 */
	int getOffsetSegundos() const;
};

#endif /* MANEJADORCLIENTEHTTP_H_ */
