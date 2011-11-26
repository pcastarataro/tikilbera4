/*
 * Usuario.h
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include <string>

/**
 * Clase que representa a un usuario.
 */
class Usuario {
private:
	std::string nombre;
	std::string pass;
public:
	/**
	 * Constructor
	 */
	Usuario();

	/**
	 * Destructor
	 */
	~Usuario();

	/**
	 * Setea el nombre del usuario
	 * @param nombre es el nombre del usuario
	 */
	void setNombre(const std::string& nombre);

	/**
	 * Setea el pass del usuario
	 * @param setea la clave del usuario
	 */
	void setClave(const std::string& clave);

	/**
	 * Devuelve el nombre
	 * @return nombre del usuario
	 */
	std::string getNombre() const;

	/**
	 * Devuelve el pass del usuario
	 * @return pass del usuario
	 */
	std::string getClave() const;
};

#endif /* USUARIO_H_ */
