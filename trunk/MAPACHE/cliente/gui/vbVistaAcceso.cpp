/*
 * vbVistaAcceso.cpp
 *
 *  Created on: 07/11/2011
 *      Author: edgardo
 */

#include "vbVistaAcceso.h"
#include <fstream>

vbVistaAcceso::vbVistaAcceso(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::VBox(cobject), builder(refGlade) {
	inicializar();
}

vbVistaAcceso::~vbVistaAcceso() {
	delete (controladorTxt);
}

void vbVistaAcceso::inicializar() {
	Gtk::Button *btnBuscarAnt;
	Gtk::Button *btnBuscarSig;
	Gtk::CheckButton* chkResaltar;
	Gtk::Entry *txtBuscarEnAcceso;
	Gtk::TextView* txtReporteAccesos;
	Gtk::Entry* txtPathLog;
	Gtk::Table* hbBuscarEnAcceso;
	BarraDeEstado *barraDeEstado;

	builder->get_widget("chkResaltar", chkResaltar);
	builder->get_widget("btnBuscarAnt", btnBuscarAnt);
	builder->get_widget("btnBuscarSig", btnBuscarSig);
	builder->get_widget("txtBuscarEnAcceso", txtBuscarEnAcceso);
	builder->get_widget("txtReporteAccesos", txtReporteAccesos);
	builder->get_widget("txtPathLogAccesos", txtPathLog);
	builder->get_widget("hbBuscarEnAcceso", hbBuscarEnAcceso);
	builder->get_widget("barraEstado", barraDeEstado);

	controladorTxt = new ControladorTxtView(hbBuscarEnAcceso, btnBuscarAnt,
			btnBuscarSig, chkResaltar, txtBuscarEnAcceso, txtReporteAccesos,
			txtPathLog, barraDeEstado);
}

void vbVistaAcceso::cargarReporte() {
	controladorTxt->cargarReporte();
}

void vbVistaAcceso::mostrarBarra() {
	controladorTxt->mostrarBarra();
}

void vbVistaAcceso::ocultarBarra() {
	controladorTxt->ocultarBarra();
}

void vbVistaAcceso::irAlfinal() {
	controladorTxt->irAlFinal();
}
