/*
 * vbViewAcceso.h
 *
 *  Created on: 07/11/2011
 *      Author: edgardo
 */

#ifndef VBVIEWACCESO_H_
#define VBVIEWACCESO_H_
#include <gtkmm-2.4/gtkmm.h>
#include "ControladorTxtView.h"

/**
 * Clase que define un control de usuario personalizado.
 * Se trata de un visualizador de texto con buscador de palabras.
 * Muestra el reporte de accesos, con un buscador de palabras.
 */
class vbViewAcceso: public Gtk::VBox {
private:
	Glib::RefPtr<Gtk::Builder> builder;
	ControladorTxtView* controladorTxt;
	//Gtk::TextBuffer::iterator itActualAcceso;
	void inicializar();

public:
	/**
	 * Constructor
	 */
	vbViewAcceso(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);

	/**
	 * Destructor
	 */
	virtual ~vbViewAcceso();

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
