/*
 * Configuracion.cpp
 *
 *  Created on: 13/10/2011
 *      Author: pablo
 */

#include "Configuracion.h"
#include <tinyxml.h>

Configuracion::Configuracion() {
}

void Configuracion::liberarRecursosErrores()
{
    std::map<int,TipoError*>::iterator itErrores;
    for(itErrores = errores.begin();itErrores != errores.end();itErrores++){
        delete itErrores->second;
    }
}

Configuracion::~Configuracion() {
    liberarRecursosDinamicos();
    liberarRecursosEstaticos();
    liberarRecursosUsuarios();
    liberarRecursosErrores();
}

bool Configuracion::agregarTipoEstatico(TipoEstatico* tipoEstatico) {
	std::pair<std::map<std::string,TipoEstatico*>::iterator , bool> retorno;
	std::pair<std::string , TipoEstatico*> elemento(tipoEstatico->getExtension() , tipoEstatico);
	retorno = estaticos.insert(elemento);
	if(retorno.second == false) {
		delete tipoEstatico;
		return false;
	} else {
		return true;
	}
}

bool Configuracion::agregarTipoDinamico(TipoDinamico* tipoDinamico) {
	 std::pair<std::map<std::string,TipoDinamico*>::iterator , bool> retorno;
	 std::pair<std::string , TipoDinamico*> elemento(tipoDinamico->getExtension() , tipoDinamico);
	 retorno = dinamicos.insert(elemento);
	 if(retorno.second == false) {
		 delete tipoDinamico;
		 return false;
	 } else {
		 return true;
	 }
}

bool Configuracion::agregarError(TipoError* error) {
	std::pair<std::map<int ,TipoError*>::iterator , bool> retorno;
	std::pair<int , TipoError*> elemento(error->getNroError() ,error);
	retorno = errores.insert(elemento);
	if(retorno.second == false) {
		delete error;
		return false;
	} else {
		return true;
	}
}

bool Configuracion::agregarUsuario(Usuario* usuario) {
	 std::pair<std::map<std::string,Usuario*>::iterator , bool> retorno;
	 std::pair<std::string , Usuario*> elemento(usuario->getNombre() , usuario);
	 retorno = usuarios.insert(elemento);
	 if(retorno.second == false) {
		 delete usuario;
		 return false;
	 } else {
		 return true;
	 }
}

bool Configuracion::removerTipoEstatico(const std::string& extension) {
	std::map<std::string , TipoEstatico*>::iterator it;
	it = estaticos.find(extension);
	if(it != estaticos.end()) {
		delete it->second;
		estaticos.erase(it);
		return true;
	} else {
		return false;
	}
}

bool Configuracion::removerTipoDinamico(const std::string& extension) {
	std::map<std::string , TipoDinamico*>::iterator it;
	it = dinamicos.find(extension);
	if(it != dinamicos.end()) {
		delete it->second;
		dinamicos.erase(it);
		return true;
	} else {
		return false;
	}
}

bool Configuracion::removerError(int codigo) {
	std::map<int , TipoError*>::iterator it;
		it = errores.find(codigo);
		if(it != errores.end()) {
			delete it->second;
			errores.erase(it);
			return true;
		} else {
			return false;
		}
}

bool Configuracion::removerUsuario(const std::string& nombre) {
	std::map<std::string , Usuario*>::iterator it;
	it = usuarios.find(nombre);
	if(it != usuarios.end()) {
		delete it->second;
		usuarios.erase(it);
		return true;
	} else {
		return false;
	}
}

std::string Configuracion::getTipoEstatico(const std::string& extension) const{
	std::map<std::string , TipoEstatico*>::const_iterator it = estaticos.find(extension);
	if(it != estaticos.end())
		return it->second->getContenido();
	else
		return "";
}

std::string Configuracion::getTipoDinamico(const std::string& extension) const{
	std::map<std::string , TipoDinamico*>::const_iterator it = dinamicos.find(extension);
	if(it != dinamicos.end())
		return it->second->getComando();
	else
		return "";
}

std::string Configuracion::getError(int codigo) const{
	std::map<int , TipoError*>::const_iterator it = errores.find(codigo);
		if(it != errores.end())
			return it->second->getRuta();
		else
			return "";
}

std::string Configuracion::getPassUsuario(const std::string& nombreUsuario) const{
	std::map<std::string , Usuario*>::const_iterator it = usuarios.find(nombreUsuario);
	if(it != usuarios.end())
		return it->second->getClave();
	else
		return "";
}

