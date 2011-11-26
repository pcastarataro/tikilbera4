#include "ProcesadorCGI.h"
#include "CargardorDeArchivos.h"
#include "ManejadorLogs.h"
#include <sstream>
#include <fstream>

#define NOMBRE_ENTRADA "post.tmp"
#define NOMBRE_SALIDA "salida.tmp"

using std::stringstream;
using std::ifstream;

ProcesadorCGI::ProcesadorCGI(const Configuracion& c, const std::string& ruta , const std::string& rutaCGI): config(c) {
	this->dir = ruta;
	this->rutaCGI = rutaCGI;
}

ProcesadorCGI::~ProcesadorCGI() {
}

/* Parametros: 
	 * - post o string que recibe el CGI en STDIN.
	 * - rutaCGI: ruta relativa (del cgi) a la carpeta cgi-bin.
	 * - params: La lista de parametros siempre tendra al menos 1 parametro,
	 * el cual es la ruta completa de la carpeta temporal del cgi, en el cual
	 * podra almacenar sus archivos temporales (si los generase).	
	 * El resto de los parametros son opcionales, y son usados gralmente por scripts php.
	 * Retorno: la respuesta generada por el CGI.
	 *  */
HTTP_Response* ProcesadorCGI::procesarCGI(HTTP_Request* request, string rutaCGI, const string& pathAbsoluto, string dirArchivosDeSalida) {
	char* dirAct = get_current_dir_name();		
	HTTP_Response* respuesta = NULL;
	chdir("cgi-bin");	// TODO: obtener de configuracion.xml!!!!

	ifstream arch(rutaCGI.c_str());
	
	if (arch.fail()) {
		respuesta = new HTTP_Response();
		respuesta->setCodigoRetorno(501);
		respuesta->setProtocolo(1, 0);
		//chdir("/home/pablo/taller1/servidor");	// TODO: obtener de configuracion.xml!!!!
		chdir("../");	// TODO: obtener de configuracion.xml!!!!

		string cadenaArchivo = CargardorDeArchivos::levantarArchivo(config.getError(501));
		respuesta->setContenido(cadenaArchivo);	

		chdir(dirAct);
		free(dirAct);
		cout << rutaCGI << " no existe!!!" << endl;
		ManejadorLogs::getInstance(config.getConfiguracionLogs())->
				getLogError()->logError("Se intento ejecutar el comando " +
				rutaCGI + " y no existe");
	}
	else {
		arch.close();
		chdir(dirAct);
		std::cout << "//////////////////////////////////////////////////////////////////////" << std::endl;
		std::cout << "///////////////COMIENZO DEL CGI///////////////////" << std::endl;
			
		string nombreEntradaTemp(NOMBRE_ENTRADA);
		string nombreSalidaTemp(NOMBRE_SALIDA);
		string escribirEnLaTerminal("");
		string rutaCompletaArchEntradaTemp(dirArchivosDeSalida);
		string rutaCompletaArchSalidaTemp(dirArchivosDeSalida);
		
		rutaCompletaArchEntradaTemp.append(nombreEntradaTemp);
		rutaCompletaArchSalidaTemp.append(nombreSalidaTemp);
		
		prepararComandoDeTerminal(rutaCGI, pathAbsoluto, escribirEnLaTerminal, 
				rutaCompletaArchEntradaTemp, rutaCompletaArchSalidaTemp, dirArchivosDeSalida);
		crearArchivoTemporalParaSTDIN(rutaCompletaArchEntradaTemp, request->getContenido());
	
		//system("./pr < temp.tmp > salida.tmp");
		std::cout << "comando a ejecutar: " << escribirEnLaTerminal << std::endl;
	
		//  me posiciono en el directorio cgi-bin
		//cout << "get_current_dir_name : " << get_current_dir_name() << endl;
		chdir("cgi-bin");	// obtener de configuracion.xml!!!!
	
		// TODO: BORRAR get_current_dir_name////////
		free(dirAct);
		dirAct = get_current_dir_name();
		cout << "get_current_dir_name (cambiado a cgi-bin): " << dirAct << endl;
		free(dirAct);
		/////////////////////////////////////////////////////////////////
		
		
		setVariableContentLenght(request->getContentLength());
		system(escribirEnLaTerminal.c_str());
		//chdir("/home/pablo/taller1/servidor");
		chdir("../");

		ManejadorLogs::getInstance(config.getConfiguracionLogs())->
				getLogAcceso()->logInfo("Se ejecuto y proceso " +
				escribirEnLaTerminal + " con exito");
		respuesta = setResponse(rutaCompletaArchSalidaTemp.c_str());
		
		removerArchivosYDirectoriosTemporales(rutaCompletaArchEntradaTemp, rutaCompletaArchSalidaTemp, dirArchivosDeSalida);

		std::cout << "///////////////FIN DEL CGI///////////////////" << std::endl;
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
	cout << "content_length: " << content_length << endl;
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
	
	char* dirAct = get_current_dir_name();
	cout << "get_current_dir_name : " << dirAct << endl;
	free(dirAct);
	cout << "borrando " << rutaArchEntrada << endl;
	cout << "borrando " << rutaArchSalida << endl;
	cout << "borrando " << directorioCGI << endl;
	
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
	//std::string dirAbsolutaDelRecurso("/home/pablo/taller1/servidor"); // TODO sacar dir raiz desde config.xml
	std::string dirAbsolutaDelRecurso(config.getConfiguracionBasica().getRaiz()); // TODO sacar dir raiz desde config.xml
	//dirAbsolutaDelRecurso.append("/tp");
	dirAbsolutaDelRecurso.append(pedido->getUri());
	return procesarCGI(pedido, rutaCGI , dirAbsolutaDelRecurso , this->dir);
}
