#include "VentanaPrincipal.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <list>

void VentanaPrincipal::on_click_CambiarVistaSolapas() {
	menuSolapas->cambiarVisibilidadSolapas();
}

void VentanaPrincipal::conectarEventos() {
	Gtk::Button *btnTickSolapas;
	builder->get_widget("btnTickSolapas", btnTickSolapas);
	btnTickSolapas->signal_clicked().connect(
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_CambiarVistaSolapas));
}

bool existeArchivo(const std::string& nombreArchivo) {
	bool existe;
	std::ifstream archivo(nombreArchivo.c_str());
	existe = archivo.good();
	if (existe)
		archivo.close();
	return existe;
}

bool VentanaPrincipal::cargarConfiguracion(const std::string &path) {
	Configuracion configuracion;
	bool cargoOk = configuracion.cargarDesde(path);
	if (cargoOk)
		menuSolapas->cargarConfiguracion(configuracion);
	return cargoOk;
}

void VentanaPrincipal::on_click_CargarConfiguracion() {
	std::string filename = buscarRutaArchivo();
	bool cargoOk = cargarConfiguracion(filename);
	if (cargoOk) {
		barraDeEstado->mensajeOk("Se cargo la configuracion " + filename);
	} else {
		barraDeEstado->mensajeError("No se pudo cargar la configuracion");
	}
}

std::string VentanaPrincipal::buscarRutaArchivo() {
	Gtk::FileChooserDialog dialog("Abrir archivo",
			Gtk::FILE_CHOOSER_ACTION_OPEN);

	dialog.set_transient_for(*ventanaPpal);

	// Agrego los botones para la respuesta:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	// Muestro el dialogo y espero hasta que elija una opcion.
	int result = dialog.run();

	// Reviso el resultado.
	if (result == Gtk::RESPONSE_OK)
		return dialog.get_filename();
	else
		return "";
}

void VentanaPrincipal::guardarConfiguracion(const std::string &filename) {
	menuSolapas->guardarConfiguracion(filename);
}

void VentanaPrincipal::on_click_GuardarConfiguracionPorDefecto() {
	guardarConfiguracion(TEMP_PATH_CONFIG);
	barraDeEstado->mensajeOk("Se guardo la configuracion por defecto");
}

void VentanaPrincipal::on_click_GuardarConfiguracion() {
	Gtk::FileChooserDialog dialog("Guardar como...",
			Gtk::FILE_CHOOSER_ACTION_SAVE);

	dialog.set_transient_for(*ventanaPpal);

	//  Agrego los botones para la respuesta:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
	dialog.set_current_name("Configuracion.xml");
	dialog.set_do_overwrite_confirmation(true);

	//  Muestro el dialogo y espero hasta que elija una opcion.
	int result = dialog.run();

	//  Reviso el resultado.
	switch (result) {
	case(Gtk::RESPONSE_OK): {
		std::string filename = dialog.get_filename();
		guardarConfiguracion(filename);
		barraDeEstado->mensajeOk("Se guardo la configuracion correctamente");
		break;
	}
	case(Gtk::RESPONSE_CANCEL): {
		barraDeEstado->mensajeInfo("Guardar configuracion cancelada");
		break;
	}
	default: {
		barraDeEstado->mensajeInfo("No se guardo la configuracion");
		break;
	}
	}
}

void VentanaPrincipal::on_click_Salir() {
	Gtk::Main::quit();
}

void VentanaPrincipal::on_click_ConfiguracionBasica() {
	menuSolapas->set_current_page(SOLAPA_CONF_BASICA);
}

void VentanaPrincipal::on_click_ConfiguracionTiposEstaticos() {
	menuSolapas->set_current_page(SOLAPA_CONF_ESTATICO);
}

void VentanaPrincipal::on_click_ConfiguracionTiposDinamicos() {
	menuSolapas->set_current_page(SOLAPA_CONF_DINAMICO);
}

