#include "VentanaPrincipal.h"

/**
 * Inicializa la aplicacion con la interfaz grafica.
 */
int main(int argc, char **argv) {
	VentanaPrincipal ventana;

	try {
		ventana.init(argc, argv);
	} catch (const Glib::FileError& ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	} catch (const Gtk::BuilderError& ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
