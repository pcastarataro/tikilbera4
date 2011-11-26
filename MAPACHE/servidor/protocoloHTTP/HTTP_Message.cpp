/*
 * HTTP_Message.cpp
 *
 *  Created on: 27/10/2011
 *      Author: pablo
 */

#include "HTTP_Message.h"
#include <sstream>

HTTP_Message::HTTP_Message() {
}

HTTP_Message::~HTTP_Message() {
}

void HTTP_Message::setProtocolo(int mayor , int menor) {
	std::stringstream mayorSS;
	std::stringstream menorSS;
	mayorSS << mayor;
	menorSS << menor;
	this->versionProtocolo = "HTTP/" + mayorSS.str() + "." + menorSS.str();
}

std::string HTTP_Message::getProtocolo() const {
	return this->versionProtocolo;
}