void Configuracion::setConfiguracionLogs(ConfiguracionLogs config) {
	this->logs = config;
}

ConfiguracionLogs Configuracion::getConfiguracionLogs() const {
	return this->logs;
}

ConfiguracionBasica Configuracion::getConfiguracionBasica() const {
	return this->basica;
}

void Configuracion::setConfiguracionBasica(ConfiguracionBasica config) {
	this->basica = config;
}

bool Configuracion::cargarDesde(const std::string& path) {
	bool cargadoOk = false;
	TiXmlDocument doc(path);
	if(doc.LoadFile(path , TIXML_ENCODING_UTF8)) {
		// cargar configuracion desde el archivo.
		try {
			TiXmlElement *nodoConfiguracion = doc.FirstChildElement("configuracion");
			cargarConfiguracionBasica(nodoConfiguracion);
			cargarTiposEstaticos(nodoConfiguracion);
			cargarTiposDinamicos(nodoConfiguracion);
			cargarErrores(nodoConfiguracion);
			cargarUsuarios(nodoConfiguracion);
			cargarLogs(nodoConfiguracion);
			cargadoOk = true;
		} catch (const std::exception&) {
			cargadoOk = false;
		}
	}
	return cargadoOk;
}

void Configuracion::guardarComo(const std::string& path) {
	TiXmlDocument doc;
	// cargar contenido al documento
    agregarDeclaracionXml(doc);
    TiXmlElement* nodoConfiguracion = new TiXmlElement("configuracion");
    agregarConfiguracionBasica(nodoConfiguracion);
    agregarTiposEstaticos(nodoConfiguracion);
    agregarTiposDinamicos(nodoConfiguracion);
    agregarErrores(nodoConfiguracion);
    agregarUsuarios(nodoConfiguracion);
    agregarLogs(nodoConfiguracion);
    doc.LinkEndChild(nodoConfiguracion);
	doc.SaveFile(path);
}


void Configuracion::cargarLogs(TiXmlElement* nodo) {
	TiXmlElement *nodoUsuarios = nodo->FirstChildElement("configuracionLogs");
	std::string accesos = nodoUsuarios->Attribute("logAccesos");
	std::string errores = nodoUsuarios->Attribute("logErrores");
	this->logs.setRutaLogAccesos(accesos);
	this->logs.setRutaLogErrores(errores);
}

void Configuracion::liberarRecursosDinamicos() {
    std::map<std::string,TipoDinamico*>::iterator itDinamicos;
    for(itDinamicos = dinamicos.begin() ; itDinamicos != dinamicos.end() ; itDinamicos++) {
        delete itDinamicos->second;
    }
}

void Configuracion::liberarRecursosEstaticos() {
    std::map<std::string,TipoEstatico*>::iterator itEstaticos;
    for(itEstaticos = estaticos.begin() ; itEstaticos != estaticos.end() ; itEstaticos++) {
        delete itEstaticos->second;
    }
}

void Configuracion::liberarRecursosUsuarios() {
    std::map<std::string,Usuario*>::iterator itUsuario;
    for(itUsuario = usuarios.begin();itUsuario != usuarios.end();itUsuario++){
        delete itUsuario->second;
    }
}

void Configuracion::agregarDeclaracionXml(TiXmlDocument & doc) {
    TiXmlDeclaration *declaracionXml = new TiXmlDeclaration("1.0", "", "");
    doc.LinkEndChild(declaracionXml);
}

void Configuracion::agregarConfiguracionBasica(TiXmlElement* & doc) {
    TiXmlElement *nodoConfiguracionBasica = new TiXmlElement("configuracionBasica");
    nodoConfiguracionBasica->SetAttribute("puerto", this->basica.getPuerto());
    nodoConfiguracionBasica->SetAttribute("puertoControl", this->basica.getPuertoControl());
    nodoConfiguracionBasica->SetAttribute("maximoConexiones", this->basica.getMaximoConexiones());
    nodoConfiguracionBasica->SetAttribute("maximoConexionesCliente", this->basica.getMaximoConexionesCliente());
    nodoConfiguracionBasica->SetAttribute("raiz", this->basica.getRaiz());
    if(this->basica.getProteccion())
    	nodoConfiguracionBasica->SetAttribute("protegido", "si");
    else
    	nodoConfiguracionBasica->SetAttribute("protegido", "no");
    nodoConfiguracionBasica->SetAttribute("timeOut", this->basica.getTimeOut());
    doc->LinkEndChild(nodoConfiguracionBasica);
}

