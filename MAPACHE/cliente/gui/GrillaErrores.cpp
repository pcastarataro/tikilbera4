/*
 * GrillaErrores.cpp
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#include "GrillaErrores.h"

GrillaErrores::GrillaErrores(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::Table(cobject), builder(refGlade) {
	inicializar();
}

GrillaErrores::~GrillaErrores() {
	delete (controlador);
}

void GrillaErrores::inicializar() {
	Gtk::Button *btnAgregarError;
	Gtk::Button *btnEliminarError;
	Gtk::Button *btnModifError;
	Gtk::Dialog* dialogError;
	Gtk::TreeView* tvError;
	BarraDeEstado* barraDeEstado;
	Gtk::Entry* txtNroError;
	Gtk::Entry* txtPathError;

	builder->get_widget("tvError", tvError);
	builder->get_widget("txtNroError", txtNroError);
	builder->get_widget("txtPathError", txtPathError);
	builder->get_widget("btnAgregarError", btnAgregarError);
	builder->get_widget("btnEliminarError", btnEliminarError);
	builder->get_widget("btnModifErro", btnModifError);
	builder->get_widget("dialogError", dialogError);
	builder->get_widget_derived("barraEstado", barraDeEstado);

	Glib::RefPtr < Gtk::ListStore > listError
			= Glib::RefPtr<Gtk::ListStore>::cast_static(
					builder->get_object("liststore3"));

	controlador = new ControladorGrilla(btnAgregarError, btnEliminarError,
			btnModifError, tvError, txtNroError, txtPathError, dialogError,
			listError, barraDeEstado);
}
void GrillaErrores::agregarAGrilla(const std::string &cadena,
		const std::string &valor) {
	controlador->agregarAGrilla(cadena, valor);
}

void GrillaErrores::limpiarGrilla(){
	controlador->limpiarGrilla();
}
