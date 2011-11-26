/*
 * Thread.h
 *
 *  Created on: 28/04/2011
 *      Author: pablo
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

/**
 * Clase abstracta utilizada para abstraer los sockets de c.
 * Para utilizarla se deberán crear clases derivadas de esta
 * que implementen el metodo void run();
 */
class Thread {
private:
	pthread_t h;
	static void* init(void* data) {
		Thread* h = (Thread*)data;
		h->run();
		return NULL;
	};
	bool vida;
protected:
	virtual void run() = 0;
public:
	/**
	 * Constructor
	 */
	Thread();

	/**
	 * Empieza a correr el hilo
	 */
	void start();

	/**
	 * Joinea el hilo.
	 */
	void join();

	/**
	 * Devuelve el estado del hilo
	 * @return estado
	 */
	bool vivo();

	/**
	 * Hace que el hilo cambie su estado a muerto.
	 */
	void morir();
};

#endif /* THREAD_H_ */
