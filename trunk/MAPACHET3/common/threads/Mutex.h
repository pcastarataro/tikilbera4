/*
 * Mutex.h
 *
 *  Created on: 01/05/2011
 *      Author: pablo
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

/**
 * Clase utilizada para representar un Mutex.
 */
class Mutex {
private:
	pthread_mutex_t mutex;
public:
	/**
	 * Constructor
	 */
	Mutex();

	/**
	 * Destructor
	 */
	~Mutex();

	/**
	 * Bloquea al mutex para que otro hilo no pueda utilizar
	 * el recurso asociado al mismo mutex
	 */
	void lock();

	/**
	 * Desbloquea al mutex para que otro hilo pueda utilizar el
	 * recurso asociado al mismo
	 */
	void unlock();
};

#endif /* MUTEX_H_ */
