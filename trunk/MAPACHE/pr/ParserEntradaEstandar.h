#ifndef PARSERENTRADAESTANDAR_H_
#define PARSERENTRADAESTANDAR_H_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
using std::string;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;
using std::list;

class ParserEntradaEstandar {
private:
	ofstream archSalida;
	int cantBytesLeidos;
	int content_length;
	bool primerArchivo;
	bool archivoActualValido;
	bool finDePost, esFinDeUnoDeLosArchivos;
	string boundary, boundaryFinPost;
	string nombreArchivoSalida;
	string nombreArchivoPrincipal;
	char* rutaDirectorioArchTemporales;
	list<string> listaDeNombresDeArchivos;
	list<string>::iterator it;
	
	/**
	 * Metodo que ayuda a identificar el fin de los datos correspondientes
	 * a uno de los archivos contenidos en el POST, que el programa
	 * recibe por STDIN.
	 * @param lineaStr linea leida de STDIN.
	 * @return true si la linea coincide con la marca de fin archivo actual.
	 */
	bool boundaryCoincide(string* lineaStr);
	/**
	 * Metodo que ayuda a identificar el fin del POST, que el programa
	 * recibe por STDIN.
	 * @param lineaStr linea leida de STDIN.
	 * @return true si la linea coincide con la marca de fin de POST.
	 */
	bool marcaDeFinDeArchivo_Post(string* linea);
	/**
	 * Escribe una linea en el ultimo archivo creado.
	 * @param lineaStr Cadena de caracteres.
	 * @return void
	 */
	void escribirLineaAArchivo(string* lineaStr);
	/**
	 * Lee una linea de STDIN.
	 * @param linea cadena en donde se guardan los datos leidos.
	 * @return void
	 */
	void leerLinea(char* linea);
	/**
	 * Chequea si cadena contiene datos referentes a fin de archivo actual o de fin de POST,
	 * y realiza las acciones pertinentes.
	 * @param cadena linea leida de STDIN.
	 * @return void
	 */
	void analizarLinea(char* cadena);
	/**
	 * Si es la 1era vez que se entra a esta funcion, se parsea la marca de fin de archivo actual.
	 * Siempre parsea el nombre del archivo actual, y crea un archivo con ese nombre.
	 * @return void
	 */	
	void levantarDatosDeCabecera();
	/**
	 * Verifica que no se haya superado la cant. maxima de bytes leidos,
	 * que viene dada por content_length.
	 * @return true Si quedan bytes por leer.
	 */
	bool quedanBytesPorLeer();
	/**
	 * Crea un archivo con el nombre contenido en nombreArchivoSalida.
	 * @return void
	 */
	void crearNuevoArchivo();
	/**
	 * Busca una cadena dentro de otra.
	 * @param cadena Cadena de caracteres en la que se hara la busqueda.
	 * @param cadenaAHallar Cadena a hallar.
	 * @return string Substring desde donde comienza la coincidencia con cadenaAHallar
	 * hasta el fin de cadena.
	 */
	string buscarCadena(char* cadena, char* cadenaAHallar);
	/**
	 * Elimina las comillas y el salto de linea de nombreArchivoSalida.
	 * @return void
	 */
	void eliminarComillasYSaltoDeLinea();
public:
	/**
	 * Constructor
	 */
	ParserEntradaEstandar(int content_length, char* ruta);
	/**
	 * Retorna el valor de content_length.
	 * @return int
	 */
	int getContent_length() {return content_length;}
	/**
	 * Retorna la cantidad de bytes leidos por el programa.
	 * @return int
	 */
	int getCantBytesLeidos() {return cantBytesLeidos;}
	/**
	 * Parsea el POST, que viene por STDIN, y extrae la info de los archivos que contiene,
	 * colocando dicha info en archivos temporales.
	 * @return int Cantidad de archivos creados.
	 */
	int crearArchivosAPartirDeEntradaEstandar();
	/**
	 * Apunta el iterador it al inicio de la lista listaDeNombresDeArchivos.
	 * @return void
	 */	
	void setIterador() {it = listaDeNombresDeArchivos.begin();}
	/**
	 * Retorna el nombre del archivo principal.
	 * @return string
	 */	
	string getNombreArchivoPpal() {return nombreArchivoPrincipal;}
	/**
	 * Retorna el siguiente nombre de archivo dentro de la lista.
	 * @return string
	 */	
	string getSiguienteNombreArch() {
		string str = *it;
		it++;
		return str;
	}
	/**
	 * Destructor
	 */
	~ParserEntradaEstandar() {}
};
#endif /* PARSERENTRADAESTANDAR_H_ */
