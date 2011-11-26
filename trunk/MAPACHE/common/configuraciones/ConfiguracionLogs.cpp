/*
 * ConfiguracionLogs.cpp
 *
 *  Created on: 18/10/2011
 *      Author: pablo
 */

#include "ConfiguracionLogs.h"

ConfiguracionLogs::ConfiguracionLogs() {
	this->setRutaLogAccesos("../Accesos.log");
	this->setRutaLogErrores("../logErrores.log");
}

ConfiguracionLogs::~ConfiguracionLogs() {
}

void ConfiguracionLogs::setRutaLogAccesos(const std::string& ruta) {
	this->rutaLogAccesos = ruta;
}

void ConfiguracionLogs::setRutaLogErrores(const std::string& ruta) {
	this->rutaLogErrores = ruta;
}

std::string ConfiguracionLogs::getRutaLogAccesos() const {
	return this->rutaLogAccesos;
}
std::string ConfiguracionLogs::getRutaLogErrores() const {
	return this->rutaLogErrores;
}
