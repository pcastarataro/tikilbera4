/*
 * TipoEstatico.cpp
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#include "TipoEstatico.h"

TipoEstatico::TipoEstatico() {
}

TipoEstatico::~TipoEstatico() {
}

void TipoEstatico::setContenido(const std::string& contenido) {
	this->contenido = contenido;
}

std::string TipoEstatico::getContenido() const {
	return this->contenido;
}
