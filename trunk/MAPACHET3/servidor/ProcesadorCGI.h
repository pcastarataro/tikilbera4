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
	std::string dir;
	std::string rutaCGI;
	const Configuracion& config;

	HTTP_Response* setResponse(const char* rutaCompletaArchSalida);
	void removerArchivosYDirectoriosTemporales(const string rutaArchEntrada, const string rutaArchSalida, 
			const string directorioCGI);
	string crearDirectorioTemporalParaElCGI(int* nroCarpeta);
	void crearArchivoTemporalParaSTDIN(const string& rutaCompletaArchEntradaTemp, const string& contenidoDeRequest);
	void prepararComandoDeTerminal(const string rutaCGI, const string& uri, string& comando, const string& nombreEntradaTemp, 
			const string& nombreSalidaTemp, const string& dirArchivosGeneradosPorCGI);
	void setVariableContentLenght(int valor);
public:
	ProcesadorCGI(const Configuracion& config, const std::string& ruta , const std::string& rutaCgi);
	virtual ~ProcesadorCGI();
	HTTP_Response* procesarCGI(HTTP_Request* request, string rutaCGI, const string& pathAbsoluto, string dirArchivosDeSalida);
	HTTP_Response* procesar(HTTP_Request* pedido);
};

#endif /*CGI_H_*/
