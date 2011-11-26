/*
 * Solapas.cpp
 *
 *  Created on: 06/11/2011
 *      Author: edgardo
 */
#include <iostream>
#include <fstream>

#include "Solapas.h"
#include "ModelEstatico.h"
#include "ModelDinamico.h"
#include "ModelUsuarioclave.h"
#include "ModelError.h"
//#include "BoxTextView.h"

Solapas::Solapas(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::Notebook(cobject), builder(refGlade) {

	solapasVisibles = false;
	this->set_show_tabs(solapasVisibles);
	cargarWidgets();
	conectarEventos();
	//inicializarDialogos();
	cargarBarraDeHerramientasTexto();

	builder->get_widget_derived("vbReporteAcceso", viewTextAcceso);
	builder->get_widget_derived("vbReporteError", viewTextError);
	builder->get_widget_derived("tblUsuarios", grillaUsuarios);
	builder->get_widget_derived("tblEstaticos", grillaEstaticos);
	builder->get_widget_derived("tblDinamicos", grillaDinamicos);
	builder->get_widget_derived("tblErrores", grillaErrores);

	setModoTexto(false);
}

Solapas::~Solapas() {
}

int stringToInt(const std::string& cadena) {
	int auxEntero;
	std::stringstream auxStream;

	auxStream.clear();
	auxStream << cadena;
	auxStream >> auxEntero;
	return auxEntero;
}

void Solapas::cambiarVisibilidadSolapas() {
	solapasVisibles = !solapasVisibles;
	this->set_show_tabs(solapasVisibles);
}

void Solapas::conectarEventos() {
	Gtk::Button *btnExaminar;
	Gtk::Button *btnExaminarRaiz;

	Gtk::Button *btnExaminarLogAccesos;
	Gtk::Button *btnExaminarLogErrores;

	builder->get_widget("btnExaminar", btnExaminar);
	builder->get_widget("btnExaminarRaiz", btnExaminarRaiz);

	builder->get_widget("btnExaminarLogAccesos", btnExaminarLogAccesos);
	builder->get_widget("btnExaminarLogErrores", btnExaminarLogErrores);

	btnExaminar->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_btnExaminar));

	btnExaminarRaiz->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_btnExaminarRaiz));

	btnExaminarLogAccesos->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_btnExaminarLogAccesos));

	btnExaminarLogErrores->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_btnExaminarLogErrores));

}

