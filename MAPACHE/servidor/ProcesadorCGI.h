#ifndef CGI_H_
#define CGI_H_

#include "Thread.h"
#include "TCPSocket.h"
#include "SocketException.h"
#include "HTTP_Request.h"
#include "HTTP_Response.h"
#include "ProtocoloHTTP.h"
#include "IProcesador.h"
#include "Configuracion.h"

#include <list>
#include <iterator>
#include <string>
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::iterator;
using std::list;
using std::string;

class ProcesadorCGI: public IProcesador {
private:
	string dir;
	string rutaCGI;
	const Configuracion& config;

	/**
	 * Crea una nueva instancia de HTTP_Response y setea su contenido con 
	 * el archivo que tiene como ruta a rutaCompletaArchSalida.
	 * @param rutaCompletaArchSalida
	 * @return HTTP_Response*
	 */
	HTTP_Response* setResponse(const char* rutaCompletaArchSalida);
	/**
	 * Elimina los archivos y/o directorios creados por el CGI, luego de finalizada su ejecucion.
	 * @param rutaArchEntrada Ruta del archivo que el CGI toma como entrada.
	 * @param rutaArchSalida Ruta del archivo que el CGI genero como salida.
	 * @param directorioCGI Ruta del directorio en donde el CGI almaceno sus archivos.
	 * @return void
	 */
	void removerArchivosYDirectoriosTemporales(const string rutaArchEntrada, 
			const string rutaArchSalida, const string directorioCGI);
	/**
	 * Crea el archivo que el CGI tomara como entrada y lo carga con la cadena contenidoDeRequest.
	 * @param rutaCompletaArchEntradaTemp Ruta del archivo que el CGI toma como entrada.
	 * @param contenidoDeRequest Basicamente es el POST del request.
	 * @return void
	 */
	void crearArchivoTemporalParaSTDIN(const string& rutaCompletaArchEntradaTemp, const string& contenidoDeRequest);
	/**
	 * Genera el comando para terminal que se ejecutara para el CGI, segun los parametros pasados.
	 * @param rutaCGI Ruta relativa (del cgi) a la carpeta cgi-bin.
	 * @param uri
	 * @param nombreEntradaTemp Ruta del archivo que el CGI toma como entrada.
	 * @param nombreSalidaTemp Ruta del archivo que el CGI genera como salida.
	 * @param dirArchivosGeneradosPorCGI Ruta del directorio en donde el CGI almaceno sus archivos.
	 * @return void
	 */
	void prepararComandoDeTerminal(const string rutaCGI, const string& uri, 
			string& comando, const string& nombreEntradaTemp, 
			const string& nombreSalidaTemp, 
			const string& dirArchivosGeneradosPorCGI);
	/**
	 * Setea el valor de la variable de entorno content_length.
	 * @param valor
	 * @return void
	 */
	void setVariableContentLenght(int valor);
public:
	/**
	 * Constructor
	 */
	ProcesadorCGI(const Configuracion& config, const std::string& ruta , const std::string& rutaCgi);
	/**
	 * Destructor
	 */
	virtual ~ProcesadorCGI();
	/* Prepara al sistema y al CGI para su correcta ejecucion y luego lo ejecuta.
	 * Controla que el CGI exista y borra los archivos temporales que este cree.
	 * Se agrega al log la ejecucion del CGI en cuestion.
	 * @param request.
	 * @param rutaCGI Ruta relativa (del cgi) a la carpeta cgi-bin.
	 * @param pathAbsolutoDelRecurso.
	 * @param dirArchivosDeSalida Ruta absoluta del directorio en 
	 * donde el CGI almacenara los archivos que genere.
	 * @return HTTP_Response* Una nueva instancia de HTTP_Response, 
	 * seteada con la salida generada por el CGI.
	 *  */
	HTTP_Response* procesarCGI(HTTP_Request* request, string rutaCGI, 
			const string& pathAbsolutoDelRecurso, string dirArchivosDeSalida);
	/**
	 * Metodo que implementa de IProcesador.
	 * @param pedido es el pedido a procesar
	 * @return es la respuesta generada por el pedido
	 */
	HTTP_Response* procesar(HTTP_Request* pedido);
};

#endif /*CGI_H_*/