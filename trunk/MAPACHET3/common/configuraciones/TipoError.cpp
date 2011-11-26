/*
 * TipoError.cpp
 *
 *  Created on: 18/10/2011
 *      Author: pablo
 */

#include "TipoError.h"

TipoError::TipoError() {
}

TipoError::~TipoError() {
}

int TipoError::getNroError() const {
	return this->numero;
}

const std::string& TipoError::getRuta() const {
	return this->ruta;
}

void TipoError::setRuta(const std::string& ruta) {
	this->ruta = ruta;
}

void TipoError::setNroError(int numero) {
	this->numero = numero;
}