void VentanaPrincipal::on_click_ConfiguracionErrores() {
	menuSolapas->set_current_page(SOLAPA_CONF_CODIG_ERRORES);
}

void VentanaPrincipal::on_click_ConfiguracionUsuarios() {
	menuSolapas->set_current_page(SOLAPA_CONF_USUARIO);
}

void VentanaPrincipal::on_click_ConfiguracionReportes() {
	menuSolapas->set_current_page(SOLAPA_CONF_REPORTES);
}

void VentanaPrincipal::on_click_VerReportesErrores() {
	menuSolapas->set_current_page(SOLAPA_REPORTE_ERROR);
}

void VentanaPrincipal::on_click_VerReportesAccesos() {
	menuSolapas->set_current_page(SOLAPA_REPORTE_ACCESO);
}

void VentanaPrincipal::abrirDocumentacion(const std::string& ruta) {
	bool existe = existeArchivo(ruta);
	if (existe) {
		std::string comando = CMD_APP_POR_DEFECTO;
		comando.append(" ");
		comando.append(ruta.c_str());
		comando.append("&");
		system(comando.c_str());
		barraDeEstado->mensajeOk("Mostrando documentacion tecnica");
	} else
		barraDeEstado->mensajeError("no se encuetra la documentacion tecnica");
}

void VentanaPrincipal::on_click_VerDocTecnicaConfigurador() {
	abrirDocumentacion(PATH_DOC_TECNICA_CONFIGURADOR);
}

void VentanaPrincipal::on_click_VerAyuda() {
	abrirDocumentacion(PATH_DOC_USUARIO);
}

void VentanaPrincipal::on_click_VerDocPrecompilador() {
	abrirDocumentacion(PATH_DOC_TECNICA_PRECOM);
}

void VentanaPrincipal::on_click_VerDocParserPhp() {
	abrirDocumentacion(PATH_DOC_TECNICA_PARSER_PHP);
}

void VentanaPrincipal::on_click_VerDocPrecompiladorZip() {
	abrirDocumentacion(PATH_DOC_TECNICA_PRECOM_ZIP);
}

void VentanaPrincipal::on_click_VerDocPrecompiladorCgi() {
	abrirDocumentacion(PATH_DOC_TECNICA_PRECOM_CGI);
}

void VentanaPrincipal::on_click_VerDocServidor() {
	abrirDocumentacion(PATH_DOC_TECNICA_SERVIDOR);
}

void VentanaPrincipal::on_click_VerAcercaDe() {
	Gtk::AboutDialog* about;
	builder->get_widget("ventanaAcercaDe", about);
	if (about) {
		about->run();
		about->hide();
	}
}

void VentanaPrincipal::iniciarServidor(bool forzarSocket) {
	std::string comando = PATH_SERVIDOR;
	FILE* fpipe;
	char line[TAM_LINEA];
	char* linea = line;
	std::string flagForzarSocket = "N";

	if (forzarSocket)
		flagForzarSocket = "R";

	//  Creo un xml temporal para iniciar el servidor.
	guardarConfiguracion(TEMP_PATH_XML);

	if (!existeArchivo(PATH_SERVIDOR))
		comando = buscarRutaArchivo();

	if (comando != "") {
		comando.append(" ");
		comando.append(TEMP_PATH_XML);
		comando.append(" ");
		comando.append(flagForzarSocket.c_str());
		comando.append("&");
		if (!(fpipe = (FILE*) popen(comando.c_str(), "r"))) {
			barraDeEstado->mensajeError("No se pudo encontrar el servidor");
		} else {
			size_t tamanioLinea = TAM_LINEA;
			size_t size = getline(&linea, &tamanioLinea, fpipe);
			linea[size - 1] = '\0';
			barraDeEstado->mensajeInfo(linea);
		}
		pclose(fpipe);
	}
}

void VentanaPrincipal::on_click_IniciarServidor() {
	iniciarServidor(true);
}

