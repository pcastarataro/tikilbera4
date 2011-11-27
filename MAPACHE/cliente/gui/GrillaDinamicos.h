/*
 * GrillaDinamicos.h
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#ifndef GRILLADINAMICOS_H_
#define GRILLADINAMICOSH_
#include "ControladorGrilla.h"
#include "BarraDeEstado.h"
#include <gtkmm-2.4/gtkmm.h>

class GrillaDinamicos : public Gtk::Table {

private:
	Glib::RefPtr<Gtk::Builder> builder;
	ControladorGrilla* controlador;
	void inicializar();

public:
	GrillaDinamicos(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~GrillaDinamicos();

	void agregarAGrilla(const std::string &cadena, const std::string &valor);
	void limpiarGrilla();

};

#endif /* GRILLADINAMICOS_H_ */
