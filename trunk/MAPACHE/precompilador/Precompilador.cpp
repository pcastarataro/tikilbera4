#include "Precompilador.h"
using std::string;

char* Precompilador::buscarReemplazos(char* linea,	ContenedorDeDefines& lista) {
	string lineaAuxStr(linea);

	//  un ciclo por define
	for (int k = 0; k <= lista.getIndexActual(); k++) {
		char* defineActual = lista.getDefine(k);
		char* valorDefineActual = lista.getValorDefine(k);
		int longNombreDelDefine = strlen(defineActual);
		int longValorDelDefine = strlen(valorDefineActual);
		string defineActualStr(defineActual);
		size_t posDentroDeLaLinea = 0;
		size_t posSiguienteMatch = lineaAuxStr.find(defineActual, posDentroDeLaLinea);

		//  busco coincidencias
		while (posSiguienteMatch != lineaAuxStr.npos) {
			char caracterAnteriorAlMatch;
			char caracterPosteriorAlMatch = lineaAuxStr.at(posSiguienteMatch + longNombreDelDefine);

			if (posSiguienteMatch == 0) {
				caracterAnteriorAlMatch = '/';
				//  match en 1era letra de linea->lo seteo a un separador valido
			}
			else caracterAnteriorAlMatch = lineaAuxStr.at(posSiguienteMatch - 1);

			if (sepValidos.esSeparadorValido(caracterAnteriorAlMatch)
					&& sepValidos.esSeparadorValido(caracterPosteriorAlMatch)) {
				lineaAuxStr.replace(posSiguienteMatch, longNombreDelDefine, valorDefineActual);
				posDentroDeLaLinea = posSiguienteMatch + longValorDelDefine;
			}
			else posDentroDeLaLinea++;
			
			posSiguienteMatch = lineaAuxStr.find(defineActual, posDentroDeLaLinea);
		}  //  fin ciclo while
	}  //  fin ciclo for
	strcpy(linea, lineaAuxStr.c_str());

	return linea;
}

char* Precompilador::quitarComentarios(char* linea, FlagsDePrograma& flags) {
	char lineaAux[LONGITUD_LINEA_LEIDA] = {0};

	flags.comentarioAbiertoEnLineaActual = false;

	if (!flags.comentarioAbierto) {
		buscarAperturaDeComentarioOBarraDoble(lineaAux, linea, flags);
	}
	/*
	 * no seria adecuado poner un else if(flags.comentarioAbierto == true)
	 * porque flags.comentarioAbierto puede cambiar su valor
	 * dentro de buscarAperturaDeComentarioOBarraDoble,
	 * ya que, justamente, su tarea es buscar apertura de comentarios.
	 */
	if (flags.comentarioAbierto) {
		buscarCierreDeComentario(lineaAux, linea, flags);
	}

	strcpy(linea, lineaAux);
	return linea;
}

void Precompilador::buscarAperturaDeComentarioOBarraDoble(char* lineaAux,
		char* linea, FlagsDePrograma& flags) {
	char* ptrIteradorLinea = linea;
	char* siguienteMatch = strstr(ptrIteradorLinea, BARRASDOBLES);

	if (siguienteMatch != NULL) {
		strncpy(lineaAux, linea, siguienteMatch - linea);
		lineaAux[siguienteMatch - linea] = BARRA_N;
		flags.todaviaTieneComentarios = false;
	}
	else {
		siguienteMatch = strstr(ptrIteradorLinea, APERTURA_COMENTARIO);

		if (siguienteMatch != NULL) {
			flags.comentarioAbierto = true;
			strncpy(lineaAux, linea, siguienteMatch - linea);
			lineaAux[siguienteMatch - linea] = (int) NULL;
			ptrIteradorLinea = siguienteMatch;
			flags.comentarioAbiertoEnLineaActual = true;
		}
		else {
			strcpy(lineaAux, linea);
			flags.todaviaTieneComentarios = false;
		}
	}
}

void Precompilador::buscarCierreDeComentario(char* lineaAux, char* linea,
		FlagsDePrograma& flags) {
	char* ptrIteradorLinea = linea;
	char* siguienteMatch = strstr(ptrIteradorLinea, CIERRE_COMENTARIO);

	if (siguienteMatch != NULL) {
		flags.comentarioAbierto = false;

		/*  Si hubo una apertura de comentario en la linea actual,
		 *  lo que no estaba comentado esta en lineaAux.
		 *  siguienteMatch+2 apunta al 1er carac no comentado luego del cierre de comentario
		 *  Entonces, concateno ambas partes*/
		if (flags.comentarioAbiertoEnLineaActual) {
			strcat(lineaAux, siguienteMatch + 2);
		} else {
			/* El flujo del programa llego a este punto porque
			 * se hallo un cierre de comentario, pero la apertura
			 * se realizo en una linea anterior.
			 * No puedo concatenar, porque lineaAux tiene basura
			 * */
			strcpy(lineaAux, siguienteMatch + 2);
		}
	} else {
		flags.todaviaTieneComentarios = false;
	}
}
