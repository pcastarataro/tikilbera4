/*
 * ServidorHttp.cpp
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#include "ServidorHttp.h"
#include "ManejadorClienteHTTP.h"
#include "VerificadorTimeOut.h"
#include "SocketException.h"
#include "BindException.h"
#include "ListenException.h"
#include "AcceptException.h"

#define MAX_ESPERA 200
#define TIEMPO_REFREZCO 5

ServidorHttp::ServidorHttp(const Configuracion& c , bool reiniciando): config(c) {
	administradorClientes = new AdministradorClientes(config);
	this->reiniciando = reiniciando;
	if(reiniciando)
		socketHTTP.setearComoReusable();
}

ServidorHttp::~ServidorHttp() {
	socketHTTP.apagar();
	socketHTTP.cerrar();
	delete administradorClientes;
}

void ServidorHttp::run() {
	VerificadorTimeOut verificador(TIEMPO_REFREZCO , config.getConfiguracionBasica().getTimeOut() ,administradorClientes);
	verificador.start();
	try {
		socketHTTP.bindear(config.getConfiguracionBasica().getPuerto());
		socketHTTP.escuchar(MAX_ESPERA);
		while(this->vivo()) {
			administradorClientes->limpiarFinalizados();
			TCPSocket* sockCliente = socketHTTP.aceptar();
			ManejadorClienteHTTP *manejador = new ManejadorClienteHTTP(sockCliente , this->config);
			administradorClientes->agregarCliente(manejador);
		}
	} catch (const BindException&) {
		std::cout << "NO SE PUDO INICIAR EL SERVIDOR HTTP" << std::endl;
	} catch (const ListenException&) {
		std::cout << "NO SE PUDO INICIAR EL SERVIDOR HTTP" << std::endl;
	} catch (const AcceptException&) {

	}
	catch(const SocketException&) {
		std::cout << "SE DESCONECTO" << std::endl;
	}
	verificador.morir();
	verificador.join();
}

void ServidorHttp::apagar() {
	socketHTTP.apagar();
	socketHTTP.cerrar();
}
