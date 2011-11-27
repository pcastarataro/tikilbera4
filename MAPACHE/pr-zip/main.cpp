#include "ConstantesParser.h"
#include "Precompilador.h"
#include "ContenedorDeDefines.h"
#include "FlagsDePrograma.h"
#include "Utilitarias.h"
#include "SeparadoresValidos.h"
#include "IfDefAnidados.h"
#include "Procesador.h"
#include "FlagsDePrograma.h"
#include "Constantes.h"
#include "ParserEntradaEstandar.h"
#include <errno.h>
using std::cerr;

void precompilarArchivo(const char* nombreArchivo) {
	Procesador p;
	p.procesoArchivoEntrada(nombreArchivo);
}

/* se precompila el archivo ppal (y los archivos que incluya) 
 * args:
 * 0- nombre programa
 * 1- path en donde se deben almacenar los archivos creados por el programa
 * 2- uri (no usada por este cgi)*/

void printHeader() {
	cout << "<HTML>\n";
	cout << "<HEAD><TITLE>Precompilador c/c++</TITLE>";
	cout << "<script src=\"src/prettify.js\"";
	cout << " type=\"text/javascript\"></script>";
	cout << "    <link href=\"src/prettify.css\"";
	cout << "type=\"text/css\" rel=\"stylesheet\" />";
	cout << "</HEAD>\n";

	cout
			<< "<BODY onload=\"prettyPrint()\" BGCOLOR=\"#AAAFFF\"TEXT=\"#000000\">\n";
	cout << "<pre class=\"prettyprint\">";
}

void printFooter() {
	cout << "<pre/>";
	cout << "</BODY>\n";
	cout << "</HTML>\n";
}

int main(int argc, char** argv) {
	printHeader();
	if (argc != 3)
		cout << "error al ejecutar CGI: cant de parametros erronea: " << argc
				<< ". Deberian ser 3." << endl;
	else {
		int content_length = atoi(getenv("CONTENT_LENGTH"));
		if (content_length <= TAM_MAX_POST) {
			chdir("/");
			chdir(argv[1]);
			ParserEntradaEstandar parser(content_length, argv[1]);
			int resultadoDescompresion = parser.descomprimir();

			if (resultadoDescompresion == OK) {
				string rutaCompletaFuentes(argv[1]);
				rutaCompletaFuentes.append(
						parser.getNombreCarpetaDescomprimida());
				rutaCompletaFuentes.append("/");
				chdir(rutaCompletaFuentes.c_str());
				precompilarArchivo(parser.getNombreArchivoPpal().c_str());

				chdir("/");
				chdir(argv[1]);
				if (remove(parser.getNombreArchivoComprimido().c_str()) == -1) {
					cerr << "Error borrando archivo zip: "
							<< parser.getNombreArchivoComprimido() << endl;
					cerr << "errno: " << errno << endl;
					cerr << "strerror(errno)):  " << strerror(errno) << endl;
				}

				string comandoBorrarCarpetaDescomprimida("rm -dfr ");

				comandoBorrarCarpetaDescomprimida.append(
						parser.getNombreCarpetaDescomprimida());
				comandoBorrarCarpetaDescomprimida.append("/");
				system(comandoBorrarCarpetaDescomprimida.c_str());

			} else if (resultadoDescompresion == NOMBRE_ARCHIVO_INVALIDO)
				cout << "No se recibieron archivos para precompilar...";
			else if (resultadoDescompresion == CONTENT_LENGTH_EXCEDIDO) {
				cout
						<< "Se leyo una cantidad de bytes superior a la esperada. "
						<< endl;
				cout << "Cant. esperada (content_length): "
						<< parser.getContent_length() << endl;
				cout << "Cant. leida: " << parser.getCantBytesLeidos() << endl;
			}
		} else {
			cout << "El tamaño de los archivos supera ";
			cout << "el maximo permitido por la aplicacion." << endl;
			cout << "Tamaño max: " << TAM_MAX_POST << endl;
			cout << "Tamaño de los archivos: " << content_length;
		}
	}

	printFooter();

	return 1;
}
