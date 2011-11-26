/*
 * ManejadorLogs.h
 *
 *  Created on: 12/11/2011
 *      Author: pablo
 */

#ifndef MANEJADORLOGS_H_
#define MANEJADORLOGS_H_

#include "Log.h"
#include "ConfiguracionLogs.h"
#include "Mutex.h"
#include "Lock.h"

/**
 * Clase encargada de manejar los logs.
 * Los logs son unicos dentro de la aplicacion. Es por eso que se utiliza
 * el patron singleton. De esa manera las instacias son unicas.
 */
class ManejadorLogs {
private:
	/**
	 * Clase encargada de encapsular el puntero al manejador. Esto es para evitar perder
	 * la memoria asociada al mismo sin que nadie tenga que liberarla.
	 * Se libera automaticamente
	 */
	class Ptr {
	public:
		Ptr() : m_ptr(0) {}
		~Ptr() {
			if(m_ptr)
				delete m_ptr;
		}

		ManejadorLogs* Get() {
			return m_ptr;
		}

		void Set(ManejadorLogs* p) {
			if(p!= 0) {
				delete m_ptr;
				m_ptr = p;
			}
		}
	private:
		ManejadorLogs* m_ptr;
	};

	static Ptr pinstance;
	static Mutex mutex;

public:
	/**
	 * Devuelve la instancia del manejador.
	 */
	static ManejadorLogs* getInstance(const ConfiguracionLogs& conf) {
		if(pinstance.Get() == 0) {
			Lock l(mutex);
			if(pinstance.Get() == 0)
				pinstance.Set(new ManejadorLogs(conf));
		}
		return pinstance.Get();
	};

	/**
	 * Devuelve el log de acceso asociado al manejador
	 */
	Log* getLogAcceso();

	/**
	 * Devuelve el log de errores asociado al manejador
	 */
	Log* getLogError();
protected:
	ManejadorLogs(const ConfiguracionLogs& c);
	ManejadorLogs(const ManejadorLogs & ) ;
	ManejadorLogs &operator= (const ManejadorLogs & ) ;
	~ManejadorLogs();
private:
	Log* logError;
	Log* logAcceso;
};

#endif /* MANEJADORLOGS_H_ */
