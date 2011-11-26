/*
 * vbViewError.cpp
 *
 *  Created on: 07/11/2011
 *      Author: edgardo
 */

#include "vbViewError.h"
#include <fstream>
//
vbViewError::vbViewError(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::VBox(cobject), builder(refGlade) {
	inicializar();
}

vbViewError::~vbViewError() {
	delete(controladorTxt);
}

void vbViewError::inicializar() {
	/* widgets */
	Gtk::Button *btnBuscarAnt;
	Gtk::Button *btnBuscarSig;
	Gtk::CheckButton* chkResaltar;
	Gtk::Entry *txtBuscarEnAcceso;
	Gtk::TextView* txtReporteAccesos;
	Gtk::Entry* txtPathLog;
	Gtk::Table* hbBuscarEnError;
	Gtk::Statusbar *barraEstado;

	builder->get_widget("chkResaltarError", chkResaltar);
	builder->get_widget("btnBuscarAntError", btnBuscarAnt);
	builder->get_widget("btnBuscarSigError", btnBuscarSig);
	builder->get_widget("txtBuscarEnError", txtBuscarEnAcceso);
	builder->get_widget("txtReporteError", txtReporteAccesos);
	builder->get_widget("txtPathLogError", txtPathLog);
	builder->get_widget("hbBuscarEnError", hbBuscarEnError);
	builder->get_widget("barraEstado", barraEstado);

	controladorTxt = new ControladorTxtView(hbBuscarEnError, btnBuscarAnt,
			btnBuscarSig, chkResaltar, txtBuscarEnAcceso, txtReporteAccesos,
			txtPathLog, barraEstado);
}

void vbViewError::cargarReporte() {
	controladorTxt->cargarReporte();
}

void vbViewError::mostrarBarra() {
	controladorTxt->mostrarBarra();
}

void vbViewError::ocultarBarra() {
	controladorTxt->ocultarBarra();
}

void vbViewError::irAlfinal() {
	controladorTxt->irAlFinal();
}
