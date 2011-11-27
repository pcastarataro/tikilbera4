/*
 * GrillaErrores.h
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#ifndef GRILLAERRORES_H_
#define GRILLAERRORES_H_
#include "ControladorGrilla.h"
#include "BarraDeEstado.h"
#include <gtkmm-2.4/gtkmm.h>

class GrillaErrores : public Gtk::Table {
private:
	Glib::RefPtr<Gtk::Builder> builder;
	ControladorGrilla* controlador;
	void inicializar();

public:
	GrillaErrores(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~GrillaErrores();
	void agregarAGrilla(const std::string &cadena, const std::string &valor);
	void limpiarGrilla();
};

#endif /* GRILLAERRORES_H_ */
