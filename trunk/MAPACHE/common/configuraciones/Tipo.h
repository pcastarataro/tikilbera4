/*
 * Tipo.h
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#ifndef TIPO_H_
#define TIPO_H_

#include <string>

/**
 * Clase base para los tipos
 */
class Tipo {
private:
	std::string extension;
protected:
	Tipo();
public:
	/**
	 * Destructor
	 */
	virtual ~Tipo();

	/**
	 * Setea la extension
	 * @param extension es la extension del tipo
	 */
	void setExtension(const std::string& extension);

	/**
	 * Devuelve la extension
	 * @return devuelve la extension del tipo
	 */
	std::string getExtension() const;
};


#endif /* TIPO_H_ */
