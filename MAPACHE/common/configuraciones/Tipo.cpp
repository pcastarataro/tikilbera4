/*
 * Tipo.cpp
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#include "Tipo.h"

Tipo::Tipo() {
}

Tipo::~Tipo() {
}

void Tipo::setExtension(const std::string& extension) {
	this->extension = extension;
}

std::string Tipo::getExtension() const {
	return this->extension;
}
