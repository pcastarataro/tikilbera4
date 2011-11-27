/*
 * Lock.cpp
 *
 *  Created on: 01/05/2011
 *      Author: pablo
 */

#include "Lock.h"

Lock::Lock(Mutex& mutex): m(mutex) {
	m.lock();
}

Lock::~Lock() {
	m.unlock();
}
