/*
 * IProcesador.h
 *
 *  Created on: 04/11/2011
 *      Author: pablo
 */

#ifndef IPROCESADOR_H_
#define IPROCESADOR_H_

#include "HTTP_Request.h"
#include "HTTP_Response.h"

/**
 * Interfaz utilizada para representar a todos los procesadores de todos los tipos dentro
 * del servidor.
 */
class IProcesador {
public:
	/**
	 * Destructor
	 */
	virtual ~IProcesador();

	/**
	 * Metodo abstracto puro que deben implementar todas los procesadores que se implementen.
	 * @param pedido es el pedido a procesar
	 * @return es la respuesta generada por el pedido
	 */
	virtual HTTP_Response* procesar(HTTP_Request* pedido) = 0;

	/**
	 * Metodo que sirve para extraer la extension de un pedido.
	 */
	static std::string obtenerExtension(const std::string& pedidoStr) {
	    size_t pos = pedidoStr.find_last_of(' ');
	    size_t pos_punto = pedidoStr.find_last_of('.', pos);
	    std::string extension = pedidoStr.substr(pos_punto + 1, pos - pos_punto);
	    return extension;
	}
};

#endif /* IPROCESADOR_H_ */
