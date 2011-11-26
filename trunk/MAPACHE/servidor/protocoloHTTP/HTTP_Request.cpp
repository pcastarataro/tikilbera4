/*
 * HTTP_Request.cpp
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#include "HTTP_Request.h"
#include <sstream>
#include <string>
#include <iostream>

HTTP_Request::HTTP_Request() {
}

HTTP_Request::~HTTP_Request() {
}

HTTP_Request::HTTP_Request(const std::string& entrada) {
	generarMapa(entrada);
}

void HTTP_Request::generarMapa(const std::string& msg) {
	size_t posicionInicial = 0;
	size_t posicionFinal = 0;
	std::string clave;
	std::string valor;
	std::pair<std::string, std::string> dato;
	std::map<std::string, std::string>::iterator it;
	std::string linea;
	std::string mensaje = msg;
	posicionFinal = mensaje.find(CRLF);
	linea = mensaje.substr(posicionInicial, posicionFinal);
	mensaje.erase(posicionInicial, posicionFinal + 2);
	posicionFinal = linea.find(" ");
	clave = "Method";
	valor = linea.substr(0, posicionFinal);
	linea.erase(0, posicionFinal + 1);
	dato.first = clave;
	dato.second = valor;
	idMapas.insert(dato);

	posicionFinal = linea.find(" ");
	clave = "Uri";
	valor = linea.substr(0, posicionFinal);
	linea.erase(0, posicionFinal + 1);
	dato.first = clave;
	dato.second = valor;
	idMapas.insert(dato);

	clave = "Protocol";
	valor = linea;
	dato.first = clave;
	dato.second = valor;
	idMapas.insert(dato);
	posicionFinal = mensaje.find(CRLF);
	bool termine = false;
	while (!termine) {
		posicionFinal = mensaje.find(CRLF);
		if(posicionFinal != 0) {
			linea = mensaje.substr(posicionInicial, posicionFinal);
			mensaje.erase(posicionInicial, posicionFinal + 2);
			posicionFinal = linea.find(" ");
			clave = linea.substr(0, posicionFinal - 1);
			valor = linea.substr(posicionFinal + 1, linea.length());
			dato.first = clave;
			dato.second = valor;
			idMapas.insert(dato);
		} else {
			termine = true;
			posicionFinal = std::string::npos;
		}
	}
}

std::string HTTP_Request::getValor(const std::string& clave) {
	std::pair<std::string, std::string> dato;
	std::map<std::string, std::string>::iterator it;
	std::string resultado = "";
	it = idMapas.find(clave);

	if ((it != idMapas.end())) {
		resultado = it->second;
	}
	return resultado;
}

std::string HTTP_Request::getMethod() {
	return getValor("Method");
}

std::string HTTP_Request::getUri() {
	return getValor("Uri");
}

std::string HTTP_Request::getHost() {
	return getValor("Host");
}

std::string HTTP_Request::getConnection() {
	return getValor("Connection");
}

std::string HTTP_Request::getUserAgent() {
	return getValor("User-Agent");
}

std::string HTTP_Request::getTypeText() {
	return getValor("Accept");
}

std::string HTTP_Request::getAuthentication() {
	return getValor("WWW-Authenticate");
}

std::string HTTP_Request::getAuthorization() {
	return getValor("Authorization");
}

std::string HTTP_Request::getContenido() {
	return this->contenido;
}

int HTTP_Request::getContentLength() {
	std::string cad = getValor("Content-Length");
	if(cad == "")
		return 0;
	std::stringstream ss;
	int tam;
	ss << cad;
	ss >> tam;
	return tam;
}

void HTTP_Request::setContenido(const std::string& cont) {
	this->contenido = cont;
}
