/*
 * ErrorArchivoException.h
 *
 *  Created on: 04/11/2011
 *      Author: pablo
 */

#ifndef ERRORARCHIVOEXCEPTION_H_
#define ERRORARCHIVOEXCEPTION_H_

#include <exception>

/**
 * Excepcion utilizada para indicar un error con el archivo
 */
class ErrorArchivoException: public std::exception {
public:
	/**
	 * Constructor
	 */
	ErrorArchivoException();
};

#endif /* ERRORARCHIVOEXCEPTION_H_ */
