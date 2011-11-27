#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#include "ContenedorDeDefines.h"
#include "IfDefAnidados.h"
#include "FlagsDePrograma.h"
#include "Utilitarias.h"
#include "SeparadoresValidos.h"
#include "Precompilador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
class Procesador {
private:
	Precompilador precompilador;
	FlagsDePrograma flags;
	ContenedorDeDefines lista;
	IfDefAnidados ifDefAnidados;
	Utilitarias util;

	/**
	 * Verifica la validez del separador, dada la instruccion.
	 * @param instruccion Cadena de caracteres que contiene el nombre de una instruccion de compilador.
	 * @param separador Caracter siguiente o anterior a la instruccion.
	 * @return bool
	 */
	bool esSeparadorValidoParaLaInstruccion(char* instruccion, char separador);
	/**
	 * Parsea la instruccion dada en instr.
	 * @param instr Cadena de caracteres que contiene el nombre de una instruccion de compilador.
	 * @param codInstruccion Entero que representa univocamente a una determinada instruccion.
	 * @return true Si pudo procesar la instruccion.
	 */
	bool parseInstruccion(char* linea, char* instr, int codInstruccion);
	/**
	 * Realiza las acciones correspondientes al codigo de instruccion que se recibe como parametro.
	 * @param linea Linea leida del archivo en proceso.
	 * @param codInstr Entero que representa univocamente a una determinada instruccion.
	 * @return void
	 */
	void procesarInstruccion(char* linea, int codInstr);
	/**
	 * Procesa la instruccion ifdef/ifndef.
	 * @param linea Linea leida del archivo en proceso.
	 * @param codInstr Entero que representa univocamente a una determinada instruccion.
	 * @return void
	 */
	void procesarIfdefOIfndef(char* linea, int codInstr);
	/**
	 * Procesa la instruccion include.
	 * @param linea Linea leida del archivo en proceso.
	 * @return void
	 */
	void procesarInclude(char* linea);
	/**
	 * Procesa la instruccion else.
	 * @param linea Linea leida del archivo en proceso.
	 * @return void
	 */
	void procesarElse(char* linea);
	/**
	 * Procesa la instruccion endif.
	 * @param linea Linea leida del archivo en proceso.
	 * @return void
	 */
	void procesarEndif(char* linea);
	/**
	 * Procesa la instruccion define.
	 * @param linea Linea leida del archivo en proceso.
	 * @return void
	 */
	void procesarDefine(char* linea);
	/**
	 * Sabiendo que se trata de una directiva de compilador, se intenta saber cual de ellas es.
	 * @param linea Linea leida del archivo en proceso.
	 * @return char* una cadena nula.
	 */
	char* procesarDirectivaCompilador(char* linea);
	/**
	 * Quita comentarios, reemplaza define`s, 
	 * o procesa directivas de compilador que se encuentren en la linea.
	 * @param linea Linea leida del archivo en proceso.
	 * @return void
	 */
	void procesoLinea(char* linea);
	/**
	 * Decide si hay que procesar una directiva de compilador o buscar reemplazos.
	 * @param linea Linea leida del archivo en proceso.
	 * @return void
	 */
	void procesarDirectivaOBuscarReemplazos(char* linea);
	/**
	 * Decide si el contenido de lina es una directiva de compilador.
	 * @param linea Linea leida del archivo en proceso.
	 * @return void
	 */
	bool esDirectivaDeCompilador(char* linea);
public:
	/**
	 * Constructor
	 */
	Procesador() {
	}
	/**
	 * Lee linea a linea el archivo de entrada, y las procesa.
	 * Emite la salida por consola.
	 * @param nombreArchivo Nombre del archivo a procesar.
	 * @return void
	 */
	void procesoArchivoEntrada(const char* nombreArchivo);
	// {cout << "procesoArchivoEntrada!!!!!" << endl;}
	/**
	 * Destructor
	 */
	~Procesador() {
	}
};
#endif /* PROCESADOR_H_ */
