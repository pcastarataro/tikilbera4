/*
 * GrillaUsuarios.cpp
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#include "GrillaUsuarios.h"

GrillaUsuarios::GrillaUsuarios(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::Table(cobject), builder(refGlade) {
	inicializar();
}

GrillaUsuarios::~GrillaUsuarios() {
	delete (controlador);
}

void GrillaUsuarios::inicializar() {
	Gtk::Button *btnAgregarUsuario;
	Gtk::Button *btnEliminarUsuario;
	Gtk::Button *btnModifUsuario;
	Gtk::TreeView* tvUsuario;
	Gtk::Entry* txtNombre;
	Gtk::Entry* txtClave;
	Gtk::Dialog* dialogUsuario;
	Gtk::Statusbar *barraEstado;

	builder->get_widget("tvUsuario", tvUsuario);
	builder->get_widget("txtNombre", txtNombre);
	builder->get_widget("txtClave", txtClave);
	builder->get_widget("btnAgregarUsuario", btnAgregarUsuario);
	builder->get_widget("btnEliminarUsuario", btnEliminarUsuario);
	builder->get_widget("btnModifUsuario", btnModifUsuario);
	builder->get_widget("dialogUsuario", dialogUsuario);
	builder->get_widget("barraEstado", barraEstado);

	Glib::RefPtr < Gtk::ListStore > listUsuario
			= Glib::RefPtr<Gtk::ListStore>::cast_static(
					builder->get_object("liststore4"));

	controlador = new ControladorGrilla(btnAgregarUsuario, btnEliminarUsuario,
			btnModifUsuario, tvUsuario, txtNombre, txtClave, dialogUsuario,
			listUsuario, barraEstado);
}

void GrillaUsuarios::agregarAGrilla(const std::string &cadena,
		const std::string &valor) {
	controlador->agregarAGrilla(cadena, valor);
}

void GrillaUsuarios::limpiarGrilla(){
	controlador->limpiarGrilla();
}

