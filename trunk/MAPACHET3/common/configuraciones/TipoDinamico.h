/*
 * TipoDinamico.h
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#ifndef TIPODINAMICO_H_
#define TIPODINAMICO_H_

#include "Tipo.h"

/**
 * Clase utilizada para representar un tipo dinamico
 */
class TipoDinamico: public Tipo {
private:
	std::string comando;
public:
	/**
	 * Constructor
	 */
	TipoDinamico();

	/**
	 * Destructor
	 */
	virtual ~TipoDinamico();

	/**
	 * Setea el comando del tipo dinamico
	 * @param comando es el comando que se ejecutara
	 */
	void setComando(const std::string& comando);

	/**
	 * Devuelve el comando asociado al tipo
	 * @return comando
	 */
	std::string getComando() const;
};

#endif /* TIPODINAMICO_H_ */