void Configuracion::agregarLogs(TiXmlElement*& nodo) {
	TiXmlElement *nodoConfiguracionLogs = new TiXmlElement("configuracionLogs");
	nodoConfiguracionLogs->SetAttribute("logAccesos" , this->logs.getRutaLogAccesos());
	nodoConfiguracionLogs->SetAttribute("logErrores" , this->logs.getRutaLogErrores());
	nodo->LinkEndChild(nodoConfiguracionLogs);
}

void Configuracion::agregarTiposEstaticos(TiXmlElement* & doc) {
    TiXmlElement *nodoTiposEstaticos = new TiXmlElement("tiposEstaticos");
    std::map<std::string,TipoEstatico*>::iterator it;
    for(it = estaticos.begin();it != estaticos.end();it++){
        TiXmlElement *nodoTipoEstatico = new TiXmlElement("tipoEstatico");
        nodoTipoEstatico->SetAttribute("extension", it->second->getExtension());
        nodoTipoEstatico->SetAttribute("contenido", it->second->getContenido());
        nodoTiposEstaticos->LinkEndChild(nodoTipoEstatico);
    }
    doc->LinkEndChild(nodoTiposEstaticos);
}

void Configuracion::agregarTiposDinamicos(TiXmlElement* & doc) {
    TiXmlElement *nodoTiposDinamicos = new TiXmlElement("tiposDinamicos");
    std::map<std::string,TipoDinamico*>::iterator it;
    for(it = dinamicos.begin();it != dinamicos.end();it++){
        TiXmlElement *nodoTipoDinamico = new TiXmlElement("tipoDinamico");
        nodoTipoDinamico->SetAttribute("extension", it->second->getExtension());
        nodoTipoDinamico->SetAttribute("comando", it->second->getComando());
        nodoTiposDinamicos->LinkEndChild(nodoTipoDinamico);
    }
    doc->LinkEndChild(nodoTiposDinamicos);
}

void Configuracion::agregarErrores(TiXmlElement* & doc) {
    TiXmlElement *nodoErrores = new TiXmlElement("errores");
    std::map<int,TipoError*>::iterator it;
    for(it = errores.begin();it != errores.end();it++){
        TiXmlElement *nodoError = new TiXmlElement("error");
        nodoError->SetAttribute("codigo", it->first);
        nodoError->SetAttribute("path", it->second->getRuta());
        nodoErrores->LinkEndChild(nodoError);
    }
    doc->LinkEndChild(nodoErrores);
}

void Configuracion::agregarUsuarios(TiXmlElement* & doc) {
    TiXmlElement *nodoTiposEstaticos = new TiXmlElement("usuarios");
    std::map<std::string,Usuario*>::iterator it;
    for(it = usuarios.begin();it != usuarios.end();it++){
        TiXmlElement *nodoTipoEstatico = new TiXmlElement("usuario");
        nodoTipoEstatico->SetAttribute("nombre", it->second->getNombre());
        nodoTipoEstatico->SetAttribute("pass", it->second->getClave());
        nodoTiposEstaticos->LinkEndChild(nodoTipoEstatico);
    }
    doc->LinkEndChild(nodoTiposEstaticos);
}

void Configuracion::cargarConfiguracionBasica(TiXmlElement* doc) {
    // cargar configuracion desde el archivo.
    TiXmlElement *confBasica = doc->FirstChildElement("configuracionBasica");
    int puerto = 0;
    confBasica->Attribute("puerto", &puerto);
    this->basica.setPuerto(puerto);
    int puertoControl = 0;
    confBasica->Attribute("puertoControl", &puertoControl);
    this->basica.setPuertoControl(puertoControl);
    int maxConexiones = 0;
    confBasica->Attribute("maximoConexiones", &maxConexiones);
    this->basica.setMaximoConexiones(maxConexiones);
    int maxConexionesCliente = 0;
    confBasica->Attribute("maximoConexionesCliente", &maxConexionesCliente);
    this->basica.setMaximoConexionesCliente(maxConexionesCliente);
    std::string raiz;
    raiz = confBasica->Attribute("raiz");
    this->basica.setRaiz(raiz);
    std::string protegido;
    protegido = confBasica->Attribute("protegido");
    if(protegido == "si")
        this->basica.proteger();

    else
        this->basica.desproteger();

    int timeOut = 0;
    confBasica->Attribute("timeOut", &timeOut);
    this->basica.setTimeOut(timeOut);
}

