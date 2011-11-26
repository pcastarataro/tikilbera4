/*
 * Configuracion.h
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <map>
#include <string>
#include <list>
#include <tinyxml.h>
#include "ConfiguracionBasica.h"
#include "ConfiguracionLogs.h"
#include "TipoEstatico.h"
#include "TipoDinamico.h"
#include "TipoError.h"
#include "Usuario.h"

/**
 * Clase utilizada para abstraer el manejo de archivos xml en el
 * proceso de configurar y obtener datos desde la misma.
 * Es utilizada por el servidor y el configurador.
 */
class Configuracion {
private:
	ConfiguracionBasica basica;
	ConfiguracionLogs logs;
	std::map<std::string , TipoEstatico*> estaticos;
	std::map<std::string , TipoDinamico*> dinamicos;
	std::map<int , TipoError*> errores;
	std::map<std::string , Usuario*> usuarios;
public:
	/**
	 * Constructor
	 */
	Configuracion();

	/**
	 * Destructor
	 */
	~Configuracion();

	/**
	 * Setea la configuracion basica para esta configuracion
	 * @param config es una configuracion basica que se desee setear
	 */
	void setConfiguracionBasica(ConfiguracionBasica config);

	/**
	 * Setea la configuracion para los logs.
	 * @param config es una configuracion de log que se desea setear
	 */
	void setConfiguracionLogs(ConfiguracionLogs config);

	/**
	 * Agrega un nuevo tipo estatico a la configuracion
	 * @param tipoEstatico no nulo.
	 * @return true si no existia anteriormente, false si ya existia
	 */
	bool agregarTipoEstatico(TipoEstatico* tipoEstatico);

	/**
	 * Agrega un nuevo tipo dinamico a la configuracion
	 * @param tipoDinamico no nulo.
	 * @return true si no existia anteriormente, false si ya existia
	 */
	bool agregarTipoDinamico(TipoDinamico* tipoDinamico);

	/**
	 * Agrega un nuevo error a la configuracion
	 * @param tipoError no nulo.
	 * @return true si no existia anteriormente, false si ya existia
	 */
	bool agregarError(TipoError* tipoError);

	/**
	 * Agrega un nuevo usuario a la configuracion
	 * @param usuario no nulo.
	 * @return true si no existia anteriormente, false si ya existia
	 */
	bool agregarUsuario(Usuario* usuario);

	/**
	 * Remueve un tipo estatico que tiene la extension pasada
	 * @param extension es la extension del tipo estatico que se esta buscando
	 * @return devuelve true si lo encontro y lo borro, false en otro caso
	 */
	bool removerTipoEstatico(const std::string& extension);

	/**
	 * Remueve un tipo dinamico que tiene la extension pasada
	 * @param extension es la extension del tipo dinamico que se esta buscando
	 * @return devuelve true si lo encontro y lo borro, false en otro caso
	 */
	bool removerTipoDinamico(const std::string& extension);

	/**
	 * Remueve un error que tiene el codigo pasado
	 * @param codigo es numero del codigo que se esta buscando
	 * @return devuelve true si lo encontro y lo borro, false en otro caso
	 */
	bool removerError(int codigo);

	/**
	 * Remueve un usuario con el nombre dado
	 * @param nombre del usuario que se desea borrar
	 * @return devuelve true si lo encontro y lo borro, false en otro caso
	 */
	bool removerUsuario(const std::string& nombre);

	/**
	 * Devuelve el tipo estatico asociado a la extension
	 * @param extension es la extension que se esta buscando
	 * @return si lo encuentra devuelve el tipo, sino devuelve un string vacio
	 */
	std::string getTipoEstatico(const std::string& extension) const;

	/**
	 * Devuelve el tipo dinamico asociado a la extension
	 * @param extension es la extension que se esta buscando
	 * @return si lo encuentra devuelve el tipo, sino devuelve un string vacio
	 */
	std::string getTipoDinamico(const std::string& extension) const;

	/**
	 * Devuelve elerror asociado al codigo
	 * @param codigo es el numero que se esta buscando
	 * @return si lo encuentra devuelve el tipo, sino devuelve un string vacio
	 */
	std::string getError(int codigo) const;

	/**
	 * Devuelve el pass asociado al nombre del usuario
	 * @param nombreUsuario es el nombre del usuario buscado.
	 * @return si lo encuentra devuelve el tipo, sino devuelve un string vacio
	 */
	std::string getPassUsuario(const std::string& nombreUsuario) const;

	/**
	 * Devuelve la configuracion básica asociada a la confifuracion
	 * @return configuracion basica
	 */
	ConfiguracionBasica getConfiguracionBasica() const;

	/**
	 * Devuelve la configuracion de los logs
	 * @return configuracion de logs
	 */
	ConfiguracionLogs getConfiguracionLogs() const;

	/**
	 * Lista a los tipos estaticos asociados a la configuracion
	 * @return lista de tipos estaticos
	 */
	std::list<TipoEstatico> getTiposEstaticos() const;

	/**
	 * Lista a los tipos dinamicos asociados a la configuracion
	 * @return lista de tipos dinamicos
	 */
	std::list<TipoDinamico> getTiposDinamicos() const;

	/**
	 * Lista a los usuarios asociados a la configuracion
	 * @return lista de usuarios
	 */
	std::list<Usuario> getUsuarios() const;

	/**
	 * Lista a los errores asociados a la configuracion
	 * @return lista de errores.
	 */
	std::list<TipoError> getTiposErrores() const;

	/**
	 * Carga la configuracion desde el archivo xml
	 * @param path es la ruta del archivo xml que tiene la configuracion
	 * @return true si se pudo cargar, false si el archivo no existe
	 */
	bool cargarDesde(const std::string& path);

	/**
	 * Guarda la configuracion en el archivo
	 * @param path es la ruta donde se desea guardar el archivo
	 */
	void guardarComo(const std::string& path);
private:
	void liberarRecursosDinamicos();
	void liberarRecursosEstaticos();
	void liberarRecursosUsuarios();
	void liberarRecursosErrores();
	void cargarUsuarios(TiXmlElement *doc);
	void cargarErrores(TiXmlElement *doc);
	void cargarTiposDinamicos(TiXmlElement *doc);
	void cargarTiposEstaticos(TiXmlElement *doc);
	void cargarConfiguracionBasica(TiXmlElement *doc);
	void cargarLogs(TiXmlElement* nodo);
	void agregarUsuarios(TiXmlElement*& doc);
	void agregarErrores(TiXmlElement *& doc);
	void agregarTiposDinamicos(TiXmlElement *& doc);
	void agregarTiposEstaticos(TiXmlElement *& doc);
	void agregarConfiguracionBasica(TiXmlElement *& doc);
	void agregarLogs(TiXmlElement*& nodo);
	void agregarDeclaracionXml(TiXmlDocument & doc);
};

#endif /* CONFIGURACION_H_ */
