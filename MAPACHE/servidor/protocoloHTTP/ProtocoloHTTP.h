/*
 * ProtocoloHTTP.h
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#ifndef PROTOCOLOHTTP_H_
#define PROTOCOLOHTTP_H_

#include "../../common/sockets/TCPSocket.h"
#include "HTTP_Request.h"
#include "HTTP_Response.h"

/**
 * Clase que asbtrae el manejo de los sockets y el protocolo HTTP
 */
class ProtocoloHTTP {
private:
	TCPSocket* sock;
public:
	/**
	 * Constructor
	 * @param socket que utilizará el protocolo http. Este debe estar conectado.
	 */
	ProtocoloHTTP(TCPSocket* s);

	/**
	 * Destructor
	 */
	virtual ~ProtocoloHTTP();

	/**
	 * Recibe un pedido u operacion a travez del socket asociado
	 * En caso de desconexion arroja socket exception
	 * @return HTTP_Request con el pedido recibido
	 */
	HTTP_Request* recibirOperacion();

	/**
	 * Envia un HTTP_Response a traves del socket asociado.
	 * En caso de desconexion arroja socket exception
	 * @param r es la respuesta que se desea enviar.
	 */
	void enviarRespuesta(HTTP_Response* r);
};

#endif /* PROTOCOLOHTTP_H_ */
