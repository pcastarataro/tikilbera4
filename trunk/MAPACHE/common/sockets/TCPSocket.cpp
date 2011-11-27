/*
 * Socket.cpp
 *
 *  Created on: 12/05/2011
 *      Author: pablo
 */

#include "TCPSocket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <string.h>

#include "InitException.h"
#include "BindException.h"
#include "ConnectException.h"
#include "ListenException.h"
#include "AcceptException.h"
#include "SocketException.h"

#include <iostream>

TCPSocket::TCPSocket() {
	apagado = false;
	cerrado = false;
	this->descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (descriptor == -1) {
		throw InitException();
	}
}

TCPSocket::TCPSocket(int descriptor) {
	if (descriptor == -1) {
		throw InitException();
	}
	this->descriptor = descriptor;
	apagado = false;
	cerrado = false;
}

TCPSocket::~TCPSocket() {
	apagar();
	cerrar();
}

void TCPSocket::setearComoReusable() {
	const int optVal = 1;
	const socklen_t optLen = sizeof(optVal);
	setsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR, (void*) &optVal, optLen);
}

void TCPSocket::bindear(int puerto) {
	sockaddr_in direccion_server;
	memset((char*) &(direccion_server), 0, sizeof(direccion_server));
	direccion_server.sin_family = AF_INET;
	direccion_server.sin_port = htons(puerto);
	direccion_server.sin_addr.s_addr = INADDR_ANY;
	if (bind(this->descriptor, (struct sockaddr*) &direccion_server,
			(socklen_t) sizeof(sockaddr)) < 0) {
		throw BindException();
	}
}

void TCPSocket::escuchar(int max_cola_conexiones) {
	if (listen(this->descriptor, max_cola_conexiones) < 0)
		throw ListenException();
}

void TCPSocket::conectar(const std::string& ip, int puerto) {
	sockaddr_in direccion_server;
	memset((char*) &(direccion_server), 0, sizeof(direccion_server));
	direccion_server.sin_family = AF_INET;
	direccion_server.sin_port = htons(puerto);
	direccion_server.sin_addr.s_addr = inet_addr(ip.c_str());
	if (connect(this->descriptor, (struct sockaddr *) &direccion_server,
			sizeof(direccion_server)) == -1) {
		throw ConnectException();
	}
}

void TCPSocket::apagar() {
	if (!apagado) {
		shutdown(this->descriptor, 2);
		apagado = true;
	}
}

void TCPSocket::cerrar() {
	if (!cerrado) {
		close(this->descriptor);
		cerrado = true;
	}
}

TCPSocket* TCPSocket::aceptar() {
	socklen_t tamanio = sizeof(struct sockaddr_in);
	int nuevo_cliente_descriptor;
	sockaddr_in dir_cliente;
	if ((nuevo_cliente_descriptor = accept(this->descriptor,
			(struct sockaddr *) &dir_cliente, &tamanio)) == -1) {
		throw AcceptException();
	}
	TCPSocket* sock_cliente_nuevo = new TCPSocket(nuevo_cliente_descriptor);
	sock_cliente_nuevo->ip = inet_ntoa(dir_cliente.sin_addr);
	return sock_cliente_nuevo;
}

void TCPSocket::recibir(char* data, int longitud) {
	int total_recibido = 0;
	while (total_recibido < longitud) {
		int cantidad = recv(this->descriptor, data + total_recibido,
				longitud - total_recibido, 0);
		if (cantidad <= 0)
			throw SocketException();
		total_recibido += cantidad;
	}
}

void TCPSocket::enviar(char* data, int longitud) {
	int total_enviado = 0;
	while (total_enviado < longitud) {
		int cantidad = send(this->descriptor, data + total_enviado,
				longitud - total_enviado, 0);
		if (cantidad <= 0)
			throw SocketException();
		total_enviado += cantidad;
	}
}

std::string TCPSocket::getIp() const {
	return this->ip;
}
