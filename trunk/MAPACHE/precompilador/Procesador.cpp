#include "Procesador.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

void Procesador::procesarIfdefOIfndef(char* linea, int codInstr) {
	char* ptrAParametro = NULL;

	/* 01234567
	 * #ifdef PARAMETRO
	 * 012345678
	 * #ifndef PARAMETRO
	 *
	 * Cuando se trata de ifdef, para llegar al parametro,
	 * tengo que avanzar 7 posiciones dentro de la cadena "linea".
	 * Cuando se trata de ifndef, avanzo 8 posiciones.
	 * */
	if (codInstr == COD_INSTR_IFDEF) ptrAParametro = linea + 7;
	else ptrAParametro = linea + 8;

	/*  cuidar que el tamanio de vectorDeTopes sea igual
	 *  al ultimo parametro de getLargoCadena
	 */

	char vectorDeTopes[3] = {BLANCO, BARRA_N, BARRA_R};
	int largoDelDefine = util.getLargoCadena(ptrAParametro, vectorDeTopes, 3);
	char comp;

	if (largoDelDefine == 0)
		flags.statusDelPrograma = ERROR_PROGRAMA;
	else {
		bool defineEncontrado = lista.existeEsteDefine(ptrAParametro, largoDelDefine);

		if (defineEncontrado) {
			if (codInstr == COD_INSTR_IFDEF) {
				comp = COMPILAR;  //  esta definido y es ifdef
			}
			else comp = NO_COMPILAR;  //  esta definido y es ifndef
		}
		else if (codInstr == COD_INSTR_IFDEF) {
			comp = NO_COMPILAR;  //  no esta definido y es ifdef
			}
			else comp = COMPILAR;  //  no esta definido y es ifndef

	ifDefAnidados.anidar(comp, flags);
	}
}

void Procesador::procesarElse(char* linea) {
	ifDefAnidados.invertirUltimoValorAnidado();
}

void Procesador::procesarEndif(char* linea) {ifDefAnidados.desanidar();}
	/*  levanta los parametros de la instruccion define
	 *  tanto en su forma de 2 parametros, como en su forma de unico parametro*/
void Procesador::procesarDefine(char* linea) {
	char* ptrA1erParametro = linea + 8;
	lista.incrementarIndex();
	int indiceActual = lista.getIndexActual();

	/* 012345678
	 * #define PARAMETRO1 PARAMETRO2
	 *
	 * Tengo que avanzar 8 posiciones dentro de la cadena "linea"
	 * para poder apuntar al 1er parametro.
	 * */

	if (!util.esNumero(ptrA1erParametro)) {
		char vectorDeTopes[3] = {BLANCO, BARRA_N, BARRA_R};
		int largoDelDefine = util.getLargoCadena(ptrA1erParametro, vectorDeTopes, 3);
		char* separador = (char*)(ptrA1erParametro + largoDelDefine);
		char* ptrA2doParametro = NULL;
		int largoValorDefine;

		/* Caso de 2 parametros:
		 *
		 * 012345678901234567
		 * #define AUTOR "yo"
		 * #define AUTOS 27
		 *
		 * Tengo que saber si el valor del define esta entre comillas/comillas simples.
		 * En el 1er caso, debo buscar el valor del define en la pos 15.
		 * En el 2do caso, en la pos 14.
		 * Saber esto tambien me da la posibilidad de saber que caracter
		 * buscar para terminar el parseo (lo que llamo "charDelimitador")
		 * */
		if ((*separador == BARRA_N) || (*separador == BARRA_R)) {
			char* nulo = (char*)NULO;
			ptrA2doParametro = nulo;
			largoValorDefine = strlen(nulo);
			//  seteo el segundo parametro a un valor nulo
		}
		else {  //  hay 2 parametros
			ptrA2doParametro = (char*)(separador + 1);
			char vectorDeTopes2[1] = {BARRA_N};
			largoValorDefine = util.getLargoCadena(ptrA2doParametro, vectorDeTopes2, 1);
		}

		if (largoDelDefine > LONGITUD_VALOR_DEFINE ||
				largoValorDefine > LONGITUD_VALOR_DEFINE)
					flags.statusDelPrograma = ERROR_PROGRAMA;
		else
			lista.setDefineYSuValor(ptrA1erParametro, largoDelDefine,
					ptrA2doParametro, largoValorDefine, indiceActual);
	}
	else flags.statusDelPrograma = ERROR_PROGRAMA;
}

	/* establece, segun el codInstr (que identifica de que instr se trata),
	 * el separador correcto para la instruccion.
	 * Defino "separador" como el caracter inmediatamente posterior
	 * a la instruccion.
	 */
