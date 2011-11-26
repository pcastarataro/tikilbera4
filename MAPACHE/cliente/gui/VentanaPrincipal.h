#ifndef VENTANAPRINCIPAL_H_
#define VENTANAPRINCIPAL_H_
#include <gtkmm-2.4/gtkmm.h>
#include "Configuracion.h"
#include "TipoEstatico.h"
#include "TipoDinamico.h"
#include "ClienteControl.h"
#include "vbViewAcceso.h"
#include "vbViewError.h"
#include "Solapas.h"
//#include "GrillaUsuarios.h"
//#include "GrillaEstaticos.h"
//#include "GrillaDinamicos.h"
//#include "GrillaErrores.h"

#define PATH_SERVIDOR "./ServidorMapache"
#define PATH_INTERFACE "./Interfaz/gui.glade"
#define TEMP_PATH_XML "./config_temp.xml"

/**
 * Clase que es la ventana principal de la aplicacion
 */
class VentanaPrincipal {
private:
	ClienteControl clienteControl;
	Solapas* menuSolapas;
//	GrillaUsuarios* grillaUsuarios;
//	GrillaEstaticos* grillaEstaticos;
//	GrillaDinamicos* grillaDinamicos;
//	GrillaErrores* grillaErrores;

	/* Builder */
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Window *ventanaPpal;

	/* Barra de menu */
	Gtk::Widget* menu;
	Glib::RefPtr<Gtk::UIManager> menu_UIManager;
	Glib::RefPtr<Gtk::ActionGroup> menuArchivo;
	Glib::RefPtr<Gtk::ActionGroup> menuConfiguracion;
	Glib::RefPtr<Gtk::ActionGroup> menuControl;
	Glib::RefPtr<Gtk::ActionGroup> menuReportes;
	Glib::RefPtr<Gtk::ActionGroup> menuAyuda;

	/* Abrir configuracion */
	void cargarConfiguracion(const std::string &path);

	/* Guardar configuracion */
	void guardarConfiguracion(const std::string &filename);

	/* Eventos barra de menu. */
	void on_click_CargarConfiguracion();
	void on_click_GuardarConfiguracion();
	void on_click_Salir();
	void on_click_ConfiguracionBasica();
	void on_click_ConfiguracionTiposEstaticos();
	void on_click_ConfiguracionTiposDinamicos();
	void on_click_ConfiguracionErrores();
	void on_click_ConfiguracionUsuarios();
	void on_click_VerReportesErrores();
	void on_click_VerReportesAccesos();
	void on_click_ConfiguracionReportes();
	void on_click_VerAcercaDe();
	void on_click_VerAyuda();

	/* Eventos de la barra de herramientas */
	void on_click_IniciarServidor();
	void on_click_ReiniciarServidor();
	void on_click_DetenerServidor();

	/* Mostrar o ocultar las solapas */
	void on_click_CambiarVistaSolapas();

	/* widget barra de estado */
	Gtk::Statusbar *barraEstado;

	/* Toolbar */
	Gtk::Toolbar* barraTexto;

	/* Inicializaciones */
	void cargarBarraDeMenu();
	void cargarWidget();
	void cargarBarraDeHerramientas();
	void conectarEventos();
	std::string buscarRutaArchivo();

public:
	/**
	 * Constructor
	 */
	VentanaPrincipal();

	/**
	 * Destructor
	 */
	virtual ~VentanaPrincipal();

	/**
	 * inicializa la aplicacion con la configuracion por defecto y muestra la
	 * ventana grafica.
	 * @param argv argumentos
	 * @param argc cantidad de argumentos que recibe argv
	 */
	void init(int argc, char *argv[]);
};

#endif
