/*
 * ControladorTxtView.h
 *
 *  Created on: 07/11/2011
 *      Author: edgardo
 */

#ifndef ControladorTxtView_H_
#define ControladorTxtView_H_
#include <gtkmm-2.4/gtkmm.h>
#include "BarraDeEstado.h"

#define MAX_BUFFER 1024

/**
 * Clase que se controla los eventos del control personalizado que se utiliza para
 * mostrar texto con buscador de palabras.
 * Controla el rellenado de cuadro de texto, el buscador en el cuadro de texto,
 * los marcadores y la barra de busqueda.
 */
class ControladorTxtView {
private:
	Gtk::TextBuffer::iterator itActualAcceso;
	/* widgets */
	Gtk::Button *btnBuscarAnterior;
	Gtk::Button *btnBuscarSiguiente;
	Gtk::CheckButton* chkResaltar;
	Gtk::Entry *txtTextoABuscar;
	Gtk::TextView* txtTextoReporte;
	Gtk::Entry* txtPathLog;
	Gtk::Table* barraBusqueda;
	//Gtk::Statusbar *barraEstado;
	BarraDeEstado *barraDeEstado;

	/* eventos */
	bool on_text_key_press_event(GdkEventKey *Key);
	void on_click_BuscarSig();
	void on_click_BuscarAnt();
	void on_click_IrAlFinal();
	void on_click_Actualizar();
	void on_click_ResaltarTexto();

	void BuscarSigEnTextbox(std::string texto, Gtk::TextView* txt,
			bool resaltar);
	void BuscarAntEnTextbox(std::string texto, Gtk::TextView* txt,
			bool resaltar);
	void ResaltaTextoEnTextbox(std::string texto, Gtk::TextView* txt);
	void inicializarItAcceso();

public:
	/**
	 * Constructor
	 */
	ControladorTxtView(Gtk::Table* barraBusqueda,
			Gtk::Button *btnBuscarAnterior, Gtk::Button *btnBuscarSiguiente,
			Gtk::CheckButton* chkResaltar, Gtk::Entry *txtTextoABuscar,
			Gtk::TextView* txtTextoReporte, Gtk::Entry* txtPathLog,
			BarraDeEstado *barraEstado);
	/**
	 * Destructor
	 */
	virtual ~ControladorTxtView();

	/**
	 * Carga el reporte en el "Gtk::TextView" : txtTextoReporte
	 * tomando como ubicacion del reporte la ruta en "Gtk::Entry" : txtPathLog
	 */
	void cargarReporte();

	/**
	 * Se mueve hasta el final del texto que esta en el "Gtk::TextView" : txtTextoReporte
	 */
	void irAlFinal();

	/**
	 * Muestra la barra para buscar palabras.
	 */
	void mostrarBarra();

	/**
	 * Oculta la barra para buscar palabras.
	 */
	void ocultarBarra();
};

#endif
