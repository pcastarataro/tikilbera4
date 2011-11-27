/*
 * HTTP_Request.h
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_
#include <string>
#include <map>
#include "HTTP_Message.h"

/**
 * Clase encargada de representar un pedido de protocolo HTTP
 */
class HTTP_Request: public HTTP_Message {
private:
	std::pair<std::string, std::string> Dato;
	std::map<std::string, std::string> idMapas;
	void generarMapa(const std::string& mensaje);
	std::string getValor(const std::string& clave);
	std::string contenido;
public:
	/**
	 * Contructor
	 */
	HTTP_Request();

	/**
	 * Constructor
	 * @param cadena es la cadena que recibe el socket indicando el pedido.
	 */
	explicit HTTP_Request(const std::string& entrada);

	/**
	 * Destructor
	 */
	virtual ~HTTP_Request();

	/**
	 * Devuelve el metodo que pedia el pedido
	 * @return metodo
	 */
	std::string getMethod();

	/**
	 * Devuelve el URI del pedido
	 * @return URI
	 */
	std::string getUri();

	/**
	 * Devuelve el host del pedido
	 * @return HOST
	 */
	std::string getHost();

	/**
	 * Devuelve la conexion del pedido
	 * @return CONNECTION
	 */
	std::string getConnection();

	/**
	 * Devuelve el user agent del pedido
	 * @return User Agent
	 */
	std::string getUserAgent();

	/**
	 * Devuelve el type text del pedido
	 * @return type text
	 */
	std::string getTypeText();

	/**
	 * Devuelve la autorizacion asociada al pedido
	 * @return autorizacion
	 */
	std::string getAuthorization();

	/**
	 * Devuelve el contenido de la peticion. En caso de ser un get será vacio.
	 * @return contenido de la peticion. "" para GET y algún contenido para el post
	 */
	std::string getContenido();

	std::string getAuthentication();

	/**
	 * Devuelve la longitud del contenido
	 */
	int getContentLength();

	/**
	 * Setea el contenido al request
	 */
	void setContenido(const std::string& cont);
};

#endif /* HTTP_REQUEST_H_ */
