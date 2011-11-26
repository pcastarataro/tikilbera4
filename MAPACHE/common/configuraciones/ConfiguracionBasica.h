/*
 * ConfiguracionBasica.h
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#ifndef CONFIGURACIONBASICA_H_
#define CONFIGURACIONBASICA_H_

#include <string>

/**
 * Clase que almacena los datos basicos de configuracion
 */
class ConfiguracionBasica {
private:
	int puerto;
	int puertoControl;
	int maximoConexiones;
	int maximoConexionesCliente;
	std::string raiz;
	bool protegido;
	int timeOutSegundos;
public:
	/**
	 * Constructor
	 */
	ConfiguracionBasica();

	/**
	 * Destructor
	 */
	~ConfiguracionBasica();

	/**
	 * Setea el puerto donde escuchara el servidor
	 * @param puerto es el numero de puerto
	 */
	void setPuerto(int puerto);

	/**
	 * Setea el puerto donde el servidor estará escuchando operaciones de control.
	 * @param es el numero de puerto
	 */
	void setPuertoControl(int puerto);

	/**
	 * Setea la cantidad maxima de conexiones que podrá manejar el servidor
	 * @param cant es la cantidad maxima de conexiones
	 */
	void setMaximoConexiones(int cant);

	/**
	 * Setea la cantidad maxima de conexiones de un mismo cliente que
	 * manejara el servidor.
	 */
	void setMaximoConexionesCliente(int cant);

	/**
	 * Setea la raiz donde estara alojado el sitio a hostear
	 */
	void setRaiz(const std::string& raiz);

	/**
	 * Pone al servidor en estado protegido.
	 */
	void proteger();

	/**
	 * Pone el servidor en estado desprotegido
	 */
	void desproteger();

	/**
	 * Setea el tiempo de timeout que tendra la conexion
	 * @param segundos es el tiempo en segundos que tendra de timeout.
	 */
	void setTimeOut(int segundos);

	/**
	 * Devuelve el numero de puerto
	 * @return numero de puerto del servidor
	 */
	int getPuerto() const;

	/**
	 * Devuelve el numero de puerto de control
	 * @return numero de puerto de control
	 */
	int getPuertoControl() const;

	/**
	 * Devuelve la cantidad maxima de conexiones
	 * @return cantidad maxima de conexiones
	 */
	int getMaximoConexiones() const;

	/**
	 * Devuelve la cantidad maxima de conexiones por cliente
	 * @return cantidad maxima de conexiones por cliente
	 */
	int getMaximoConexionesCliente() const;

	/**
	 * Devuelve la raiz del sitio.
	 * @return path del sitio
	 */
	std::string getRaiz() const;

	/**
	 * Devuelve el estado de proteccion del sitio
	 * @return true si esta protegido, false si no.
	 */
	bool getProteccion() const;

	/**
	 * Devuelve el tiempo de time out
	 * @return tiempo de timeout en segundos.
	 */
	int getTimeOut() const;
};

#endif /* CONFIGURACIONBASICA_H_ */
