/*
 * ProcesadorRequest.cpp
 *
 *  Created on: 04/11/2011
 *      Author: pablo
 */

#include "ProcesadorRequest.h"
#include "ProcesadorCGI.h"
#include "ProcesadorTipoEstatico.h"
#include "Codigos.HTTP.h"
#include "Tipos_HTTP.h"
#include "Base64EncoderDecoder.h"
#include "CargardorDeArchivos.h"
#include "ErrorArchivoException.h"
#include "Log.h"
#include "ManejadorLogs.h"

int ProcesadorRequest::contador = 0;
Mutex ProcesadorRequest::mutex;

ProcesadorRequest::ProcesadorRequest(const Configuracion& c) :
	config(c) {
}

ProcesadorRequest::~ProcesadorRequest() {
}

bool ProcesadorRequest::autentificar(HTTP_Request * pedido) {
	Base64EncoderDecoder decoder;
	bool autentificadoConExito = false;
	if (config.getConfiguracionBasica().getProteccion()) {
		// el servidor pide validación
		std::string cadenaAutentificacion = pedido->getAuthorization();
		cadenaAutentificacion = cadenaAutentificacion.substr(
				cadenaAutentificacion.find(' ', 0) + 1,
				cadenaAutentificacion.size() - cadenaAutentificacion.find(' ',
						0));
		std::string cadenaDecodificada = decoder.decodificar(
				cadenaAutentificacion);
		size_t posSeparador = cadenaDecodificada.find(':', 0);
		if (posSeparador != std::string::npos) {
			std::string nombreUsuario = cadenaDecodificada.substr(0,
					posSeparador);
			cadenaDecodificada.erase(0, posSeparador + 1); // se corta la cadena quedando solo el pass
			std::string passUsuario = config.getPassUsuario(nombreUsuario);
			if ((cadenaDecodificada == passUsuario) && (passUsuario != "")) {
				autentificadoConExito = true;
				ManejadorLogs::getInstance(config.getConfiguracionLogs())-> getLogAcceso()->logInfo(
						"Autentificado con exito el usuario: " + nombreUsuario);
			}

		}
	} else {
		// no hacia falta autentificacion. No estaba protegido.
		autentificadoConExito = true;
	}
	return autentificadoConExito;
}

HTTP_Response* ProcesadorRequest::exigirAutentificacion() {
	HTTP_Response *respuesta = new HTTP_Response();
	respuesta->setCodigoRetorno(CODIGO_NO_AUTORIZADO);
	respuesta->exigirAutentificacion();
	respuesta->setProtocolo(1, 0);
	respuesta->setTipoContenido(DEFAULT_TYPE);
	std::string nombreArchivo;
	try {
		nombreArchivo = config.getError(CODIGO_NO_AUTORIZADO);
		if (nombreArchivo != "") {
			std::string cadenaArchivo = CargardorDeArchivos::levantarArchivo(
					nombreArchivo);
			respuesta->setContenido(cadenaArchivo);
		}
	} catch (const ErrorArchivoException& e) {
		ManejadorLogs::getInstance(config.getConfiguracionLogs())-> getLogError()->logError(
				"El archivo " + nombreArchivo + " no existe en el servidor");
	}
	return respuesta;
}

HTTP_Response* ProcesadorRequest::procesar(HTTP_Request* pedido) {
	HTTP_Response* respuesta = NULL;
	IProcesador* procesador = NULL;
	char* dirAct = get_current_dir_name();
	bool autentificado = autentificar(pedido);
	if (!autentificado) {
		respuesta = exigirAutentificacion();
	} else {
		std::string pedidoStr = pedido->getUri();
		std::string extension = IProcesador::obtenerExtension(pedidoStr);
		size_t posParams = extension.find('?', 0);
		if (posParams != std::string::npos) {
			extension = extension.substr(0, posParams);
		}
		std::string comando;
		if (extension == "cgi") {
			string uri = pedido->getUri();
			comando = uri.substr(1, uri.length());
		} else {
			comando = config.getTipoDinamico(extension);
		}
		if (comando != "") {
			std::string dir = crearDirectorioTemporalParaElCGI();
			procesador = new ProcesadorCGI(config, dir, comando);
		} else {
			procesador = new ProcesadorTipoEstatico(config);
		}
		respuesta = procesador->procesar(pedido);
		chdir(dirAct);
		free(dirAct);
		delete procesador;
	}
	return respuesta;
}

/*	Crea un directorio para que un cgi guarde sus archivos de salida y devuelve su ruta completa.
 * 	Se bloquea hasta que termine de consultar y modificar a "contador".*/
std::string ProcesadorRequest::crearDirectorioTemporalParaElCGI() {
	std::string strContador;
	std::stringstream ss;
	char* dirAct;// = get_current_dir_name();

	mutex.lock();
	ss << contador;
	contador++;
	mutex.unlock();

	ss >> strContador;
	strContador.append("/");
	std::string comandoMkDir("mkdir ");
	comandoMkDir.append(strContador);

	chdir("./arch-temp-cgi");
	// TODO: "extraer de archivo de configuracion el path de los arch creados por los cgi"
	system(comandoMkDir.c_str());
	dirAct = get_current_dir_name();
	std::string dirTemporalArchivosCGI(dirAct);
	free(dirAct);
	dirTemporalArchivosCGI.append("/");
	dirTemporalArchivosCGI.append(strContador);

	chdir("../");
	// TODO: "extraer de archivo de configuracion el path raiz"

	return dirTemporalArchivosCGI;
}
