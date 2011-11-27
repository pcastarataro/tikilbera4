/*
 * BarraDeEstado.h
 *
 *  Created on: 26/11/2011
 *      Author: edgardo
 */

#ifndef BARRADEESTADO_H_
#define BARRADEESTADO_H_
#include <gtkmm-2.4/gtkmm.h>

class BarraDeEstado : public Gtk::Statusbar {
private:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Image* imagenEstado;

public:
	BarraDeEstado(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~BarraDeEstado();

	void mensajeOk(const std::string& mensaje);
	void mensajeError(const std::string& mensaje);
	void mensajeInfo(const std::string& mensaje);
};

#endif /* BARRADEESTADO_H_ */
