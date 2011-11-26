/*
 * ManejadorClienteHTTP.cpp
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#include "ManejadorClienteHTTP.h"
#include "protocoloHTTP/ProtocoloHTTP.h"
#include "ProcesadorRequest.h"
#include "SocketException.h"

ManejadorClienteHTTP::ManejadorClienteHTTP(TCPSocket* sock ,
		const Configuracion& c): sockCliente(sock), config(c) {
}

ManejadorClienteHTTP::~ManejadorClienteHTTP() {
	this->apagar();
	delete sockCliente;
}

void ManejadorClienteHTTP::enviarMsg(HTTP_Response* respuesta) {
	try {
		ProtocoloHTTP http(this->sockCliente);
		http.enviarRespuesta(respuesta);
	}catch (const SocketException& e) {
	}
}

std::string ManejadorClienteHTTP::getIpCliente() const {
	return this->sockCliente->getIp();
}

int ManejadorClienteHTTP::getOffsetSegundos() const {
	return this->offsetInicioSegundos;
}

void ManejadorClienteHTTP::run() {
	time_t t;
	time(&t);
	struct tm* petm = localtime(&t);
	this->offsetInicioSegundos = petm->tm_hour*3600 + petm->tm_min * 60 + petm->tm_sec; // offset Segundos
	ProtocoloHTTP http(this->sockCliente);
	ProcesadorRequest procesador(this->config);
	try {
		HTTP_Request *operacionRecibida = http.recibirOperacion();
		HTTP_Response* respuesta = NULL;
		respuesta = procesador.procesar(operacionRecibida);
		delete operacionRecibida;
		http.enviarRespuesta(respuesta);
		delete respuesta;
	} catch (const SocketException& e) {
		// FIXME LOG?
	}
	this->apagar();
	this->morir();
}

void ManejadorClienteHTTP::apagar() {
	this->sockCliente->apagar();
	this->sockCliente->cerrar();
}
