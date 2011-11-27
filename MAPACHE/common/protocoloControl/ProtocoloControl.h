/*
 * ProtocoloControl.h
 *
 *  Created on: 23/10/2011
 *      Author: pablo
 */

#ifndef PROTOCOLOCONTROL_H_
#define PROTOCOLOCONTROL_H_

#include "TCPSocket.h"
#include "ProtocoloControlException.h"

/**
 * Codigos de control
 */
#define CODIGO_DETENER_SERVIDOR 'D'
#define CODIGO_DETENIDO_OK 'S'
#define CODIGO_DETENIDO_ERROR 'E'

/**
 * Clase utilizada para abstraer los mensajes necesarios para la
 * comunicación entre un cliente controlador y un servidor.
 */
class ProtocoloControl {
private:
	TCPSocket& socket;
    char recibirCaracter();
    void enviarCaracter(char codigoDetener);
public:
    /**
     * Constructor
     * @param sock es un socket que ya esta conectado.
     */
	explicit ProtocoloControl(TCPSocket& sock);

	/**
	 * Destructor
	 */
	virtual ~ProtocoloControl();

	/**
	 * Envia una operación pidiendo que se detenga el servidor que tiene
	 * como controlador al socket indicado.
	 */
	void enviarOperacionDetenerServidor();

	/**
	 * Recibe una respuesta a traves del socket y devuelve el resultado
	 * @return true si fue detenido, false en otro caso
	 */
	bool recibirRespuestaDetenido();

	/*
	 * Envia una respuesta indicando si hubo exito o no en la
	 * detencion del servidor
	 * @param conExito = true si fue detenido, false en otro caso
	 */
	void enviarRespuestaDetenido(bool conExito);

	/*
	 * Recibe una respuesta que indica si hay que tener el
	 * servidor o no.
	 * @return devuelve true si hay que detener, false en otro caso
	 */
	bool recibirOperacionDetener();
};

#endif /* PROTOCOLOCONTROL_H_ */
