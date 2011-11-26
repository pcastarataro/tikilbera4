/*
 * HTTP_Response.cpp
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#include "HTTP_Response.h"
#include <sstream>

HTTP_Response::HTTP_Response() {
	exigeAutentificacion = false;
	this->setCodigoRetorno(200);
	this->setContenido("");
	exigeAutentificacion = false;
	this->setProtocolo(1,0);

}

HTTP_Response::~HTTP_Response() {
}

void HTTP_Response::setCodigoRetorno(int codigo) {
	this->codigoRetorno = codigo;
}

void HTTP_Response::setTipoContenido(const std::string& tipo) {
	this->tipoContenido = tipo;
}

void HTTP_Response::setContenido(const std::string& cont) {
	this->contenido = cont;
	this->longitudContenido = cont.size();
}

void HTTP_Response::exigirAutentificacion() {
	this->exigeAutentificacion = true;
}

std::string HTTP_Response::getCadena() const {
	std::stringstream codigoSS;
	codigoSS << this->codigoRetorno;

	std::stringstream longitudSS;
	longitudSS << this->longitudContenido;

	std::string resultado;
	resultado.append(this->getProtocolo());
	resultado.append(" ");
	resultado.append(codigoSS.str());

	resultado.append(CRLF);
	resultado.append("Date: ");
	Time t;
	resultado.append(t.getFechaHora());
	resultado.append(CRLF);

	if(exigeAutentificacion) {
		resultado.append("WWW-Authenticate: Basic realm=\"Secure Area\"\n");
		resultado.append(CRLF);
	}

	resultado.append("Content-Type: ");
	resultado.append(this->tipoContenido);
	resultado.append(CRLF);
	resultado.append("Content-Length: ");
	resultado.append(longitudSS.str());
	resultado.append(CRLF);
	resultado.append(CRLF);
	resultado.append(this->contenido);
	return resultado;
}
