/*
 * ConfiguracionBasica.cpp
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#include "ConfiguracionBasica.h"

#define DEFAULT_PUERTO 3000
#define DEFAULT_PUERTO_CONTROL 33000
#define DEFAULT_MAXIMO_CONEXIONES 100
#define DEFAULT_MAXIMO_CONEXIONES_CLIENTE 2
#define DEFAULT_TIME_OUT 10

ConfiguracionBasica::ConfiguracionBasica() {
	this->setPuerto(DEFAULT_PUERTO);
	this->setPuertoControl(DEFAULT_PUERTO_CONTROL);
	this->setMaximoConexiones(DEFAULT_MAXIMO_CONEXIONES);
	this->setMaximoConexionesCliente(DEFAULT_MAXIMO_CONEXIONES_CLIENTE);
	this->desproteger();
	this->setTimeOut(DEFAULT_TIME_OUT);
}

ConfiguracionBasica::~ConfiguracionBasica() {
}

void ConfiguracionBasica::setPuerto(int puerto) {
	this->puerto = puerto;
}

void ConfiguracionBasica::setPuertoControl(int puerto) {
	this->puertoControl = puerto;
}

void ConfiguracionBasica::setMaximoConexiones(int cant) {
	this->maximoConexiones = cant;
}

void ConfiguracionBasica::setMaximoConexionesCliente(int cant) {
	this->maximoConexionesCliente = cant;
}

void ConfiguracionBasica::setRaiz(const std::string& raiz) {
	this->raiz = raiz;
}

void ConfiguracionBasica::proteger() {
	this->protegido = true;
}

void ConfiguracionBasica::desproteger() {
	this->protegido = false;
}

void ConfiguracionBasica::setTimeOut(int segundos) {
	this->timeOutSegundos = segundos;
}

int ConfiguracionBasica::getPuerto() const {
	return this->puerto;
}

int ConfiguracionBasica::getPuertoControl() const {
	return this->puertoControl;
}

int ConfiguracionBasica::getMaximoConexiones() const {
	return this->maximoConexiones;
}

int ConfiguracionBasica::getMaximoConexionesCliente() const {
	return this->maximoConexionesCliente;
}

std::string ConfiguracionBasica::getRaiz() const {
	return this->raiz;
}

bool ConfiguracionBasica::getProteccion() const {
	return this->protegido;
}

int ConfiguracionBasica::getTimeOut() const {
	return this->timeOutSegundos;
}
