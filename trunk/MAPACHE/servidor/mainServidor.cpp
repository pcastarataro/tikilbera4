/*
 * mainServidor.cpp
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#include "Configuracion.h"
#include "Servidor.h"
#include "ServidorHttp.h"

#define ERROR_ARGUMENTOS 1
#define ERROR_ARCHIVO -1
#define EN_REINICIO "R"
#define CANT_ARGS 3

int main(int argc , char**args) {
	if(argc != CANT_ARGS)
		return ERROR_ARGUMENTOS;

	std::string nombreArchivo = args[1];
	std::string cadenaReinicio = args[2];
	bool reiniciar;
	cadenaReinicio == EN_REINICIO? reiniciar = true : reiniciar = false;

	Configuracion configuracionServidor;
	bool archivoValido = configuracionServidor.cargarDesde(nombreArchivo);
	if(!archivoValido)
		return ERROR_ARCHIVO;

	Servidor servidor(configuracionServidor , reiniciar);
	int res = servidor.start();  // ENCARGADO DE ESCUCHAR EL CIERRE DE SERVIDOR
	return res;
}
