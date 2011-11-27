/*
 * ProcesadorTipoEstatico.cpp
 *
 *  Created on: 09/11/2011
 *      Author: pablo
 */

#include "ProcesadorTipoEstatico.h"
#include "CargardorDeArchivos.h"
#include "Log.h"
#include "ManejadorLogs.h"
#include "Codigos.HTTP.h"
#include "Tipos_HTTP.h"

ProcesadorTipoEstatico::ProcesadorTipoEstatico(const Configuracion& c) :
	config(c) {
}

ProcesadorTipoEstatico::~ProcesadorTipoEstatico() {
}

HTTP_Response* ProcesadorTipoEstatico::procesar(HTTP_Request* pedido) {
	HTTP_Response *respuesta = new HTTP_Response();
	respuesta->setProtocolo(1, 0);

	std::string pedidoStr = pedido->getUri();
	if (pedidoStr.at(pedidoStr.size() - 1) == '/')
		pedidoStr += "index.html";
	std::string extension = IProcesador::obtenerExtension(pedidoStr);
	std::string tipo = config.getTipoEstatico(extension);
	if (tipo == "") {
		try {
			ManejadorLogs::getInstance(config.getConfiguracionLogs())
			-> getLogError()->logError("El archivo con extension " + extension
							+ " no puede ser procesado por el servidor");
			tipo = DEFAULT_TYPE;
			respuesta->setTipoContenido(tipo);
			respuesta->setCodigoRetorno(CODIGO_PAGINA_NO_ENCONTRADA);
			std::string cadenaArchivo = CargardorDeArchivos::levantarArchivo(
					config.getError(CODIGO_PAGINA_NO_ENCONTRADA));
			respuesta->setContenido(cadenaArchivo);
		} catch(const ErrorArchivoException&) {
			ManejadorLogs::getInstance(config.getConfiguracionLogs())
			-> getLogError()->logError("El archivo "
							+ config.getError(CODIGO_PAGINA_NO_ENCONTRADA)
							+ " no existe en el servidor");
		}
		return respuesta;
	}

	respuesta->setTipoContenido(tipo);

	std::string pathArchivo = config.getConfiguracionBasica().getRaiz()
			+ pedidoStr;
	std::string cadenaArchivo;
	try {
		cadenaArchivo = CargardorDeArchivos::levantarArchivo(pathArchivo);
		respuesta->setContenido(cadenaArchivo);
		respuesta->setCodigoRetorno(CODIGO_OK);
		ManejadorLogs::getInstance(config.getConfiguracionLogs())
		-> getLogAcceso()->logInfo("Se accede al recurso "
				+ pathArchivo + " con exito");
	} catch(const ErrorArchivoException& e) {
		try {
			ManejadorLogs::getInstance(config.getConfiguracionLogs())
			-> getLogError()->logError("El archivo "
					+ pathArchivo + " no existe en el servidor");
			cadenaArchivo = CargardorDeArchivos::levantarArchivo(
					config.getError(404));
			respuesta->setContenido(cadenaArchivo);
			respuesta->setCodigoRetorno(CODIGO_PAGINA_NO_ENCONTRADA);
		} catch(const std::exception& e) {
			respuesta->setCodigoRetorno(CODIGO_PAGINA_NO_ENCONTRADA);
			ManejadorLogs::getInstance(config.getConfiguracionLogs())
			-> getLogError()->logError("El archivo " + config.getError(404)
							+ " no existe en el servidor");
		}
	}
	return respuesta;
}
