/*
 * ProcesadorRequest.h
 *
 *  Created on: 04/11/2011
 *      Author: pablo
 */

#ifndef PROCESADORREQUEST_H_
#define PROCESADORREQUEST_H_

#include "Configuracion.h"
#include "HTTP_Request.h"
#include "HTTP_Response.h"
#include "Mutex.h"

/**
 * Clase encargada de procesar una request entrante al server.
 * El procesamiento consiste en:
 * 	- Verificar el usuario si es un servidor protegido
 * 	- Identificar el tipo
 * 	- Si es dinamico, ejecutar y generar response
 * 	- Si es estatico, devolver informacion con el tipo asociado en la configuracion
 */
class ProcesadorRequest {
private:
	const Configuracion& config;
    bool autentificar(HTTP_Request * pedido);
    HTTP_Response *exigirAutentificacion();
    std::string crearDirectorioTemporalParaElCGI();
    static int contador;
    static Mutex mutex;
public:
    /**
     * Constructor
     * @param c es la configuracion que esta utilizando el servidor
     */
	explicit ProcesadorRequest(const Configuracion& c);

	/**
	 * Destructor
	 */
	virtual ~ProcesadorRequest();

	/**
	 * Metodo encargado de procesar un pedido.
	 * @param pedido es el pedido a procesar
	 * @return es la respuesta generada por el procesamiento del request.
	 */
	HTTP_Response* procesar(HTTP_Request* pedido);
};

#endif /* PROCESADORREQUEST_H_ */