std::list<TipoEstatico> Configuracion::getTiposEstaticos() const {
	std::list<TipoEstatico> lista;
	std::map<std::string , TipoEstatico*>::const_iterator it = this->estaticos.begin();
	for( ; it != this->estaticos.end() ;
			it++) {
		lista.push_back(*(it->second));
	}
	return lista;
}

std::list<TipoDinamico> Configuracion::getTiposDinamicos() const {
	std::list<TipoDinamico> lista;
	std::map<std::string , TipoDinamico*>::const_iterator it;
	for(it = this->dinamicos.begin() ; it != this->dinamicos.end() ;
			it++) {
		lista.push_back(*(it->second));
	}
	return lista;
}

std::list<Usuario> Configuracion::getUsuarios() const {
	std::list<Usuario> lista;
	std::map<std::string , Usuario*>::const_iterator it;
	for(it = this->usuarios.begin() ; it != this->usuarios.end() ; it++) {
		lista.push_back(*(it->second));
	}
	return lista;
}

std::list<TipoError> Configuracion::getTiposErrores() const {
	std::list<TipoError> lista;
	std::map<int , TipoError*>::const_iterator it;
	for(it = this->errores.begin() ; it != this->errores.end() ; it++) {
		lista.push_back(*(it->second));
	}
		return lista;
}


void Configuracion::cargarTiposEstaticos(TiXmlElement* doc) {
    TiXmlElement *nodoEstaticos = doc->FirstChildElement("tiposEstaticos");
    TiXmlElement *nodoEstatico = nodoEstaticos->FirstChildElement("tipoEstatico");
    while(nodoEstatico != NULL) {
    	std::string extension = nodoEstatico->Attribute("extension");
    	std::string contenido = nodoEstatico->Attribute("contenido");
    	TipoEstatico* t = new TipoEstatico();
    	t->setExtension(extension);
    	t->setContenido(contenido);
    	this->agregarTipoEstatico(t);
    	nodoEstatico = nodoEstatico->NextSiblingElement();
    }
}

void Configuracion::cargarTiposDinamicos(TiXmlElement* doc)
{
    TiXmlElement *nodoDinamicos = doc->FirstChildElement("tiposDinamicos");
    TiXmlElement *nodoDinamico = nodoDinamicos->FirstChildElement("tipoDinamico");
    while(nodoDinamico != NULL) {
	    	std::string extension = nodoDinamico->Attribute("extension");
	    	std::string comando = nodoDinamico->Attribute("comando");
	    	TipoDinamico* t = new TipoDinamico();
	    	t->setExtension(extension);
	    	t->setComando(comando);
	    	this->agregarTipoDinamico(t);
	    	nodoDinamico = nodoDinamico->NextSiblingElement();
	    }
}

void Configuracion::cargarErrores(TiXmlElement* doc)
{
    TiXmlElement *nodoErrores = doc->FirstChildElement("errores");
    TiXmlElement *nodoError = nodoErrores->FirstChildElement("error");
    while(nodoError != NULL) {
	    	int codigo;
	    	nodoError->Attribute("codigo" , &codigo);
	    	std::string path = nodoError->Attribute("path");
	    	TipoError* error = new TipoError();
	    	error->setNroError(codigo);
	    	error->setRuta(path);
	    	this->agregarError(error);
	    	nodoError = nodoError->NextSiblingElement();
	    }
}

void Configuracion::cargarUsuarios(TiXmlElement* doc)
{
    TiXmlElement *nodoUsuarios = doc->FirstChildElement("usuarios");
    TiXmlElement *nodoUsuario = nodoUsuarios->FirstChildElement("usuario");
    while(nodoUsuario != NULL) {
	    	std::string nombre = nodoUsuario->Attribute("nombre");
	    	std::string pass = nodoUsuario->Attribute("pass");
	    	Usuario* t = new Usuario();
	    	t->setNombre(nombre);
	    	t->setClave(pass);
	    	this->agregarUsuario(t);
	    	nodoUsuario = nodoUsuario->NextSiblingElement();
	    }
}
