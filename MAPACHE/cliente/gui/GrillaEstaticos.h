/*
 * GrillaEstaticos.h
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#ifndef GRILLAESTATICOS_H_
#define GRILLAESTATICOS_H_
#include "ControladorGrilla.h"
#include <gtkmm-2.4/gtkmm.h>

class GrillaEstaticos : public Gtk::Table {

private:
	Glib::RefPtr<Gtk::Builder> builder;
	ControladorGrilla* controlador;
	void inicializar();

public:
	GrillaEstaticos(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~GrillaEstaticos();

	void agregarAGrilla(const std::string &cadena, const std::string &valor);
	void limpiarGrilla();

};

#endif /* GRILLAESTATICOS_H_ */
