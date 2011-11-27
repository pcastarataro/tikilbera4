#ifndef PRECOMPILADOR_H_
#define PRECOMPILADOR_H_

#include "Constantes.h"
#include "FlagsDePrograma.h"
#include "ContenedorDeDefines.h"
#include "SeparadoresValidos.h"
#include <string.h>

class Precompilador {
private:
	SeparadoresValidos sepValidos;
	/**
	 * Busca apertura de comentarios en sus diversas formas.
	 * @param lineaAux Cadena de caracteres que no contiene los comentarios de linea.
	 * @param linea Linea leida del archivo en proceso.
	 * @param flags Pasa banderas relevantes para el funcionamiento del algoritmo.
	 * @return void
	 */
	void buscarAperturaDeComentarioOBarraDoble(char* lineaAux, char* linea,
			FlagsDePrograma& flags);
	/**
	 * Busca cierre de comentarios.
	 * @param lineaAux Cadena de caracteres que no contiene los comentarios de linea.
	 * @param linea Linea leida del archivo en proceso.
	 * @param flags Pasa banderas relevantes para el funcionamiento del algoritmo.
	 * @return void
	 */
	void buscarCierreDeComentario(char* lineaAux, char* linea,
			FlagsDePrograma& flags);
public:
	/**
	 * Constructor
	 */
	Precompilador() {
	}
	/**
	 * Busca define`s en la linea, y efectua reemplazos si halla coincidencias.
	 * @param linea Cadena de caracteres sobre la que se buscaran posibles reemplazos.
	 * @param contenedor Contiene a los nombres de los defines y a sus valores correspondientes.
	 * @return char* La linea, con los reemplazos efectuados.
	 */
	char* buscarReemplazos(char* linea, ContenedorDeDefines& contenedor);
	/**
	 * Remueve los comentarios que pueda tener la linea.
	 * @param linea Cadena de caracteres sobre la que se buscaran los comentarios.
	 * @param flags Pasa banderas relevantes para el funcionamiento del algoritmo.
	 * @return char* La linea, con los comentarios removidos.
	 */
	char* quitarComentarios(char* linea, FlagsDePrograma& flags);
	/**
	 * Destructor
	 */
	~Precompilador() {
	}
};
#endif /* PRECOMPILADOR_H_ */
