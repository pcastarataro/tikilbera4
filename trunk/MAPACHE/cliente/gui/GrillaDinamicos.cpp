/*
 * GrillaDinamicos.cpp
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#include "GrillaDinamicos.h"

GrillaDinamicos::GrillaDinamicos(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::Table(cobject), builder(refGlade) {
	inicializar();
}

GrillaDinamicos::~GrillaDinamicos() {
	delete (controlador);
}

void GrillaDinamicos::inicializar() {
	Gtk::Button *btnAgregarDinamico;
	Gtk::Button *btnEliminarDinamico;
	Gtk::Button *btnModifDinamico;
	Gtk::Dialog* dialogDinamico;
	Gtk::TreeView* tvDinamico;
	BarraDeEstado* barraDeEstado;
	Gtk::Entry* txtExtension;
	Gtk::Entry* txtComando;

	builder->get_widget("tvDinamico", tvDinamico);
	builder->get_widget("txtExtensionDi", txtExtension);
	builder->get_widget("txtComando", txtComando);
	builder->get_widget("btnAgregarDinamico", btnAgregarDinamico);
	builder->get_widget("btnEliminarDinamico", btnEliminarDinamico);
	builder->get_widget("btnModifDinamico", btnModifDinamico);
	builder->get_widget("dialogDinamico", dialogDinamico);
	builder->get_widget_derived("barraEstado", barraDeEstado);

	Glib::RefPtr < Gtk::ListStore > listDinamico
			= Glib::RefPtr<Gtk::ListStore>::cast_static(
					builder->get_object("liststore2"));

	controlador = new ControladorGrilla(btnAgregarDinamico,
			btnEliminarDinamico, btnModifDinamico, tvDinamico, txtExtension,
			txtComando, dialogDinamico, listDinamico, barraDeEstado);
}

void GrillaDinamicos::agregarAGrilla(const std::string &cadena,
		const std::string &valor) {
	controlador->agregarAGrilla(cadena, valor);
}

void GrillaDinamicos::limpiarGrilla() {
	controlador->limpiarGrilla();
}
