/*
 * GrillaEstaticos.cpp
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#include "GrillaEstaticos.h"

GrillaEstaticos::GrillaEstaticos(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::Table(cobject), builder(refGlade) {
	inicializar();
}

GrillaEstaticos::~GrillaEstaticos() {
	delete (controlador);
}

void GrillaEstaticos::inicializar() {
	Gtk::Button *btnAgregarEstatico;
	Gtk::Button *btnEliminarEstatico;
	Gtk::Button *btnModifEstatico;
	Gtk::Dialog* dialogEstatico;
	Gtk::TreeView* tvEstatico;
	Gtk::Statusbar *barraEstado;
	Gtk::Entry* txtExtension;
	Gtk::Entry* txtContenido;

	builder->get_widget("tvEstatico", tvEstatico);
	builder->get_widget("txtExtensionEs", txtExtension);
	builder->get_widget("txtContenido", txtContenido);
	builder->get_widget("btnAgregarEstatico", btnAgregarEstatico);
	builder->get_widget("btnEliminarEstatico", btnEliminarEstatico);
	builder->get_widget("btnModifEstatico", btnModifEstatico);
	builder->get_widget("dialogEstatico", dialogEstatico);
	builder->get_widget("barraEstado", barraEstado);

	Glib::RefPtr < Gtk::ListStore > listEstatico
			= Glib::RefPtr<Gtk::ListStore>::cast_static(
					builder->get_object("liststore1"));

	controlador = new ControladorGrilla(btnAgregarEstatico,
			btnEliminarEstatico, btnModifEstatico, tvEstatico, txtExtension,
			txtContenido, dialogEstatico, listEstatico, barraEstado);
}

void GrillaEstaticos::agregarAGrilla(const std::string &cadena,
		const std::string &valor) {
	controlador->agregarAGrilla(cadena, valor);
}

void GrillaEstaticos::limpiarGrilla(){
	controlador->limpiarGrilla();
}

