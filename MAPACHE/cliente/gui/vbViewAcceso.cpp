/*
 * vbViewAcceso.cpp
 *
 *  Created on: 07/11/2011
 *      Author: edgardo
 */

#include "vbViewAcceso.h"
#include <fstream>

vbViewAcceso::vbViewAcceso(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::VBox(cobject), builder(refGlade) {
	inicializar();
}

vbViewAcceso::~vbViewAcceso() {
	delete (controladorTxt);
}

void vbViewAcceso::inicializar() {
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

void vbViewAcceso::cargarReporte() {
	controladorTxt->cargarReporte();
}

void vbViewAcceso::mostrarBarra() {
	controladorTxt->mostrarBarra();
}

void vbViewAcceso::ocultarBarra() {
	controladorTxt->ocultarBarra();
}

void vbViewAcceso::irAlfinal() {
	controladorTxt->irAlFinal();
}
