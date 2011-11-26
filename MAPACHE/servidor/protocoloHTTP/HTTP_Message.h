/*
 * HTTP_Message.h
 *
 *  Created on: 27/10/2011
 *      Author: pablo
 */

#ifndef HTTP_MESSAGE_H_
#define HTTP_MESSAGE_H_

#include <string>

#define CRLF "\r\n"

/**
 * Clase utilizada para representar una mensaje HTTP
 */
class HTTP_Message {
private:
	std::string versionProtocolo;
protected:
	std::string getProtocolo() const;
public:
	/**
	 * Constructor
	 */
	HTTP_Message();

	/**
	 * Destructor
	 */
	virtual ~HTTP_Message();

	/**
	 * Setea el protocolo asociado al mensaje
	 * @mayor es el numero de version mayor del protocolo
	 * @menor es el numero de version menor del protocolo
	 * Ejemplo: 1.0 // mayor=1 ; menor=0
	 */
	void setProtocolo(int mayor , int menor);
};

#endif /* HTTP_MESSAGE_H_ */
