/*
 * BarraDeEstado.cpp
 *
 *  Created on: 26/11/2011
 *      Author: edgardo
 */

#include "BarraDeEstado.h"

BarraDeEstado::BarraDeEstado(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
	Gtk::Statusbar(cobject), builder(refGlade) {
	builder->get_widget("imagenEstado", imagenEstado);
}

BarraDeEstado::~BarraDeEstado() {
}

void BarraDeEstado::mensajeOk(const std::string& mensaje) {
	imagenEstado->set(Gtk::Stock::OK, Gtk::ICON_SIZE_BUTTON);
	this->push(mensaje);
}

void BarraDeEstado::mensajeError(const std::string& mensaje) {
	imagenEstado->set(Gtk::Stock::NO, Gtk::ICON_SIZE_BUTTON);
	this->push(mensaje);
}

void BarraDeEstado::mensajeInfo(const std::string& mensaje) {
	imagenEstado->set(Gtk::Stock::INFO, Gtk::ICON_SIZE_BUTTON);
	this->push(mensaje);
}
