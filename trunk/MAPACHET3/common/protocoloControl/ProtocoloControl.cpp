/*
 * ProtocoloControl.cpp
 *
 *  Created on: 23/10/2011
 *      Author: pablo
 */

#include "ProtocoloControl.h"
#include "SocketException.h"

ProtocoloControl::ProtocoloControl(TCPSocket& sock): socket(sock) {
}

ProtocoloControl::~ProtocoloControl() {
}

void ProtocoloControl::enviarOperacionDetenerServidor() {
	char codigoDetener = CODIGO_DETENER_SERVIDOR;
    enviarCaracter(codigoDetener);
}

bool ProtocoloControl::recibirRespuestaDetenido() {
	char codigoRecibido = recibirCaracter();
    if(codigoRecibido == CODIGO_DETENIDO_OK)
		return true;
	else
		return false;
}

void ProtocoloControl::enviarRespuestaDetenido(bool conExito) {
	char codigoDetenidoConExito = 0;
	if(conExito)
		codigoDetenidoConExito = CODIGO_DETENIDO_OK;
	else
		codigoDetenidoConExito = CODIGO_DETENIDO_ERROR;
	enviarCaracter(codigoDetenidoConExito);
}

bool ProtocoloControl::recibirOperacionDetener() {
	char respuestaRecibida = 0;
	respuestaRecibida = recibirCaracter();
	if(respuestaRecibida == CODIGO_DETENER_SERVIDOR)
		return false;
	else
		return true;
}

char ProtocoloControl::recibirCaracter() {
    char codigoRecibido = 0;
    try {
    	socket.recibir(&codigoRecibido , sizeof(codigoRecibido));
    }catch(const SocketException&) {
    	throw ProtocoloControlException();
    }
    return codigoRecibido;
}

void ProtocoloControl::enviarCaracter(char codigoDetener) {
	char cod = codigoDetener;
	try {
		socket.enviar(&cod , sizeof(cod));
	} catch(const SocketException&) {
		throw ProtocoloControlException();
	}
}
