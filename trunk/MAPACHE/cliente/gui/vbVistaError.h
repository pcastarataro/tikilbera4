/*
 * vbVistaError.h
 *
 *  Created on: 07/11/2011
 *      Author: edgardo
 */
#ifndef VBVISTAERROR_H_
#define VBVISTAERROR_H_
#include <gtkmm-2.4/gtkmm.h>
#include "ControladorTxtVista.h"
#include "BarraDeEstado.h"

/**
 * Clase que define un control de usuario personalizado.
 * Se trata de un visualizador de texto con buscador de palabras.
 * Muestra el reporte de errores, con un buscador de palabras.
 */
class vbVistaError: public Gtk::VBox {
private:
	Glib::RefPtr<Gtk::Builder> builder;
	ControladorTxtVista* controladorTxt;
	void inicializar();

public:
	/**
	 * Constructor
	 */
	vbVistaError(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);

	/**
	 * Destructor
	 */
	virtual ~vbVistaError();

	/**
	 * Muestra la barra para buscar palabras.
	 */
	void mostrarBarra();

	/**
	 * Oculta la barra para buscar palabras.
	 */
	void ocultarBarra();

	/**
	 * Carga el reporte en el Gtk::TextView tomando como ubicacion del reporte
	 * la ruta seteada en Gtk::Entry
	 */
	void cargarReporte();

	/**
	 * Se mueve hasta el final del texto que esta en el Gtk::TextView
	 */
	void irAlfinal();
};

#endif
