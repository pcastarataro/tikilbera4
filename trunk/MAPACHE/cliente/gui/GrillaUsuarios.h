/*
 * GrillaUsuarios.h
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */
#include <gtkmm-2.4/gtkmm.h>
#include "ControladorGrilla.h"

#ifndef GRILLAUSUARIOS_H_
#define GRILLAUSUARIOS_H_

class GrillaUsuarios: public Gtk::Table {
private:
	Glib::RefPtr<Gtk::Builder> builder;
	ControladorGrilla* controlador;
	void inicializar();

public:
	GrillaUsuarios(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~GrillaUsuarios();

	void agregarAGrilla(const std::string &cadena, const std::string &valor);
	void limpiarGrilla();

};

#endif /* GRILLAUSUARIOS_H_ */
