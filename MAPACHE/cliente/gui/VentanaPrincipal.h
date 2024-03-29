#ifndef VENTANAPRINCIPAL_H_
#define VENTANAPRINCIPAL_H_
#include <gtkmm-2.4/gtkmm.h>
#include "Configuracion.h"
#include "TipoEstatico.h"
#include "TipoDinamico.h"
#include "ClienteControl.h"
#include "Solapas.h"
#include "BarraDeEstado.h"

//  #define CMD_APP_POR_DEFECTO "xdg-open "
#define CMD_APP_POR_DEFECTO "firefox "
#define PATH_DOC_TECNICA_CONFIGURADOR \
	"Documentacion/Doxy/DoxyConfiguradorCliente/html/index.html"
#define PATH_DOC_TECNICA_PRECOM \
	"Documentacion/Doxy/DoxyCGI_Precompilador/html/index.html"
#define	PATH_DOC_TECNICA_PARSER_PHP \
	"Documentacion/Doxy/DoxyParserPHP/html/index.html"
#define PATH_DOC_TECNICA_PRECOM_ZIP \
	"Documentacion/Doxy/DoxyPr-Zip/html/index.html"
#define PATH_DOC_TECNICA_PRECOM_CGI \
	"Documentacion/Doxy/DoxyCGI_Precompilador/html/index.html"
#define PATH_DOC_TECNICA_SERVIDOR \
	"Documentacion/Doxy/DoxyServidorMapache/html/index.html"
#define PATH_DOC_USUARIO "Ayuda/index.html"
#define PATH_SERVIDOR "./ServidorMapache"
#define PATH_INTERFACE "./Interfaz/gui.glade"
#define TEMP_PATH_XML "./config_temp.xml"
#define TEMP_PATH_CONFIG "./configPorDefecto.xml"
#define TAM_LINEA 255

/**
 * Clase que es la ventana principal de la aplicacion
 */
class VentanaPrincipal {
private:
	ClienteControl clienteControl;
	Solapas* menuSolapas;

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
	bool cargarConfiguracion(const std::string &path);

	/* Guardar configuracion */
	void guardarConfiguracion(const std::string &filename);
	void on_click_GuardarConfiguracionPorDefecto();

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
	void on_click_VerDocTecnicaConfigurador();
	void on_click_VerDocPrecompilador();
	void on_click_VerDocParserPhp();
	void on_click_VerDocPrecompiladorZip();
	void on_click_VerDocPrecompiladorCgi();
	void on_click_VerDocServidor();

	void abrirDocumentacion(const std::string& ruta);

		/* Eventos de la barra de herramientas */
	void iniciarServidor(bool forzarSocket);
	void on_click_IniciarServidor();
	void on_click_ReiniciarServidor();
	void on_click_DetenerServidor();

	/* Mostrar o ocultar las solapas */
	void on_click_CambiarVistaSolapas();

	/* widget barra de estado */
	BarraDeEstado* barraDeEstado;

	/* Toolbar */
	Gtk::Toolbar* barraTexto;

	/* Inicializaciones */
	void cargarBarraDeMenu();
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
