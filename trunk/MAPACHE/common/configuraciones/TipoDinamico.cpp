/*
 * TipoDinamico.cpp
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#include "TipoDinamico.h"

TipoDinamico::TipoDinamico() {
}

TipoDinamico::~TipoDinamico() {
}

void TipoDinamico::setComando(const std::string& comando) {
	this->comando = comando;
}

std::string TipoDinamico::getComando() const {
	return this->comando;
}
