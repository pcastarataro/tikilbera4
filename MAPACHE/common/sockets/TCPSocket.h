/*
 * Socket.h
 *
 *  Created on: 12/05/2011
 *      Author: pablo
 */

#ifndef SOCKET_H_
#define SOCKET_H_
#define MAX_COLA 20
#include <string>

/**
 * Clase utilizada para abstraer el comportamiento de los sockets de c.
 */
class TCPSocket {
private:
	std::string ip;
protected:
	int descriptor;
	bool apagado;
	bool cerrado;
public:
	/**
	 * Constructor.
	 */
	TCPSocket();

	/**
	 * Constructor.
	 */
	explicit TCPSocket(int descriptor);

	/**
	 * Destructor.
	 */
	virtual ~TCPSocket();

	/**
	 * Metodo encargado de setear a un socket como reusable.
	 * Esto quiere decir que si se setea esta propiedad entonces
	 * no se tendrá en cuenta si el socket ya estaba abierto.
	 * Se debe setear luego del constructor y antes de cualquier otro
	 * metodo
	 */
	void setearComoReusable();

	/**
	 * Le indica al socket cual será la dirección donde
	 * escuchará las nuevas conexiones.
	 * @param puerto es puerto donde escuchará las conexiones.
	 */
	void bindear(int puerto);

	/**
	 * Le indica al sistema operativo que el socket
	 * debe empezar a recibir conexiones entrantes.
	 * @param max_cola_conexiones es para indicar que
	 * tamaño máximo tendrá la cola de conexiones
	 * entrantes.
	 */
	void escuchar(int max_cola_conexiones);

	/**
	 * Conecta al socket con la dirección indicada y el puerto
	 * indicado.
	 * @param ip es el puerto donde se desea conectar
	 * @param puerto es el puerto donde se desea conectar
	 */
	void conectar(const std::string& ip , int puerto);

	/**
	 * Le indica al socket que debe dejar de emitir y recibir datos.
	 */
	void apagar();

	/**
	 * Cierra el socket
	 */
	void cerrar();

	/**
	 * Valido solo para sockets que fueron bindeados y que estan escuchando.
	 *
	 * Acepta una nueva conexion desde la cola de conexiones.
	 * @return TCPSocket* es el socket del nuevo cliente aceptado.
	 */
	TCPSocket* aceptar();

	/**
	 * Envia la cantidad de bytes indicada por longitud a partir de la
	 * posicion indicada por data
	 * @param data direccion desde donde tomar los datos
	 * @param longitud es el tamaño de los datos que se deben transmitir
	 */
	void enviar(char* data , int longitud);

	/*
	 * Recibe la cantidad de bytes indicada por la longitud y lo guarda
	 * a partir de la posicion indicada
	 * @param data es la posicion donde se dejaran los datos recibidos
	 * @param longitud de los datos que se desean recibir
	 */
	void recibir(char* data , int longitud);

	/**
	 * Devuelve el ip del socket
	 * @return ip del socket
	 */
	std::string getIp() const;
};

#endif /* SOCKET_H_ */
