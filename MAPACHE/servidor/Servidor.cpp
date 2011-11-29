/*
 * Servidor.cpp
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#include "Servidor.h"
#include "TCPSocket.h"
#include "SocketException.h"
#include "ProtocoloControl.h"
#include "ProtocoloControlException.h"
#include "ServidorHttp.h"

#define CANT_MAX_CLI 10

Servidor::Servidor(const Configuracion& c, bool reiniciando) :
	config(c) {
	this->reiniciando = reiniciando;
}

Servidor::~Servidor() {
}

int Servidor::start() {
	TCPSocket sockCrtl;
	if (reiniciando)
		sockCrtl.setearComoReusable();

	int retorno = 0;
	try {
		sockCrtl.bindear(config.getConfiguracionBasica().getPuertoControl());
		sockCrtl.escuchar(CANT_MAX_CLI);
		ServidorHttp servidorHTTP(config, reiniciando);
		servidorHTTP.start();

		std::cout << "SERVIDOR HTML ACTIVADO en puerto:  "
				<< config.getConfiguracionBasica().getPuerto() << std::endl;

		bool activo = true;
		while (activo) {
			TCPSocket* sockClienteCrtl = sockCrtl.aceptar();
			ProtocoloControl protocoloCtrl(*sockClienteCrtl);
			try {
				activo = protocoloCtrl.recibirOperacionDetener();
				if (!activo) {
					servidorHTTP.morir();
					servidorHTTP.apagar();
					servidorHTTP.join();
					std::cout << "SERVIDOR HTML DESACTIVADO" << std::endl;
				} else {
					std::cout << "SE INGRESO UNA OPERACION INVALIDA"
							<< std::endl;
				}
				protocoloCtrl.enviarRespuestaDetenido(!activo);
			} catch(const ProtocoloControlException&) {}
			sockClienteCrtl->apagar();
			sockClienteCrtl->cerrar();
			delete sockClienteCrtl;
		}
	} catch(const SocketException&) {
		std::cout << "NO SE PUDO INICIAR EL SERVIDOR" << std::endl;
		// todo: log?
		retorno = 1;
	}
	sockCrtl.apagar();
	sockCrtl.cerrar();
	return retorno;
}
