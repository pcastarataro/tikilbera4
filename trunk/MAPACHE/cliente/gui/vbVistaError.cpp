/*
 * vbVistaError.cpp
 *
 *  Created on: 07/11/2011
 *      Author: edgardo
 */

#include "vbVistaError.h"
#include <fstream>

vbVistaError::vbVistaError(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::VBox(cobject), builder(refGlade) {
	inicializar();
}

vbVistaError::~vbVistaError() {
	delete(controladorTxt);
}

void vbVistaError::inicializar() {
	/* widgets */
	Gtk::Button *btnBuscarAnt;
	Gtk::Button *btnBuscarSig;
	Gtk::CheckButton* chkResaltar;
	Gtk::Entry *txtBuscarEnAcceso;
	Gtk::TextView* txtReporteAccesos;
	Gtk::Entry* txtPathLog;
	Gtk::Table* hbBuscarEnError;
	BarraDeEstado* barraDeEstado;

	builder->get_widget("chkResaltarError", chkResaltar);
	builder->get_widget("btnBuscarAntError", btnBuscarAnt);
	builder->get_widget("btnBuscarSigError", btnBuscarSig);
	builder->get_widget("txtBuscarEnError", txtBuscarEnAcceso);
	builder->get_widget("txtReporteError", txtReporteAccesos);
	builder->get_widget("txtPathLogError", txtPathLog);
	builder->get_widget("hbBuscarEnError", hbBuscarEnError);
	builder->get_widget_derived("barraEstado", barraDeEstado);

	controladorTxt = new ControladorTxtView(hbBuscarEnError, btnBuscarAnt,
			btnBuscarSig, chkResaltar, txtBuscarEnAcceso, txtReporteAccesos,
			txtPathLog, barraDeEstado);
}

void vbVistaError::cargarReporte() {
	controladorTxt->cargarReporte();
}

void vbVistaError::mostrarBarra() {
	controladorTxt->mostrarBarra();
}

void vbVistaError::ocultarBarra() {
	controladorTxt->ocultarBarra();
}

void vbVistaError::irAlfinal() {
	controladorTxt->irAlFinal();
}
