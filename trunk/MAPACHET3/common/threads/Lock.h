/*
 * Lock.h
 *
 *  Created on: 01/05/2011
 *      Author: pablo
 */

#ifndef LOCK_H_
#define LOCK_H_

#include "Mutex.h"

/**
 * Clase utilizada para representar un Lockeo.
 */
class Lock {
private:
	Mutex& m;
public:
	/**
	 * Constructor: comienza el bloqueo en el mutex asociado
	 * @param m es un mutex
	 */
	Lock(Mutex& m);

	/*
	 * Destructor: libera el bloqueo del mutex asociado
	 */
	~Lock();
};

#endif /* LOCK_H_ */
