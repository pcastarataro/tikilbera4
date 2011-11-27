/*
 * VerificadorTimeOut.h
 *
 *  Created on: 31/10/2011
 *      Author: pablo
 */

#ifndef VERIFICADORTIMEOUT_H_
#define VERIFICADORTIMEOUT_H_

#include "Thread.h"
#include "AdministradorClientes.h"

/**
 * Clase encargada de verificar el tiempo de espera de los clientes
 * dentro del servidor.
 */
class VerificadorTimeOut: public Thread {
private:
	int tiempoRefrezco;
	int cantidadEnConfiguracion;
	AdministradorClientes* administrador;
protected:
	void run();
public:
	/**
	 * Constructor
	 * @param timeOutEnSegundos es el tiempo en segundos que
	 * indica cada cuanto se realiza una nueva verificacion
	 * @param timeOutConfig es el tiempo de timeOut que los clientes no deben pasar.
	 * Una vez que el cliente supera ese limite es dado de baja
	 * @admin es una referencia al administrador de clientes asociado al servidor.
	 */
	VerificadorTimeOut(int timeOutEnSegundos, int timeOutConfig,
			AdministradorClientes* admin);

	/**
	 * Destructor
	 */
	virtual ~VerificadorTimeOut();
};
#endif /* VERIFICADORTIMEOUT_H_ */
