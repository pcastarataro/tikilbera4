#ifndef PARSERENTRADAESTANDAR_H_
#define PARSERENTRADAESTANDAR_H_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <istream>

using std::istream;
using std::cin;
using std::string;
using std::stringstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;
using std::list;

class ParserEntradaEstandar {
private:
	istream* archivoSTDIN;
	ofstream archSalida;
	int cantBytesLeidos;
	int content_length;
	int longMarcaDeFinDePost;
	bool archivoActualValido;
	bool finDePost, esFinDeUnoDeLosArchivos;
	bool leerBinario;
	string nombreArchivoComprimido, nombreCarpetaDescomprimida;
	string nombreArchivoPrincipal;
	char* rutaDirectorioArchTemporales;
	
	/**
	 * Lee una cantidad de bytes determinado por LONG_ENTRADA_ESTANDAR.
	 * Y si ya se parseo la cabecera, lo escribe en el archivo zip.
	 * @param linea Cadena de caracteres leida.
	 * @return void
	 */
	void leerYEscribirLinea(char* linea);
	/**
	 * Se parsea la longitud de la marca de fin de POST, 
	 * asi como el nombre del archivo zip, y crea un archivo con ese nombre.
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
	 * Crea el archivo comprimido, con el nombre que se parseò de la cabecera del POST.
	 * @return void
	 */
	void crearNuevoArchivoComprimido();
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
	/**
	 * Establece el archivo principal de la precompilacion.
	 * @return bool
	 */	
	bool setArchivoPrincipal();
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
	 * Parsea la cabecera del POST.
	 * Crea el archivo comprimido y escribe en èl en sucesivas iteraciones.
	 * Al finalizar, lo descomprime en DirectorioActual/nombreArchivoComprimido/
	 * @return int Codigo de operacion (OK, NOMBRE_ARCHIVO_INVALIDO o CONTENT_LENGTH_EXCEDIDO)
	 */
	int descomprimir();
	/**
	 * Retorna el nombre del archivo principal.
	 * @return string
	 */	
	string getNombreArchivoPpal() {return nombreArchivoPrincipal;}
	/**
	 * Retorna el nombre del archivo comprimido.
	 * @return string
	 */	
	string getNombreArchivoComprimido() {return nombreArchivoComprimido;}
	/**
	 * Retorna el nombre de la carpeta con los archivos descomprimidos.
	 * @return string
	 */	
	string getNombreCarpetaDescomprimida() {return nombreCarpetaDescomprimida;}
	/**
	 * Destructor
	 */
	~ParserEntradaEstandar() {}
};
#endif /* PARSERENTRADAESTANDAR_H_ */
