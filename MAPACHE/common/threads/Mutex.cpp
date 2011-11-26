/*
 * Mutex.cpp
 *
 *  Created on: 01/05/2011
 *      Author: pablo
 */

#include "Mutex.h"

Mutex::Mutex() {
	pthread_mutex_init(&mutex , 0);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&mutex);
}

void Mutex::lock() {
	pthread_mutex_lock(&mutex);
}

void Mutex::unlock() {
	pthread_mutex_unlock(&mutex);
}
