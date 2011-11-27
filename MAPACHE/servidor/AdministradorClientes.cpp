/*
 * AdministradorClientes.cpp
 *
 *  Created on: 31/10/2011
 *      Author: pablo
 */

#include "AdministradorClientes.h"
#include "Codigos.HTTP.h"
#include "CargardorDeArchivos.h"
#include "ErrorArchivoException.h"
#include "Log.h"
#include "ManejadorLogs.h"
#include "Lock.h"

#define MAPA std::map<std::string , std::list<ManejadorClienteHTTP*> >
#define ITERADOR MAPA::iterator
#define PAR_RETORNO std::pair< ITERADOR , bool>
#define PAR std::pair< std::string , std::list<ManejadorClienteHTTP*> >

AdministradorClientes::AdministradorClientes(const Configuracion& c) :
	config(c) {
	total = 0;
}

AdministradorClientes::~AdministradorClientes() {
	limpiarActivos();
}

void AdministradorClientes::avisarSobrecargaServidor(
		ManejadorClienteHTTP *manejador) {
	Lock l(mutex);
	HTTP_Response *respuesta = new HTTP_Response();
	respuesta->setCodigoRetorno(CODIGO_SERVICIO_NO_DISPONIBLE);
	respuesta->setProtocolo(1, 0);
	respuesta->setTipoContenido("text/html");
	std::string archError = config.getError(CODIGO_SERVICIO_NO_DISPONIBLE);
	if (archError != "") {
		try {
			std::string cadena =
					CargardorDeArchivos::levantarArchivo(archError);
			respuesta->setContenido(cadena);
		} catch(const ErrorArchivoException & e) {
		}
	}
	manejador->enviarMsg(respuesta);
	delete respuesta;
}

void AdministradorClientes::agregarCliente(ManejadorClienteHTTP* manejador) {
	Lock l(mutex);
	if (total < config.getConfiguracionBasica().getMaximoConexiones()) {
		PAR par;
		par.first = manejador->getIpCliente();
		this->mapaIpConexiones.insert(par);
		//  Si no existe agrega el registro en el mapa.
		//  Lo busca y trata de agregar el manejador en la lista.
		ITERADOR it = this->mapaIpConexiones.find(manejador->getIpCliente());
		if (it != this->mapaIpConexiones.end()) {
			int tamLista = it->second.size();
			if (tamLista
					< config.getConfiguracionBasica().getMaximoConexionesCliente()) {
				it->second.push_back(manejador);
				ManejadorLogs::getInstance(config.getConfiguracionLogs())
				->getLogAcceso()->logInfo("Se empieza a atender al cliente "
								+ manejador->getIpCliente());
				manejador->start();
				total++;
			} else {
				ManejadorLogs::getInstance(config.getConfiguracionLogs())
				-> getLogError()->logError("Se llego al maximo de conexiones para "
								+ manejador->getIpCliente());
				avisarSobrecargaServidor(manejador);
				delete manejador;
			}
		}
	} else {
		ManejadorLogs::getInstance(config.getConfiguracionLogs())
		-> getLogError()->logError("Se llego al maximo de conexiones");
		avisarSobrecargaServidor(manejador);
		delete manejador;
	}
}

bool finalizado(ManejadorClienteHTTP* manejador) {
	return manejador == 0;
}

void AdministradorClientes::limpiarFinalizados() {
	Lock l(mutex);
	ITERADOR itMapa;
	for (itMapa = mapaIpConexiones.begin();
			itMapa != mapaIpConexiones.end(); itMapa++) {
		std::list<ManejadorClienteHTTP*>::iterator itM;
		for (itM = itMapa->second.begin(); itM != itMapa->second.end(); itM++) {
			if (!(*itM)->vivo()) {
				(*itM)->apagar();
				(*itM)->join();
				delete (*itM);
				(*itM) = 0;
				total--;
			}
		}
		itMapa->second.remove_if(finalizado);
	}
}

void AdministradorClientes::limpiarActivos() {
	Lock l(mutex);
	ITERADOR itMapa;
	for (itMapa = this->mapaIpConexiones.begin(); itMapa
			!= this->mapaIpConexiones.end(); itMapa++) {
		std::list<ManejadorClienteHTTP*>::iterator it;
		for (it = itMapa->second.begin(); it != itMapa->second.end(); it++) {
			(*it)->morir();
			(*it)->apagar();
			(*it)->join();
			delete (*it);
			(*it) = 0;
		}
		itMapa->second.remove_if(finalizado);
	}
}

void AdministradorClientes::limpiarActivosConTimeOutMayor() {
	Lock l(mutex);
	ITERADOR itMapa;
	for (itMapa = this->mapaIpConexiones.begin(); itMapa
			!= this->mapaIpConexiones.end(); itMapa++) {
		std::list<ManejadorClienteHTTP*>::iterator it;
		for (it = itMapa->second.begin(); it != itMapa->second.end(); it++) {
			time_t t;
			time(&t);
			struct tm* petm;
			petm = localtime(&t);
			int sec = petm->tm_hour * 3600 + petm->tm_min * 60 + petm->tm_sec;
			int dif = sec - (*it)->getOffsetSegundos();
			if (dif >= config.getConfiguracionBasica().getTimeOut()) {
				ManejadorLogs::getInstance(config.getConfiguracionLogs())
				->getLogError()->logError("Se saca al cliente "
						+ (*it)->getIpCliente() + " por timeout.");
				(*it)->morir();
				(*it)->apagar();
				(*it)->join();
				delete *it;
				*it = 0;
				total--;
			}
		}
		itMapa->second.remove_if(finalizado);
	}
}