bool Procesador::esSeparadorValidoParaLaInstruccion(char* instr, char sep) {
	char sepValido1 = 'Z';
	char sepValido2 = 'Z';
	bool sepExtra = false;
	bool retorno = true;

	if (strcmp(instr, DEFINE) == 0 ||
			strcmp(instr, INCLUDE) == 0  ||
				strcmp(instr, IFDEF) == 0  ||
					strcmp(instr, IFNDEF) == 0)
						sepValido1 = BLANCO;

	else if (strcmp(instr, ELSE) == 0 ||
				strcmp(instr, ENDIF) == 0) {
					sepValido1 = BLANCO;
					sepValido2 = BARRA_N;
					sepExtra = true;
	}

	if (!sepExtra && sepValido1 == sep) retorno = true;
	else if (sepExtra && (sepValido1 == sep || sepValido2 == sep)) retorno = true;
	else retorno = false;
	
	return retorno;
}

	/* se le llama "instruccion" a la cadena inmediatamente
	 * posterior al caracter #
	 * Se verifica que tenga un separador valido.
	 * De no tenerlo, se establece que se ha producido un error de parseo
	 * Se pasan como parametro el posible nombre de la funcion (una cadena)
	 * y un cod que la identifique.
	 * - La cadena sirve para ser comparada contra lo que existe en el parametro linea.
	 * Sobre esta cadena se puede hacer strlen,
	 * por lo que puedo determinar en que lugar de
	 * "linea" deberia encontrarse el separador:
	 * separador = (char*)(linea + strlen(instruccion) + 1).
	 * - El codigo sirve para tener una forma de identificar a que funcion debo invocar
	 * que sea menos costosa que realizar nuevamente una comparacion entre cadenas
	 * (ver procesarInstruccion(.....))
	 * */
bool Procesador::parseInstruccion(char* linea, char* posibleInst, int codInstr) {
	char* instruccion = linea + 1;
	int largoPosibleInstr = strlen(posibleInst);
	char* sep = (char*)(instruccion + largoPosibleInstr);
	bool retorno = false;

	if (strncmp(instruccion, posibleInst, largoPosibleInstr) == 0) {
		if (esSeparadorValidoParaLaInstruccion(posibleInst, *sep)) {
			procesarInstruccion(linea, codInstr);
			retorno = true;
		}
		else flags.statusDelPrograma = ERROR_PROGRAMA;
	}
	return retorno;
}

	/*  no valia la pena volver a comparar cadenas en este caso,
	 *  y por eso se agrego un parametro int para determinar
	 *  de que funcion se trata*/
void Procesador::procesarInstruccion(char* linea, int codInstr) {
	if (codInstr == COD_INSTR_DEFINE) procesarDefine(linea);
	else if	(codInstr == COD_INSTR_INCLUDE) procesarInclude(linea);
	else if	(codInstr == COD_INSTR_IFDEF)
		procesarIfdefOIfndef(linea, COD_INSTR_IFDEF);
	else if	(codInstr == COD_INSTR_IFNDEF)
		procesarIfdefOIfndef(linea, COD_INSTR_IFNDEF);
	else if	(codInstr == COD_INSTR_ELSE)  procesarElse(linea);
	else if	(codInstr == COD_INSTR_ENDIF) procesarEndif(linea);
}

	/*	Si se encuentra un include de libreria estandar, se lo ignora.
	 *  En vez de hacer que el programa termine con un error por no hallar
	 *  el archivo, trato a la linea como si no existiera.*/
void Procesador::procesarInclude(char* linea) {
	char* aux = linea + 9;
	
	if (*aux != MENOR) {
		char separador1 = COMILLAS;
		//char separador2 = '>';
		char nombreArchivo[LONG_MAX_NOMBRE_DE_ARCHIVO];
		char* ptrNombreArchivo = &nombreArchivo[0];
		char* ptrAParametro = linea + 10;
		char vectorDeTopes[1] = {separador1};
		int largoDelNombre = util.getLargoCadena(ptrAParametro, vectorDeTopes, 1);
	
		strncpy(ptrNombreArchivo, ptrAParametro, largoDelNombre);
		ptrNombreArchivo[largoDelNombre] = (int) NULL;
		procesoArchivoEntrada(ptrNombreArchivo);
	}
}

	/*
	 * Se consigue mejor desempe�o ubicando las instrucciones mas comunes
	 * al inicio de los vectores.
	 * */
