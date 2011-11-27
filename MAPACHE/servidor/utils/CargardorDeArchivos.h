/*
 * CargardorDeArchivos.h
 *
 *  Created on: 04/11/2011
 *      Author: pablo
 */

#ifndef CARGARDORDEARCHIVOS_H_
#define CARGARDORDEARCHIVOS_H_

#include <string>
#include <sstream>
#include <fstream>
#include "ErrorArchivoException.h"

#define MAX_BUFFER 100

/**
 * Clase encargada de cargar un archivo para poder devolverlo luego.
 */
class CargardorDeArchivos {
public:
	/**
	 * Constructor
	 */
	CargardorDeArchivos();

	/**
	 * Destructor
	 */
	virtual ~CargardorDeArchivos();

	/**
	 * Metodo encargado de levantar el archivo y devolverlo.
	 * @param archivo es el path del archivo a devolver
	 * @return es la cadena asociada al archivo
	 */
	static std::string levantarArchivo(const std::string& archivo) {
		std::ifstream archivoPedido(archivo.c_str(),
				std::ios::in | std::ios::binary);
		if (archivoPedido.fail()) {
			throw ErrorArchivoException();
		}
		archivoPedido.seekg(0, std::ios::end);
		size_t tam = archivoPedido.tellg();
		archivoPedido.seekg(0, std::ios::beg);
		char* buffer = new char[tam];
		archivoPedido.read(buffer, tam);
		std::stringstream ssCadena;
		ssCadena.write(buffer, tam);
		delete[] buffer;
		return ssCadena.str();
	}

	/**
	 * Metodo encargado de levantar el archivo y devolverlo.
	 * @param archivo es el path del archivo a devolver
	 * @return es la cadena asociada al archivo
	 */
	static std::string levantarArchivoVersionGET(const std::string& archivo) {
		std::ifstream archivoPedido(archivo.c_str());
		if (archivoPedido.fail()) {
			throw ErrorArchivoException();
		}
		std::string cadena;
		while (!archivoPedido.eof()) {
			char buffer[MAX_BUFFER];
			archivoPedido.read(buffer, MAX_BUFFER);
			if (archivoPedido.gcount() > 0)
				cadena.append(buffer, archivoPedido.gcount());
		}
		return cadena;
	}
};

#endif /* CARGARDORDEARCHIVOS_H_ */
