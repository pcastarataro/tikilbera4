/*
 * ProtocoloHTTP.cpp
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#include "ProtocoloHTTP.h"
#include "../../common/sockets/exceptions/SocketException.h"

#define EOF_HTTP "\r\n\r\n"

ProtocoloHTTP::ProtocoloHTTP(TCPSocket* s) :
	sock(s) {
}

ProtocoloHTTP::~ProtocoloHTTP() {
}

HTTP_Request* ProtocoloHTTP::recibirOperacion() {
	std::string buffer = "";
	while (buffer.find(EOF_HTTP) == std::string::npos) {
		char c;
		sock->recibir(&c, sizeof(c));
		buffer += c;
	}
	HTTP_Request* operacionRecibida = new HTTP_Request(buffer);
	std::string bufferContenido;
	int tamanio = operacionRecibida->getContentLength();
	while (tamanio > 0) {
		char c;
		sock->recibir(&c, sizeof(c));
		bufferContenido += c;
		tamanio--;
	}
	operacionRecibida->setContenido(bufferContenido);
	return operacionRecibida;
}

void ProtocoloHTTP::enviarRespuesta(HTTP_Response* r) {
	std::string resultado = r->getCadena();
	sock->enviar((char*) resultado.c_str(), resultado.size());
}
