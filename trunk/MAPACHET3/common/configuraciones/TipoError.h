/*
 * TipoError.h
 *
 *  Created on: 18/10/2011
 *      Author: pablo
 */

#ifndef TIPOERROR_H_
#define TIPOERROR_H_

#include <string>

/**
 * Clase utilizada para representar un error
 */
class TipoError {
private:
	int numero;
	std::string ruta;
public:
	/**
	 * Constructor
	 */
	TipoError();

	/**
	 * Destructor
	 */
	virtual ~TipoError();

	/**
	 * Devuelve el numero de error
	 * @return numero error
	 */
	int getNroError() const;

	/**
	 * Devuelve la ruta asociada al error
	 * @return ruta de la pagina de error
	 */
	const std::string& getRuta() const;

	/**
	 * Setea la ruta
	 * @param ruta ruta donde estara la pagina de error asociada al codigo
	 */
	void setRuta(const std::string& ruta);

	/**
	 * Setea el numero de error
	 * @param numero es el numero de error.
	 */
	void setNroError(int numero);
};

#endif /* TIPOERROR_H_ */
