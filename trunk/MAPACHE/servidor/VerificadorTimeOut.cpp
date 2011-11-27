/*
 * VerificadorTimeOut.cpp
 *
 *  Created on: 31/10/2011
 *      Author: pablo
 */

#include "VerificadorTimeOut.h"

VerificadorTimeOut::VerificadorTimeOut(int tiempoRefrezco,
		int cantidadConfiguracion, AdministradorClientes* admin) :
	administrador(admin) {
	this->tiempoRefrezco = tiempoRefrezco;
	this->cantidadEnConfiguracion = cantidadConfiguracion;
}

VerificadorTimeOut::~VerificadorTimeOut() {
}

void VerificadorTimeOut::run() {
	int cantActual = 0;
	while (this->vivo()) {
		if (cantActual >= cantidadEnConfiguracion) {
			administrador->limpiarActivosConTimeOutMayor();
			cantActual = 0;
		} else
			cantActual += 10;
		sleep(tiempoRefrezco);
	}
}
