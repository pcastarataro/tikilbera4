/*
 * Thread.cpp
 *
 *  Created on: 28/04/2011
 *      Author: pablo
 */

#include "Thread.h"

Thread::Thread() {
	this->vida = true;
}

void Thread::start() {
	pthread_create(&this->h , NULL , init , this);
}

void Thread::join() {
	pthread_join(this->h , NULL);
}

bool Thread::vivo() {
	return this->vida;
}

void Thread::morir() {
	this->vida = false;
}
