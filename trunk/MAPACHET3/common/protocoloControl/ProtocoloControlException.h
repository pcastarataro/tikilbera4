/*
 * ProtocoloControlException.h
 *
 *  Created on: 23/10/2011
 *      Author: pablo
 */

#ifndef PROTOCOLOCONTROLEXCEPTION_H_
#define PROTOCOLOCONTROLEXCEPTION_H_

#include <exception>

class ProtocoloControlException: public std::exception {
public:
	ProtocoloControlException();
};

#endif /* PROTOCOLOCONTROLEXCEPTION_H_ */
