/*
 * vbViewError.h
 *
 *  Created on: 07/11/2011
 *      Author: edgardo
 */
#ifndef VBVIEWERROR_H_
#define VBVIEWERROR_H_
#include <gtkmm-2.4/gtkmm.h>
#include "ControladorTxtView.h"

/**
 * Clase que define un control de usuario personalizado.
 * Se trata de un visualizador de texto con buscador de palabras.
 * Muestra el reporte de errores, con un buscador de palabras.
 */
class vbViewError: public Gtk::VBox {
private:
	Glib::RefPtr<Gtk::Builder> builder;
	ControladorTxtView* controladorTxt;
	//Gtk::TextBuffer::iterator itActualAcceso;
	void inicializar();

public:
	/**
	 * Constructor
	 */
	vbViewError(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);

	/**
	 * Destructor
	 */
	virtual ~vbViewError();

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
