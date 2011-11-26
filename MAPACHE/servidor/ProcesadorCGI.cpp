#include "ProcesadorCGI.h"
#include "CargardorDeArchivos.h"
#include "ManejadorLogs.h"
#include <sstream>
#include <fstream>

#define NOMBRE_ENTRADA "post.tmp"
#define NOMBRE_SALIDA "salida.tmp"
#define CGI_BIN "cgi-bin"
using std::stringstream;
using std::ifstream;

ProcesadorCGI::ProcesadorCGI(const Configuracion& c, const std::string& ruta, 
		const std::string& rutaCGI): config(c) {
	this->dir = ruta;
	this->rutaCGI = rutaCGI;
}

ProcesadorCGI::~ProcesadorCGI() {}

HTTP_Response* ProcesadorCGI::procesarCGI(HTTP_Request* request, 
		string rutaCGI, const string& dirAbsolutaDelRecurso, 
		string dirArchivosDeSalida) {
	char* dirAct = get_current_dir_name();		
	HTTP_Response* respuesta = NULL;
	int cod_retorno = chdir(CGI_BIN);
	ifstream arch(rutaCGI.c_str());
	
	if (arch.fail()) {
		respuesta = new HTTP_Response();
		respuesta->setCodigoRetorno(501);
		respuesta->setProtocolo(1, 0);
		cod_retorno = chdir("../");

		string cadenaArchivo = CargardorDeArchivos::levantarArchivo(config.getError(501));
		respuesta->setContenido(cadenaArchivo);	

		cod_retorno = chdir(dirAct);
		free(dirAct);
		ManejadorLogs::getInstance(config.getConfiguracionLogs())->
				getLogError()->logError("Se intento ejecutar el comando " +
				rutaCGI + " y no existe");
	}
	else {
		arch.close();
		cod_retorno = chdir(dirAct);
		free(dirAct);
		string nombreEntradaTemp(NOMBRE_ENTRADA);
		string nombreSalidaTemp(NOMBRE_SALIDA);
		string escribirEnLaTerminal("");
		string rutaCompletaArchEntradaTemp(dirArchivosDeSalida);
		string rutaCompletaArchSalidaTemp(dirArchivosDeSalida);
		
		rutaCompletaArchEntradaTemp.append(nombreEntradaTemp);
		rutaCompletaArchSalidaTemp.append(nombreSalidaTemp);
		
		prepararComandoDeTerminal(rutaCGI, dirAbsolutaDelRecurso, escribirEnLaTerminal, 
				rutaCompletaArchEntradaTemp, rutaCompletaArchSalidaTemp, dirArchivosDeSalida);
		crearArchivoTemporalParaSTDIN(rutaCompletaArchEntradaTemp, request->getContenido());
	
		//  me posiciono en el directorio cgi-bin
		cod_retorno = chdir(CGI_BIN);	
		setVariableContentLenght(request->getContentLength());
		cod_retorno = system(escribirEnLaTerminal.c_str());

		cod_retorno = chdir("../");

		ManejadorLogs::getInstance(config.getConfiguracionLogs())->
				getLogAcceso()->logInfo("Se ejecuto y proceso " +
				escribirEnLaTerminal + " con exito");
		respuesta = setResponse(rutaCompletaArchSalidaTemp.c_str());
		
		removerArchivosYDirectoriosTemporales(rutaCompletaArchEntradaTemp, rutaCompletaArchSalidaTemp, dirArchivosDeSalida);
	}
	
	
	
	return respuesta;
}

void ProcesadorCGI::setVariableContentLenght(int valorContentLength) {
	string contLengthStr; 
	stringstream ss;
	ss << valorContentLength;
	ss >> contLengthStr;
    setenv("CONTENT_LENGTH", contLengthStr.c_str(), 1);
	int content_length = atoi(getenv("CONTENT_LENGTH"));
}

HTTP_Response* ProcesadorCGI::setResponse(const char* rutaCompletaArchSalida) {
	HTTP_Response* respuesta = new HTTP_Response();
	string cadenaArchivo = CargardorDeArchivos::levantarArchivo(rutaCompletaArchSalida);

	respuesta->setProtocolo(1,0);
	respuesta->setTipoContenido("text/html");
	respuesta->setContenido(cadenaArchivo);
	
	return respuesta;
}	
void ProcesadorCGI::removerArchivosYDirectoriosTemporales(const string rutaArchEntrada, const string rutaArchSalida, 
		const string directorioCGI) {
	remove(rutaArchEntrada.c_str());
	remove(rutaArchSalida.c_str());
	rmdir(directorioCGI.c_str());
}	

void ProcesadorCGI::crearArchivoTemporalParaSTDIN(const string& rutaCompletaArchEntradaTemp, const string& contenidoDeRequest) {
	std::ofstream temp(rutaCompletaArchEntradaTemp.c_str());
	temp.write(contenidoDeRequest.c_str(), contenidoDeRequest.length());
	temp.close();
}

void ProcesadorCGI::prepararComandoDeTerminal(const string rutaCGI, const string& uri, string& comando, const string& nombreEntradaTemp, 
		const string& nombreSalidaTemp, const string& dirArchivosGeneradosPorCGI) {
	
	comando.append("./");
	comando.append(rutaCGI);
	comando.append(" ");
	comando.append(dirArchivosGeneradosPorCGI);
	comando.append(" ");
	comando.append(uri);
	comando.append(" < ");
	comando.append(nombreEntradaTemp);
	comando.append(" > ");
	comando.append(nombreSalidaTemp);
}

HTTP_Response* ProcesadorCGI::procesar(HTTP_Request* pedido) {
	std::string dirAbsolutaDelRecurso(config.getConfiguracionBasica().getRaiz());
	
	dirAbsolutaDelRecurso.append(pedido->getUri());
	return procesarCGI(pedido, rutaCGI , dirAbsolutaDelRecurso , this->dir);
}