void VentanaPrincipal::on_click_ReiniciarServidor() {
	on_click_DetenerServidor();
	iniciarServidor(true);
}

void VentanaPrincipal::on_click_DetenerServidor() {
	bool detenido;
	int nroPuerto;
	Gtk::SpinButton* sbtPuertoContro;
	builder->get_widget("sbtPuertoContro", sbtPuertoContro);
	nroPuerto = sbtPuertoContro->get_value();
	detenido = clienteControl.detenerServidor("127.0.0.1", nroPuerto);
	if (detenido) {
		barraDeEstado->mensajeOk("El servidor se detuvo con exito");
	} else {
		barraDeEstado->mensajeError("No se pude detener el servidor");
	}
}

void VentanaPrincipal::cargarBarraDeMenu() {
	Gtk::Box *vboxMenuBar;

	menuArchivo = Gtk::ActionGroup::create();
	menuConfiguracion = Gtk::ActionGroup::create();
	menuControl = Gtk::ActionGroup::create();
	menuReportes = Gtk::ActionGroup::create();
	menuAyuda = Gtk::ActionGroup::create();

	/* Menu -Archivo- */
	menuArchivo->add(Gtk::Action::create("ArchivoMenu", "Archivo"));

	menuArchivo->add(
			Gtk::Action::create("Abrir", Gtk::Stock::DELETE, "_Abrir",
					"Abrir archivo"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_CargarConfiguracion));

	menuArchivo->add(
			Gtk::Action::create("Guardar", Gtk::Stock::DELETE, "_Guardar",
					"Guardar configuracion"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_GuardarConfiguracion));

	menuArchivo->add(
			Gtk::Action::create("GuardarPorDefecto", Gtk::Stock::DELETE,
					"Guardar por defecto", "Guardar por defecto"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_GuardarConfiguracionPorDefecto));

	menuArchivo->add(Gtk::Action::create("Salir", Gtk::Stock::QUIT),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_Salir));

	/* Menu -Configuración- */
	menuConfiguracion->add(Gtk::Action::create("ConfigMenu", "Configuración"));

	menuConfiguracion->add(
			Gtk::Action::create("Basica", Gtk::Stock::PREFERENCES, "_Basica",
					"Configuracion basica"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_ConfiguracionBasica));

	menuConfiguracion->add(
			Gtk::Action::create("tiposEstaticos", Gtk::Stock::PREFERENCES,
					"_Estaticos", "Configuracion tipos estaticos"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_ConfiguracionTiposEstaticos));

	menuConfiguracion->add(
			Gtk::Action::create("tiposDinamicos", Gtk::Stock::PREFERENCES,
					"_Dinamicos", "Configuracion tipos dinamicos"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_ConfiguracionTiposDinamicos));

	menuConfiguracion->add(
			Gtk::Action::create("tiposErrores", Gtk::Stock::PREFERENCES,
					"_Errores", "Configuracion tipos errores"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_ConfiguracionErrores));

	menuConfiguracion->add(
			Gtk::Action::create("Usuarios", Gtk::Stock::PREFERENCES,
					"_Usuarios", "Configuracion usuarios"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_ConfiguracionUsuarios));

	/* Menu -Control- */
	menuControl->add(Gtk::Action::create("ControlMenu", "Control"));

	menuControl->add(
			Gtk::Action::create("IniciarServidor", Gtk::Stock::PREFERENCES,
					"_Iniciar", "Iniciar Servidor"),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_IniciarServidor));

	menuControl->add(
			Gtk::Action::create("DetenerServidor", Gtk::Stock::PREFERENCES,
					"_Detener", "Detener Servidor"),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_DetenerServidor));

	menuControl->add(
			Gtk::Action::create("ReiniciarServidor", Gtk::Stock::PREFERENCES,
					"_Reiniciar", "Reiniciar Servidor"),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_ReiniciarServidor));

	/* Menu -Reportes- */
	menuReportes->add(Gtk::Action::create("ReportesMenu", "Reportes"));

	menuReportes->add(
			Gtk::Action::create("reporteAccesos", Gtk::Stock::PREFERENCES,
					"_Ver Reportes Accesos", "Configuracion reportes accesos"),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_VerReportesAccesos));
	menuReportes->add(
			Gtk::Action::create("reporteErrores", Gtk::Stock::PREFERENCES,
					"_Ver Reportes Errores", "Configuracion reportes errores"),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_VerReportesErrores));

	menuReportes->add(
			Gtk::Action::create("configurarReportes", Gtk::Stock::PREFERENCES,
					"_Configurar Reportes", "Configuracion de reportes"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_ConfiguracionReportes));

	/* Menu -Ayuda- */
	menuAyuda->add(Gtk::Action::create("HelpMenu", "Ayuda"));

	menuAyuda->add(
			Gtk::Action::create("ManualUsuario", Gtk::Stock::HELP,
					"_Manual de usuario", "ManualUsuario"),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_VerAyuda));

	menuAyuda->add(
			Gtk::Action::create("ManualConfigurador", Gtk::Stock::INFO,
					"Manual tecnico Configurador Mapache", "ManualConfigurador"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_VerDocTecnicaConfigurador));
	menuAyuda->add(
			Gtk::Action::create("ManualPrecompilador", Gtk::Stock::INFO,
					"Manual tecnico Precompilador", "ManualPrecompilador"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_VerDocPrecompilador));
	menuAyuda->add(
			Gtk::Action::create("ManualParserPhp", Gtk::Stock::INFO,
					"Manual tecnico Parser php", "ManualParserPhp"),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_VerDocParserPhp));
	menuAyuda->add(
			Gtk::Action::create("ManualPrecompiladorZip", Gtk::Stock::INFO,
					"Manual tecnico Precompilador Zip",
					"ManualPrecompiladorZip"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_VerDocPrecompiladorZip));
	menuAyuda->add(
			Gtk::Action::create("ManualPrecompiladorCgi", Gtk::Stock::INFO,
					"Manual tecnico Precompilador Cgi",
					"ManualPrecompiladorCgi"),
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_VerDocPrecompiladorCgi));
	menuAyuda->add(
			Gtk::Action::create("ManualServidor", Gtk::Stock::INFO,
					"Manual tecnico Servidor Mapache", "ManualServidor"),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_VerDocServidor));

	menuAyuda->add(
			Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT, "A_cerca De",
					"Acerca de ..."),
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_VerAcercaDe));

	menu_UIManager = Gtk::UIManager::create();
	menu_UIManager->insert_action_group(menuArchivo);
	menu_UIManager->insert_action_group(menuConfiguracion);
	menu_UIManager->insert_action_group(menuControl);
	menu_UIManager->insert_action_group(menuReportes);
	menu_UIManager->insert_action_group(menuAyuda);

	ventanaPpal->add_accel_group(menu_UIManager->get_accel_group());

	Glib::ustring ui_info = "<ui>"
		"  <menubar name='MenuBar'>"
		"    <menu action='ArchivoMenu'>"
		"      <menuitem action='Abrir'/>"
		"      <menuitem action='Guardar'/>"
		"          <separator/>"
		"      <menuitem action='GuardarPorDefecto'/>"
		"          <separator/>"
		"      <menuitem action='Salir'/>"
		"    </menu>"
		"    <menu action='ConfigMenu'>"
		"      <menuitem action='Basica'/>"
		"      <menuitem action='tiposEstaticos'/>"
		"      <menuitem action='tiposDinamicos'/>"
		"      <menuitem action='tiposErrores'/>"
		"      <menuitem action='Usuarios'/>"
		"    </menu>"
		"    <menu action='ControlMenu'>"
		"      <menuitem action='IniciarServidor'/>"
		"      <menuitem action='DetenerServidor'/>"
		"      <menuitem action='ReiniciarServidor'/>"
		"    </menu>"
		"    <menu action='ReportesMenu'>"
		"      <menuitem action='reporteErrores'/>"
		"      <menuitem action='reporteAccesos'/>"
		"          <separator/>"
		"      <menuitem action='configurarReportes'/>"
		"    </menu>"
		"    <menu action='HelpMenu'>"
		"      <menuitem action='ManualUsuario'/>"
		"          <separator/>"
		"      <menuitem action='ManualConfigurador'/>"
		"      <menuitem action='ManualParserPhp'/>"
		"      <menuitem action='ManualPrecompilador'/>"
		"      <menuitem action='ManualPrecompiladorZip'/>"
		"      <menuitem action='ManualPrecompiladorCgi'/>"
		"      <menuitem action='ManualServidor'/>"
		"          <separator/>"
		"      <menuitem action='HelpAbout'/>"
		"    </menu>"
		"  </menubar>"
		"</ui>";