void Solapas::selectorGuardar(Gtk::Entry* txtPath,
		const std::string& nombreArchivo) {
	Gtk::FileChooserDialog dialog("Guardar como...",
			Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.set_transient_for(*ventanaPpal);

	//Agrego los botones para la respuesta:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
	dialog.set_current_name(nombreArchivo);
	dialog.set_do_overwrite_confirmation(true);

	//Muestro el dialogo y espero hasta que elija una opcion.
	int result = dialog.run();

	//Reviso el resultado.
	switch (result) {
	case (Gtk::RESPONSE_OK): {
		std::string filename = dialog.get_filename();
		txtPath->set_text(filename);
		break;
	}
	case (Gtk::RESPONSE_CANCEL): {
		barraEstado->push("seleccion de archivo cancelada");
		break;
	}
	default: {
		barraEstado->push("No se pudo realizar la operacion");
		break;
	}
	}
}

void Solapas::on_click_btnExaminarLogAccesos() {
	Gtk::Entry* txtPathLogAccesos;
	builder->get_widget("txtPathLogAccesos", txtPathLogAccesos);
	selectorGuardar(txtPathLogAccesos, "Accesos.log");
}

void Solapas::on_click_btnExaminarLogErrores() {
	Gtk::Entry* txtPathLogError;
	builder->get_widget("txtPathLogError", txtPathLogError);

	selectorGuardar(txtPathLogError, "Errores.log");
}

void Solapas::on_click_btnExaminar() {
	Gtk::Entry* txtPathError;
	Gtk::FileChooserDialog dialog("Seleccionar archivo", Gtk::FILE_CHOOSER_ACTION_OPEN);
	builder->get_widget("txtPathError", txtPathError);
	dialog.set_transient_for(*ventanaPpal);

	// Agrego los botones para la respuesta:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	// Muestro el dialogo y espero hasta que elija una opcion.
	int result = dialog.run();
	// Reviso el resultado.
	switch (result) {
	case (Gtk::RESPONSE_OK): {
		std::string filename = dialog.get_filename();
		txtPathError->set_text(filename);
		break;
	}
	case (Gtk::RESPONSE_CANCEL): {
		barraEstado->push("Carga de configuracion cancelada");
		break;
	}
	default: {
		break;
	}
	}
}

/**/
void Solapas::on_click_btnExaminarRaiz() {
	Gtk::Entry* txtRaiz;
	Gtk::FileChooserDialog dialog("Seleccionar archivo",
			Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	builder->get_widget("txtRaiz", txtRaiz);
	
	dialog.set_transient_for(*ventanaPpal);

	// Agrego los botones para la respuesta:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	// Muestro el dialogo y espero hasta que elija una opcion.
	int result = dialog.run();

	// Reviso el resultado.
	switch (result) {
	case (Gtk::RESPONSE_OK): {
		std::string filename = dialog.get_filename();
		txtRaiz->set_text(filename);
		break;
	}
	case (Gtk::RESPONSE_CANCEL): {
		break;
	}
	default: {
		break;
	}
	}
}

void Solapas::cargarWidgets() {
	builder->get_widget("barraEstado", barraEstado);
}

void Solapas::setConfiguracionBasica(const ConfiguracionBasica& confBasica) {
	std::stringstream auxStream;
	Gtk::SpinButton* sbtPuerto;
	Gtk::SpinButton* sbtPuertoContro;
	Gtk::SpinButton* sbtMaxConexiones;
	Gtk::SpinButton* sbtMaxConCliente;
	Gtk::SpinButton* sbtTimeOut;
	Gtk::Entry* txtRaiz;
	Gtk::CheckButton* cbtProtegido;

	builder->get_widget("sbtPuerto", sbtPuerto);
	builder->get_widget("sbtPuertoContro", sbtPuertoContro);
	builder->get_widget("txtRaiz", txtRaiz);
	builder->get_widget("cbtProtegido", cbtProtegido);
	builder->get_widget("sbtMaxConexiones", sbtMaxConexiones);
	builder->get_widget("sbtMaxConCliente", sbtMaxConCliente);
	builder->get_widget("sbtTimeOut", sbtTimeOut);

	sbtPuerto->set_value(confBasica.getPuerto());
	sbtPuertoContro->set_value(confBasica.getPuertoControl());
	sbtMaxConexiones->set_value(confBasica.getMaximoConexiones());
	sbtMaxConCliente->set_value(confBasica.getMaximoConexionesCliente());
	sbtTimeOut->set_value(confBasica.getTimeOut());
	txtRaiz->set_text(confBasica.getRaiz());

	cbtProtegido->set_active(confBasica.getProteccion());

}

void Solapas::setConfiguracionEstatico(std::list<TipoEstatico> configuracion) {
	std::list<TipoEstatico>::iterator it = configuracion.begin();

grillaEstaticos->limpiarGrilla();
	while (it != configuracion.end()) {
		grillaEstaticos->agregarAGrilla(it->getExtension(), it->getContenido());
		it++;
	}
}

void Solapas::setConfiguracionDinamico(std::list<TipoDinamico> configuracion) {
	std::list<TipoDinamico>::iterator it = configuracion.begin();

	grillaDinamicos->limpiarGrilla();

	while (it != configuracion.end()) {
		grillaDinamicos->agregarAGrilla(it->getExtension(), it->getComando());
		it++;
	}
}

void Solapas::setConfiguracionUsuario(std::list<Usuario> configuracion) {
	std::list<Usuario>::iterator it = configuracion.begin();

	grillaUsuarios->limpiarGrilla();

	while (it != configuracion.end()) {
		grillaUsuarios->agregarAGrilla(it->getNombre(), it->getClave());
		it++;
	}
}
void Solapas::setConfiguracionReportes(ConfiguracionLogs confLog) {
	Gtk::Entry* pathReporteError;
	Gtk::Entry* pathReporteAccesos;

	builder->get_widget("txtPathLogAccesos", pathReporteAccesos);
	builder->get_widget("txtPathLogError", pathReporteError);

	pathReporteAccesos->set_text(confLog.getRutaLogAccesos());
	pathReporteError->set_text(confLog.getRutaLogErrores());
}

void Solapas::setConfiguracionErrores(std::list<TipoError> configuracion) {
	std::list<TipoError>::iterator it = configuracion.begin();

	grillaErrores->limpiarGrilla();

	while (it != configuracion.end()) {
		std::stringstream nroError;
		nroError << it->getNroError();

		grillaErrores->agregarAGrilla(nroError.str(), it->getRuta());
		it++;
	}
}

void Solapas::agregarConfiguracionBasica(Configuracion& configuracion) {
	std::stringstream auxStream;
	Gtk::SpinButton* sbtPuerto;
	Gtk::SpinButton* sbtPuertoContro;
	Gtk::SpinButton* sbtMaxConexiones;
	Gtk::SpinButton* sbtMaxConCliente;
	Gtk::SpinButton* sbtTimeOut;
	Gtk::Entry* txtRaiz;
	Gtk::CheckButton* cbtProtegido;

	builder->get_widget("sbtPuerto", sbtPuerto);
	builder->get_widget("sbtPuertoContro", sbtPuertoContro);
	builder->get_widget("txtRaiz", txtRaiz);
	builder->get_widget("cbtProtegido", cbtProtegido);
	builder->get_widget("sbtMaxConexiones", sbtMaxConexiones);
	builder->get_widget("sbtMaxConCliente", sbtMaxConCliente);
	builder->get_widget("sbtTimeOut", sbtTimeOut);

	ConfiguracionBasica confBasica;
	confBasica.setPuerto(sbtPuerto->get_value());
	confBasica.setPuertoControl(sbtPuertoContro->get_value());
	confBasica.setMaximoConexiones(sbtMaxConexiones->get_value());
	confBasica.setMaximoConexionesCliente(sbtMaxConCliente->get_value());
	confBasica.setTimeOut(sbtTimeOut->get_value());
	confBasica.setRaiz(txtRaiz->get_text());

	if (cbtProtegido->get_active())
		confBasica.proteger();

	configuracion.setConfiguracionBasica(confBasica);
}

void Solapas::agregarConfiguracionEstatico(Configuracion& configuracion) {
	TipoEstatico* confEstatico;
	Glib::ustring extension;
	Glib::ustring contenido;

	Glib::RefPtr < Gtk::ListStore > listTipoEstatico = Glib::RefPtr<
			Gtk::ListStore>::cast_static(builder->get_object("liststore1"));

	typedef Gtk::TreeModel::Children type_children; //minimise code length.
	ModelEstatico modelEstatico;

	type_children children = listTipoEstatico->children();
	for (type_children::iterator iter = children.begin(); iter
			!= children.end(); ++iter) {
		Gtk::TreeModel::Row row = *iter;
		extension = (*iter)[modelEstatico.Extension];
		contenido = (*iter)[modelEstatico.Contenido];
		confEstatico = new TipoEstatico();
		confEstatico->setExtension(extension);
		confEstatico->setContenido(contenido);
		configuracion.agregarTipoEstatico(confEstatico);
	}
}

void Solapas::agregarConfiguracionDinamico(Configuracion& configuracion) {
	TipoDinamico* confDinamico;
	Glib::ustring extension;
	Glib::ustring comando;

	Glib::RefPtr < Gtk::ListStore > listTipoDinamico = Glib::RefPtr<
			Gtk::ListStore>::cast_static(builder->get_object("liststore2"));

	typedef Gtk::TreeModel::Children type_children; //minimise code length.
	ModelDinamico modelDinamico;

	type_children children = listTipoDinamico->children();
	for (type_children::iterator iter = children.begin(); iter
			!= children.end(); ++iter) {
		Gtk::TreeModel::Row row = *iter;
		extension = (*iter)[modelDinamico.Extension];
		comando = (*iter)[modelDinamico.Comando];
		confDinamico = new TipoDinamico();
		confDinamico->setExtension(extension);
		confDinamico->setComando(comando);
		configuracion.agregarTipoDinamico(confDinamico);
	}
}

void Solapas::agregarConfiguracionUsuario(Configuracion& configuracion) {
	Usuario* confUsuario;
	Glib::ustring nombre;
	Glib::ustring clave;

	Glib::RefPtr < Gtk::ListStore > listUsuarios
			= Glib::RefPtr<Gtk::ListStore>::cast_static(
					builder->get_object("liststore4"));

	typedef Gtk::TreeModel::Children type_children; //minimise code length.
	ModelUsuarioClave modelUsuarioClave;

	type_children children = listUsuarios->children();
	for (type_children::iterator iter = children.begin(); iter
			!= children.end(); ++iter) {
		Gtk::TreeModel::Row row = *iter;
		nombre = (*iter)[modelUsuarioClave.Usuario];
		clave = (*iter)[modelUsuarioClave.Clave];
		confUsuario = new Usuario();
		confUsuario->setNombre(nombre);
		confUsuario->setClave(clave);
		configuracion.agregarUsuario(confUsuario);
	}
}

void Solapas::agregarConfiguracionErrores(Configuracion& configuracion) {
	Glib::ustring nroError;
	Glib::ustring path;
	int nroErrorEntero;

	Glib::RefPtr < Gtk::ListStore > listUsuarios
			= Glib::RefPtr<Gtk::ListStore>::cast_static(
					builder->get_object("liststore3"));

	typedef Gtk::TreeModel::Children type_children; //minimise code length.
	ModelError modelError;

	type_children children = listUsuarios->children();
	for (type_children::iterator iter = children.begin(); iter
			!= children.end(); ++iter) {
		Gtk::TreeModel::Row row = *iter;
		nroError = (*iter)[modelError.NroError];
		path = (*iter)[modelError.Path];
		nroErrorEntero = stringToInt(nroError);
		TipoError* tipoError = new TipoError();
		tipoError->setNroError(nroErrorEntero);
		tipoError->setRuta(path);
		configuracion.agregarError(tipoError);
	}
}

void Solapas::agregarConfiguracionReportes(Configuracion& configuracion) {
	Gtk::Entry* pathReporteError;
	Gtk::Entry* pathReporteAccesos;

	builder->get_widget("txtPathLogAccesos", pathReporteAccesos);
	builder->get_widget("txtPathLogError", pathReporteError);

	ConfiguracionLogs confLogs;
	confLogs.setRutaLogAccesos(pathReporteAccesos->get_text());
	confLogs.setRutaLogErrores(pathReporteError->get_text());
	configuracion.setConfiguracionLogs(confLogs);
}

void Solapas::cargarConfiguracion(Configuracion& config) {

	setConfiguracionBasica(config.getConfiguracionBasica());
	setConfiguracionEstatico(config.getTiposEstaticos());
	setConfiguracionDinamico(config.getTiposDinamicos());
	setConfiguracionUsuario(config.getUsuarios());
	setConfiguracionErrores(config.getTiposErrores());
	setConfiguracionReportes(config.getConfiguracionLogs());
}

void Solapas::guardarConfiguracion(const std::string &rutaArchivo) {
	Configuracion configuracion;

	agregarConfiguracionBasica(configuracion);
	agregarConfiguracionEstatico(configuracion);
	agregarConfiguracionDinamico(configuracion);
	agregarConfiguracionErrores(configuracion);
	agregarConfiguracionReportes(configuracion);
	agregarConfiguracionUsuario(configuracion);
	configuracion.guardarComo(rutaArchivo);

}

void Solapas::setModoTexto(bool estado) {
	Gtk::Toolbar* barraTexto;
	builder->get_widget("barraTexto", barraTexto);
	if (estado)
		barraTexto->show();
	else
		barraTexto->hide();
}

void Solapas::on_click_IrAlFinal() {
	int opcion = this->get_current_page();
	if (opcion == 6) {
		viewTextError->irAlfinal();
		barraEstado->push("Ir al final en Errores");
	} else if (opcion == 7) {
		viewTextAcceso->irAlfinal();
		barraEstado->push("Ir al final en Accessos");
	} else
		barraEstado->push("No entiendo!");
}

void Solapas::on_click_CerrarBusquedaError() {
	viewTextError->ocultarBarra();
}

void Solapas::on_click_CerrarBusquedaAcceso() {
	viewTextAcceso->ocultarBarra();
}

void Solapas::on_click_Buscar() {
	int opcion = this->get_current_page();
	if (opcion == 6) {
		viewTextError->mostrarBarra();
		barraEstado->push("Mostrar barra de buqueda Errores");
	} else if (opcion == 7) {
		viewTextAcceso->mostrarBarra();
		barraEstado->push("Mostrar barra de buqueda en Accessos");
	} else
		barraEstado->push("No entiendo!");
}

void Solapas::on_click_Actualizar() {
	int opcion = this->get_current_page();
	if (opcion == 6) {
		viewTextError->cargarReporte();
		barraEstado->push("Se actualizo el reporte de error");
	} else if (opcion == 7) {
		viewTextAcceso->cargarReporte();
		barraEstado->push("Se actualizo el reporte de accesos");
	} else
		barraEstado->push("No entiendo!");
}

void Solapas::cargarBarraDeHerramientasTexto() {
	Gtk::ToolButton * toolbtBuscar;
	Gtk::ToolButton * toolbtIrAlFinal;
	Gtk::ToolButton * toolbtActualizar;
	Gtk::Button *btnCerrarBusquedaAcceso;
	Gtk::Button *btnCerrarBusquedaError;

	builder->get_widget("toolbtBuscar", toolbtBuscar);
	builder->get_widget("toolbtIrAlFinal", toolbtIrAlFinal);
	builder->get_widget("toolbtActualizar", toolbtActualizar);
	builder->get_widget("btnCerrarBusquedaAcceso", btnCerrarBusquedaAcceso);
	builder->get_widget("btnCerrarBusquedaError", btnCerrarBusquedaError);

	toolbtIrAlFinal->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_IrAlFinal));

	toolbtBuscar->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_Buscar));

	toolbtActualizar->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_Actualizar));

	btnCerrarBusquedaAcceso->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_CerrarBusquedaAcceso));

	btnCerrarBusquedaError->signal_clicked().connect(
			sigc::mem_fun(*this, &Solapas::on_click_CerrarBusquedaError));

	setModoTexto(false);
}

void Solapas::setVentanaPpal(Gtk::Window *ventana) {
	this->ventanaPpal = ventana;
}

void Solapas::cargarReporte(int numeroReporte) {
	std::ifstream archivoError;
	switch (numeroReporte) {
	case SOLAPA_REPORTE_ERROR:
		viewTextError->cargarReporte();
		setModoTexto(true);
		break;
	case SOLAPA_REPORTE_ACCESO:
		viewTextAcceso->cargarReporte();
		setModoTexto(true);
		break;
	default:
		setModoTexto(false);
		break;
	}
}

bool Solapas::on_button_press_event(GdkEventButton* event) {
	bool res = Gtk::Notebook::on_button_press_event(event);
	int opcion = this->get_current_page();
	cargarReporte(opcion);
	return res;
}

void Solapas::set_current_page(int numero) {
	cargarReporte(numero);
	Gtk::Notebook::set_current_page(numero);
}
