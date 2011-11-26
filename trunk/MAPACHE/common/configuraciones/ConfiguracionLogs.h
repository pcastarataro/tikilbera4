/*
 * ConfiguracionLogs.h
 *
 *  Created on: 18/10/2011
 *      Author: pablo
 */

#ifndef CONFIGURACIONLOGS_H_
#define CONFIGURACIONLOGS_H_

#include <string>

/**
 * Clase que guarda la configuracion para los logs
 */
class ConfiguracionLogs {
private:
	std::string rutaLogAccesos;
	std::string rutaLogErrores;
public:
	/**
	 * Constructor
	 */
	ConfiguracionLogs();

	/**
	 * Destructor
	 */
	virtual ~ConfiguracionLogs();

	/**
	 * Setea el path del log de accesos
	 * @param ruta es el path donde se guarda el log de acceso.
	 */
	void setRutaLogAccesos(const std::string& ruta);

	/**
	 * Setea el path del log de errores
	 * @param ruta es el path donde se guarda el log de errores
	 */
	void setRutaLogErrores(const std::string& ruta);

	/**
	 * Devuelve el path del log de accesos
	 * @return ruta del log de accesos
	 */
	std::string getRutaLogAccesos() const;

	/**
	 * Devuelve el path del log de errores
	 * @return ruta del log de errores
	 */
	std::string getRutaLogErrores() const;
};

#endif /* CONFIGURACIONLOGS_H_ */
