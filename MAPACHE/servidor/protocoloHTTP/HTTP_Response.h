/*
 * HTTP_Response.h
 *
 *  Created on: 26/10/2011
 *      Author: pablo
 */

#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include "HTTP_Message.h"
#include "../utils/Time.h"

/**
 * Clase encargada de representar un response en el sistema
 */
class HTTP_Response: public HTTP_Message {
private:
	int codigoRetorno;
	std::string tipoContenido;
	int longitudContenido;
	std::string contenido;
	bool exigeAutentificacion;
	Time time;
public:
	/**
	 * Constructor
	 */
	HTTP_Response();

	/**
	 * Destructor
	 */
	virtual ~HTTP_Response();

	/**
	 * Agrega contenido al response
	 * @param contenido es lo que se desea agregar
	 */
	void agregarContenido(const std::string& contenido);

	/**
	 * Exige autentificacion.
	 */
	void exigirAutentificacion();

	/**
	 * Setea el codigo de la respuesta
	 * @param codigo es el codigo que se desea setear
	 */
	void setCodigoRetorno(int codigo);

	/**
	 * Setea el tipo de contenido. Se corresponde con el mimetype.
	 * @param tipo es el mime type
	 */
	void setTipoContenido(const std::string& tipo);

	/**
	 * Setea el contenido a la respuesta
	 * @param cont es el contenido que tendrá la respuesta
	 */
	void setContenido(const std::string& cont);

	/**
	 * Devuelve el response como una cadena de texto
	 * @return cadena representando el response
	 */
	std::string getCadena() const;
};

#endif /* HTTP_RESPONSE_H_ */
