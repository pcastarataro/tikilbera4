/*
 * ControladorGrilla.h
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#ifndef CONTROLADORGRILLA_H_
#define CONTROLADORGRILLA_H_
#include <gtkmm-2.4/gtkmm.h>

class ControladorGrilla {
private:
	Gtk::TreeView* treeview;
	Gtk::Entry* txtCadena;
	Gtk::Entry* txtValor;
	Gtk::Dialog* dialog;
	Gtk::Statusbar *barraEstado;
	Glib::RefPtr<Gtk::ListStore> lista;

	void on_click_agregar();
	void on_click_modificar();
	void on_click_eliminar();
	bool validarDatos(const std::string &cadena, const std::string &valor);

public:
	ControladorGrilla(Gtk::Button *btnAgregar, Gtk::Button *btnEliminar,
			Gtk::Button *btnModificar, Gtk::TreeView* treeview,
			Gtk::Entry* txtCadena, Gtk::Entry* txtValor, Gtk::Dialog* dialog,
			Glib::RefPtr<Gtk::ListStore> listUsuario,
			Gtk::Statusbar *barraEstado);

	virtual ~ControladorGrilla();
	void limpiarGrilla();
	void agregarAGrilla(const std::string &cadena, const std::string &valor);


};

#endif /* CONTROLADORGRILLA_H_ */
