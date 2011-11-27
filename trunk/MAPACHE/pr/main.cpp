#include "Precompilador.h"
#include "ContenedorDeDefines.h"
#include "FlagsDePrograma.h"
#include "Utilitarias.h"
#include "SeparadoresValidos.h"
#include "IfDefAnidados.h"
#include "Procesador.h"
#include "FlagsDePrograma.h"
#include "ParserEntradaEstandar.h"
#include <errno.h>
#define TAM_MAX_POST 100000  //  100 kb
using std::cerr;

#include <iostream>
using std::cout;

void precompilarArchivo(const char* nombreArchivo) {
	Procesador p;
	p.procesoArchivoEntrada(nombreArchivo);
}
void printHeader() {
	cout << "<HTML>\n";
	cout << "<HEAD><TITLE>Precompilador c/c++</TITLE>";
	cout << "<script src=\"src/prettify.js\" type=\"text/javascript\"></script>";
	cout << "    <link href=\"src/prettify.css\"";
	cout << " type=\"text/css\" rel=\"stylesheet\" />";
	cout << "</HEAD>\n";
	cout << "<BODY onload=\"prettyPrint()\"";
	cout << " BGCOLOR=\"#AAAFFF\"TEXT=\"#000000\">\n";
	cout << "<pre class=\"prettyprint\">";
}

void printFooter() {
	cout << "<pre/>";
	cout << "</BODY>\n";
	cout << "</HTML>\n";
}

/* se precompila el archivo ppal (y los archivos que incluya)
 * args:
 * 0- nombre programa
 * 1- path en donde se deben almacenar los archivos creados por el programa
 * 2- uri (no usada por este cgi)*/

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
			int cantArchivos = parser.crearArchivosAPartirDeEntradaEstandar();

			if (cantArchivos > 0) {
				precompilarArchivo(parser.getNombreArchivoPpal().c_str());
			} else if (cantArchivos == 0)
				cout << "No se recibieron archivos para precompilar...";
			else {
				cout
						<< "Se leyo una cantidad de bytes superior a la esperada. "
						<< endl;
				cout << "Cant. esperada (content_length): "
						<< parser.getContent_length() << endl;
				cout << "Cant. leida: " << parser.getCantBytesLeidos() << endl;
			}

			parser.setIterador();

			for (int a = 0; a < cantArchivos; a++) {
				string nombreArch = parser.getSiguienteNombreArch();
				string rutaArch(argv[1]);
				rutaArch.append(nombreArch);
				if (remove(nombreArch.c_str()) == -1) {
					cerr << "Error deleting file: " << rutaArch << endl;
					cerr << "errno: " << errno << endl;
					cerr << "strerror(errno)):  " << strerror(errno) << endl;
				}
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