char* Procesador::procesarDirectivaCompilador(char* linea) {
	int contador = 0;
	bool esLaInstrCorrecta = false;
	char* vecDeInstr[CANT_DE_INTR_DE_COMPILADOR] = {(char*)DEFINE,
			(char*)ELSE, (char*)ENDIF, (char*)IFDEF,
			(char*)IFNDEF, (char*)INCLUDE};

	int vecCod[CANT_DE_INTR_DE_COMPILADOR] = {COD_INSTR_DEFINE,
			COD_INSTR_ELSE, COD_INSTR_ENDIF, COD_INSTR_IFDEF,
			COD_INSTR_IFNDEF, COD_INSTR_INCLUDE};


	while(!esLaInstrCorrecta && contador < CANT_DE_INTR_DE_COMPILADOR) {
		esLaInstrCorrecta = parseInstruccion(linea,	vecDeInstr[contador], vecCod[contador]);
		contador++;
	}
	linea[0] = (int) NULL;  //  para que no imprima nada al final del ciclo
	return linea;
}

/*
* abre el archivo.
* si lo pudo abrir,  continua. Sino,  error.
* lee el archivo.
* mientras que no sea eof y no se haya producido un error.
* proceso la linea.
* se lee otra linea.
* se cierra el archivo.
* */
void Procesador::procesoArchivoEntrada(const char* nombreArchivo) {	
	FILE* ptrFile = fopen(nombreArchivo, "r");
	char lineaLeida[LONGITUD_LINEA_LEIDA];
	char* ptrALineaLeida = lineaLeida;
	
	flags.comentarioAbierto = false;
	
	if (ptrFile != NULL) {
		ptrALineaLeida = fgets(lineaLeida, LONGITUD_LINEA_LEIDA, ptrFile);
	
		while((!feof(ptrFile)) && (flags.statusDelPrograma == OK_PROGRAMA)) {
			procesoLinea(ptrALineaLeida);
			ptrALineaLeida = fgets(lineaLeida, LONGITUD_LINEA_LEIDA, ptrFile);
		}
	}
	else {
		flags.statusDelPrograma = ERROR_PROGRAMA;
		string str(nombreArchivo);
		char* dir = get_current_dir_name();
		cout << "Se trato de incluir al archivo " << str << ", pero no existe en el servidor" << endl;
		cout << "Se lo busco en " << dir << endl;
	    cout << "Causas del error: no se envio el archivo requerido o el servidor fallo al crearlo" << endl;
	    free(dir);
	}

	if (ptrFile != NULL) fclose(ptrFile);
}

/*
* si el ultimo ifdef/ifndef establece que hay que compilar, se procede a:
* -quitar comentarios (se realiza en un ciclo while).
* -procesar directivas de compilador o buscar reemplazos por define.
* si el ultimo ifdef/ifndef establece que no hay que compilar,
* entonces se busca la directiva else o endif.
* */
void Procesador::procesoLinea(char* linea) {
	
	if (ifDefAnidados.compilar()) {
		flags.todaviaTieneComentarios = true;
		while (flags.todaviaTieneComentarios)
			linea = precompilador.quitarComentarios(linea, flags);
	
		/*  linea puede salir totalmente "vacia" de quitarComentarios
		 *  si ese fuera el caso, no se la procesa
		 *  */
		if (flags.lineaNoEstaTotalmenteComentada())
			procesarDirectivaOBuscarReemplazos(linea);
	}
else {
	parseInstruccion(linea, (char*)ELSE, COD_INSTR_ELSE);
	parseInstruccion(linea, (char*)ENDIF, COD_INSTR_ENDIF);
	}
}

	/* Luego del proceso que corresponda, se imprime la salida.
	* */
void Procesador::procesarDirectivaOBuscarReemplazos(char* linea) {
	char* salida;
	
	if (esDirectivaDeCompilador(linea)) {
		salida = procesarDirectivaCompilador(linea);
	} else {
		salida = precompilador.buscarReemplazos(linea, lista);
		cout << salida;
	
		fflush(stdout);
	}
}
	/*  si la linea comienza con #, lo interpreto como una directiva */
bool Procesador::esDirectivaDeCompilador(char* linea) {
	return (linea[0] == NUMERAL);
}
