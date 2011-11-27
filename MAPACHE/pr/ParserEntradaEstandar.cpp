#include "ParserEntradaEstandar.h"
#include <string.h>
#include <stdlib.h>

#define LONG_ENTRADA_ESTANDAR 160
#define BOUNDARY "boundary="
#define FILENAME "filename="
#define LARGO_MAX_BOUNDARY 30

ParserEntradaEstandar::ParserEntradaEstandar(
		int newContent_length, char* ruta) {
	primerArchivo = true;
	finDePost = false;
	esFinDeUnoDeLosArchivos = false;
	archivoActualValido = false;
	cantBytesLeidos = 0;
	rutaDirectorioArchTemporales = ruta;
	nombreArchivoPrincipal = "";
	content_length = newContent_length;
}

string ParserEntradaEstandar::buscarCadena(char* cadena, char* cadenaAHallar) {
	string cadenaBuscada(cadenaAHallar);
	string lineaStr(cadena);
	size_t pos = lineaStr.find(cadenaBuscada, 0) + cadenaBuscada.length();
	return lineaStr.substr(pos, lineaStr.length());
}

bool ParserEntradaEstandar::marcaDeFinDeArchivo_Post(string* linea) {
	bool retorno = true;

	if (linea->find(boundaryFinPost) != linea->npos) {
		retorno = true;
	} else
		retorno = false;
	return retorno;
}

void ParserEntradaEstandar::escribirLineaAArchivo(string* lineaStr) {
	if (quedanBytesPorLeer() && archivoActualValido) {
		archSalida.write(lineaStr->c_str(), lineaStr->length());
	}
}

void ParserEntradaEstandar::leerLinea(char* entrada) {
	fgets(entrada, LONG_ENTRADA_ESTANDAR, stdin);
	cantBytesLeidos += strlen(entrada);
}

void ParserEntradaEstandar::analizarLinea(char* cadena) {
	string lineaStr;

	lineaStr.append(cadena, strlen(cadena));

	if (boundaryCoincide(&lineaStr))
		if (marcaDeFinDeArchivo_Post(&lineaStr)) {
			finDePost = true;
			esFinDeUnoDeLosArchivos = true;
		} else
			esFinDeUnoDeLosArchivos = true;
	else {
		escribirLineaAArchivo(&lineaStr);
	}
}

bool ParserEntradaEstandar::boundaryCoincide(string* lineaStr) {
	bool retorno = true;

	if (lineaStr->length() >= boundary.length()) {
		string aux = lineaStr->substr(0, boundary.length());
		if (aux.compare(boundary.c_str()) != 0) {
			retorno = false;
		}
	} else
		retorno = false;

	return retorno;
}

void ParserEntradaEstandar::levantarDatosDeCabecera() {
	char entrada[LONG_ENTRADA_ESTANDAR];

	if (primerArchivo) {
		leerLinea(entrada);
		string aux(entrada);
		boundary = aux.substr(0, aux.length() - 2);
		boundaryFinPost = boundary;
		boundaryFinPost.append("--");
		primerArchivo = false;
	}
	leerLinea(entrada);
	nombreArchivoSalida = buscarCadena(entrada, FILENAME);
	eliminarComillasYSaltoDeLinea();
	crearNuevoArchivo();
	leerLinea(entrada);
	leerLinea(entrada);
}

/**
 * 	si nombreArchivoSalida.length() == 0, se trata de un archivo invalido,
 *  sin nombre y sin contenido.
 *  Ejemplo:
 * -----------------------------161598199615330536461421384039
 * Content-Disposition: form-data; name="file"; filename=""
 * Content-Type: application/octet-stream
 *
 *
 * -----------------------------161598199615330536461421384039
 */
void ParserEntradaEstandar::eliminarComillasYSaltoDeLinea() {
	string comillaFinal("\"");
	int pos = nombreArchivoSalida.find(comillaFinal, 1);

	nombreArchivoSalida = nombreArchivoSalida.substr(1, pos - 1);
	if (nombreArchivoSalida.length() != 0)
		archivoActualValido = true;
	else
		archivoActualValido = false;
}

/**
 * 	Si el nombre del archivo es valido (nombreArchivoSalida.length() != 0),
 *  se crea el archivo.
 *  Si, ademas, nombreArchivoPrincipal.length() es igual a 0
 *  , significaria que su valor no ha sido cambiado desde su inicializacion
 *  en el constructor, y por lo tanto, se asume que ese archivo es el principal
 *  para la precompilacion.
 *  Resumiendo, el archivo principal es el primer archivo valido que se encuentra
 *  en el post.
 */
void ParserEntradaEstandar::crearNuevoArchivo() {
	if (archivoActualValido) {
		string rutaCompletaArchivo(rutaDirectorioArchTemporales);
		rutaCompletaArchivo.append(nombreArchivoSalida);
		archSalida.open(rutaCompletaArchivo.c_str(), ios::out);
		listaDeNombresDeArchivos.push_front(nombreArchivoSalida);
		if (nombreArchivoPrincipal.length() == 0)
			nombreArchivoPrincipal = nombreArchivoSalida;
	}
}

/**
 * 	Si se supera la cant. de bytes leidos permitidos,
 *  el metodo retorna una cantidad de archivos invalida.
 */
int ParserEntradaEstandar::crearArchivosAPartirDeEntradaEstandar() {
	while (quedanBytesPorLeer() && !finDePost) {
		esFinDeUnoDeLosArchivos = false;
		levantarDatosDeCabecera();
		while (quedanBytesPorLeer() && !esFinDeUnoDeLosArchivos) {
			string lineaStr;
			char entrada[LONG_ENTRADA_ESTANDAR];
			leerLinea(entrada);

			analizarLinea(entrada);
		}
		if (archivoActualValido) {
			archSalida.close();
		}
	}

	int retorno = 0;
	if (!finDePost)
		retorno = -1;
	else
		retorno = listaDeNombresDeArchivos.size();
	return retorno;
}

bool ParserEntradaEstandar::quedanBytesPorLeer() {
	return cantBytesLeidos <= content_length;
}
