#include "ParserEntradaEstandar.h"
#include "ConstantesParser.h"
#include <string.h>
#include <stdlib.h>

ParserEntradaEstandar::ParserEntradaEstandar(int newContent_length , 
char* ruta) {
	finDePost = false;
	esFinDeUnoDeLosArchivos = false;
	archivoActualValido = false;
	cantBytesLeidos = 0;
	rutaDirectorioArchTemporales = ruta;
	content_length = newContent_length;
	leerBinario = false;
	archivoSTDIN = NULL;
}

string ParserEntradaEstandar::buscarCadena(char* cadena, char* cadenaAHallar) {
	string cadenaBuscada(cadenaAHallar);
	string lineaStr(cadena);
	size_t pos = lineaStr.find(cadenaBuscada, 0) + cadenaBuscada.length();
	return lineaStr.substr(pos, lineaStr.length());
}

void ParserEntradaEstandar::leerYEscribirLinea(char* entrada) {
	if (leerBinario) {
		int cantBytesRestantes = content_length - cantBytesLeidos;
		int cantBytesALeer = 0;
		if (cantBytesRestantes > LONG_ENTRADA_ESTANDAR)
			cantBytesALeer = LONG_ENTRADA_ESTANDAR;
		else 
			cantBytesALeer = cantBytesRestantes;
		archivoSTDIN->read(entrada, cantBytesALeer);
		cantBytesLeidos += archivoSTDIN->gcount();
		archSalida.write(entrada, archivoSTDIN->gcount());
	} else {
		fgets(entrada, LONG_ENTRADA_ESTANDAR, stdin);
		cantBytesLeidos += strlen(entrada);
	}
}

void ParserEntradaEstandar::levantarDatosDeCabecera() {
	char entrada[LONG_ENTRADA_ESTANDAR];
	leerYEscribirLinea(entrada);
	string aux(entrada);
	string boundary = aux.substr(0, aux.length());
	string boundaryFinPost = boundary;
	boundaryFinPost.append("--");
	longMarcaDeFinDePost = boundaryFinPost.length() + 2;
	leerYEscribirLinea(entrada);
	nombreArchivoComprimido = buscarCadena(entrada, FILENAME);
	eliminarComillasYSaltoDeLinea();
	crearNuevoArchivoComprimido();
	leerYEscribirLinea(entrada);
	leerYEscribirLinea(entrada);
	leerBinario = true;
}

	/*  si nombreArchivoSalida.length() == 0, se trata de un archivo invalido,
	 *  sin nombre y sin contenido.
	 *  Ejemplo:
	 * -----------------------------161598199615330536461421384039
	 * Content-Disposition: form-data; name="file"; filename=""
	 * Content-Type: application/octet-stream
	 *
	 *
	 * -----------------------------161598199615330536461421384039*/
void ParserEntradaEstandar::eliminarComillasYSaltoDeLinea() {
	string comillaFinal("\"");
	int pos = nombreArchivoComprimido.find(comillaFinal , 1);
	nombreArchivoComprimido = nombreArchivoComprimido.substr(1 , pos - 1);
	if (nombreArchivoComprimido.length() != 0) {
		archivoActualValido = true;
		nombreCarpetaDescomprimida = nombreArchivoComprimido.substr(0 , 
				nombreArchivoComprimido.length() - 4);
	} else 
archivoActualValido = false;
}

void ParserEntradaEstandar::crearNuevoArchivoComprimido() {
	if (archivoActualValido) {
		string rutaCompletaArchivo(rutaDirectorioArchTemporales);
		rutaCompletaArchivo.append(nombreArchivoComprimido);
		archSalida.open(rutaCompletaArchivo.c_str(), ios::out|ios::binary);
	}
}

	/*	Si se supera la cant. de bytes leidos permitidos,
	 *  el metodo retorna una cantidad de archivos invalida.*/
int ParserEntradaEstandar::descomprimir() {
	int retorno = 0;
	levantarDatosDeCabecera();
	archivoSTDIN = &cin;
	content_length -= longMarcaDeFinDePost;
	if (archivoActualValido) {
		while(quedanBytesPorLeer()) {
			char entrada[LONG_ENTRADA_ESTANDAR];
			leerYEscribirLinea(entrada);
		}
		archSalida.close();
		if (cantBytesLeidos == content_length) {
			setArchivoPrincipal();
			string comando("unzip -d ");
			comando.append(nombreCarpetaDescomprimida);
			comando.append(" ");
			comando.append(nombreArchivoComprimido);
			system(comando.c_str());
			retorno = OK;
		} else 
			retorno = CONTENT_LENGTH_EXCEDIDO;
	} else 
		retorno = NOMBRE_ARCHIVO_INVALIDO;
	return retorno;
}

	/*	se puede buscar int main(...) en todos los archivos, y setear como principal
	 *  aquel en donde sea hallado.
	 *  Otra opcion es imponer la restriccion de que exista si o si
	 *  un archivo main.cpp en la raiz del comprimido (como se hace ahora)*/
bool ParserEntradaEstandar::setArchivoPrincipal() {
	bool mainHallado = true;
	nombreArchivoPrincipal = "main.cpp";
	return mainHallado;
}
bool ParserEntradaEstandar::quedanBytesPorLeer() {
	return cantBytesLeidos < content_length;
}

