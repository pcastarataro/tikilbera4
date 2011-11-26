/*
 * TipoEstatico.h
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#ifndef TIPOESTATICO_H_
#define TIPOESTATICO_H_

#include "Tipo.h"

/**
 * Clase que representa a un tipo estatico
 */
class TipoEstatico: public Tipo {
private:
	std::string contenido;
public:
	/**
	 * Constructor
	 */
	TipoEstatico();

	/**
	 * Destructor
	 */
	virtual ~TipoEstatico();

	/**
	 * Setea el contenido del tipo
	 * @param contenido es el contenido del tipo.
	 */
	void setContenido(const std::string& contenido);

	/**
	 * Devuelve el tipo del contenido.
	 */
	std::string getContenido() const;
};

#endif /* TIPOESTATICO_H_ */