#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try {
		menu_UIManager->add_ui_from_string(ui_info);
	}
	catch(const Glib::Error& ex) {
		std::cerr << "building menus failed: " << ex.what();
	}

#else
	std::auto_ptr < Glib::Error > ex;
	menu_UIManager->add_ui_from_string(ui_info, ex);
	if (ex.get()) {
		std::cerr << "building menus failed: " << ex->what();
	}
#endif  // GLIBMM_EXCEPTIONS_ENABLED
	menu = menu_UIManager->get_widget("/MenuBar");

	builder->get_widget("vboxMenuBar", vboxMenuBar);
	vboxMenuBar->pack_end(*menu, Gtk::PACK_SHRINK);
}

void VentanaPrincipal::cargarBarraDeHerramientas() {
	Gtk::ToolButton * toolbtAbrir;
	Gtk::ToolButton * toolbtGuardar;
	Gtk::ToolButton * toolbtIniciarServidor;
	Gtk::ToolButton * toolbtDetenerServidor;
	Gtk::ToolButton * toolbtReiniciarServidor;

	builder->get_widget("toolbtAbrir", toolbtAbrir);
	builder->get_widget("toolbtGuardar", toolbtGuardar);
	builder->get_widget("toolbtIniciarServidor", toolbtIniciarServidor);
	builder->get_widget("toolbtDetenerServidor", toolbtDetenerServidor);
	builder->get_widget("toolbtReiniciarServidor", toolbtReiniciarServidor);

	toolbtAbrir->signal_clicked().connect(
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_CargarConfiguracion));

	toolbtGuardar->signal_clicked().connect(
			sigc::mem_fun(*this,
					&VentanaPrincipal::on_click_GuardarConfiguracion));

	toolbtIniciarServidor->signal_clicked().connect(
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_IniciarServidor));

	toolbtDetenerServidor->signal_clicked().connect(
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_DetenerServidor));

	toolbtReiniciarServidor->signal_clicked().connect(
			sigc::mem_fun(*this, &VentanaPrincipal::on_click_ReiniciarServidor));
}

void VentanaPrincipal::init(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);

	// Creo la GUI a partir del .glade
	builder = Gtk::Builder::create_from_file(PATH_INTERFACE);

	builder->get_widget("ventanaConfiguracion", ventanaPpal);
	conectarEventos();
	cargarBarraDeMenu();
	cargarBarraDeHerramientas();
	builder->get_widget_derived("barraEstado", barraDeEstado);
	builder->get_widget_derived("ntbOpciones", menuSolapas);
	menuSolapas->setVentanaPpal(ventanaPpal);

	if (cargarConfiguracion(TEMP_PATH_CONFIG))
		barraDeEstado->mensajeInfo("Se cargo la configuracion por defecto");

	kit.run(*ventanaPpal);
}

VentanaPrincipal::VentanaPrincipal() {
}

VentanaPrincipal::~VentanaPrincipal() {
}
