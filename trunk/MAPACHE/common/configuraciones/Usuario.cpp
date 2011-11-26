/*
 * Usuario.cpp
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#include "Usuario.h"

Usuario::Usuario() {
}

Usuario::~Usuario() {
}

void Usuario::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

void Usuario::setClave(const std::string& clave) {
	this->pass = clave;
}

std::string Usuario::getNombre() const {
	return this->nombre;
}

std::string Usuario::getClave() const {
	return this->pass;
}
