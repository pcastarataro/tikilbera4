/*
 * AdministradorClientes.h
 *
 *  Created on: 31/10/2011
 *      Author: pablo
 */

#ifndef ADMINISTRADORCLIENTES_H_
#define ADMINISTRADORCLIENTES_H_

#include <map>
#include <string>
#include "Configuracion.h"
#include "Mutex.h"
#include "ManejadorClienteHTTP.h"

/**
 * Clase encargada de administrar los clientes dentro del servidor.
 * Esta clase es la encargada de determinar si un cliente puede ser atendido
 * o no segun la configuracion asociada al servidor.
 */
class AdministradorClientes {
private:
	const Configuracion& config;
	Mutex mutex;
	std::map<std::string , std::list<ManejadorClienteHTTP*> > mapaIpConexiones;
	int total;
    void limpiarActivos();
    void avisarSobrecargaServidor(ManejadorClienteHTTP *manejador);
public:
    /**
     * Contructor.
     * @param config es la conficuracion asociada al servidor
     */
	AdministradorClientes(const Configuracion& config);

	/**
	 * Destructor
	 */
	virtual ~AdministradorClientes();

	/**
	 * Agrega el manejador de un cliente al servidor.
	 * En el caso de no poder atenderlo, devuelve una respuesta al mismo indicandolo.
	 * En otro caso lo atiende.
	 */
	void agregarCliente(ManejadorClienteHTTP* manejador);

	/**
	 * Limpia todos los manejadores que ya han finalizado su ejecución
	 */
	void limpiarFinalizados();

	/**
	 * Limpia todos los manejadores que tienen timeOut mayor al indicado
	 * en la configuracion.
	 */
	void limpiarActivosConTimeOutMayor();
};

#endif /* ADMINISTRADORCLIENTES_H_ */
