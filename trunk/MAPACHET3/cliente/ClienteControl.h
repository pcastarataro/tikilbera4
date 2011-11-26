#ifndef CLIENTECONTROL_H_
#define CLIENTECONTROL_H_
#include <iostream>

/**
 * Clase que se encarga de detener el servidor
 */
class ClienteControl {
public:

	/**
	 * Constructor
	 */
	ClienteControl();

	/**
	 * Destructor
	 */
	virtual ~ClienteControl();

	/**
	 * Si el servidor se encuentra encendido, lo detiene.
	 * @param ip Ip del servidor
	 * @param puerto Puerto del servidor
	 * @return true si se detiene el servidor false si no se puede detener el servidor.
	 */
	bool detenerServidor(const std::string& ip, unsigned int puerto);
};
#endif
