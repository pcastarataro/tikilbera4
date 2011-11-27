/*
 * ControladorGrilla.cpp
 *
 *  Created on: 20/11/2011
 *      Author: edgardo
 */

#include "ControladorGrilla.h"
#include "ModelData.h"

ControladorGrilla::ControladorGrilla(Gtk::Button *btnAgregar,
		Gtk::Button *btnEliminar, Gtk::Button *btnModificar,
		Gtk::TreeView* treeview, Gtk::Entry* txtCadena, Gtk::Entry* txtValor,
		Gtk::Dialog* dialog, Glib::RefPtr<Gtk::ListStore> listUsuario,
		BarraDeEstado *barraDeEstado) {
	this->txtValor = txtValor;
	this->txtCadena = txtCadena;
	this->treeview = treeview;
	this->dialog = dialog;
	this->lista = listUsuario;
	this->barraDeEstado = barraDeEstado;
	this->dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	this->dialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	btnAgregar->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorGrilla::on_click_agregar));

	btnModificar->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorGrilla::on_click_modificar));

	btnEliminar->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorGrilla::on_click_eliminar));
}

ControladorGrilla::~ControladorGrilla() {
}

void ControladorGrilla::agregarAGrilla(const std::string &cadena,
		const std::string &valor) {
	ModelData model;

	typedef Gtk::TreeModel::Children type_children;
	Gtk::TreeModel::Row row = *(lista->append());
	row[model.Cadena] = cadena;
	row[model.Valor] = valor;
}

/*
 * Retorna true si los datos son validos.
 */
bool ControladorGrilla::validarDatos(const std::string &cadena,
		const std::string &valor) {
	if ((cadena == "" || valor == ""))
		return false;
	else
		return true;
}

void ControladorGrilla::on_click_agregar() {
	//  Muestro el dialogo y espero hasta que elija una opcion.
	int result = dialog->run();

	//  Reviso el resultado.
	switch (result) {
	case(Gtk::RESPONSE_OK): {
		if (validarDatos(txtCadena->get_text(), txtValor->get_text())) {
			agregarAGrilla(txtCadena->get_text(), txtValor->get_text());
			barraDeEstado->mensajeOk("Se agregaron los datos");
		} else {
			barraDeEstado->mensajeError("Los datos ingresados son invalidos");
		}
		break;
	}
	case(Gtk::RESPONSE_CANCEL): {
		break;
	}
	default: {
		break;
	}
	}
	txtCadena->set_text("");
	txtValor->set_text("");
	dialog->hide();
}

void ControladorGrilla::on_click_modificar() {
	Glib::ustring nombre;
	Glib::ustring clave;
	Gtk::TreeModel::iterator iter;
	Glib::RefPtr < Gtk::TreeView::Selection > refSelection;
	ModelData model;

	refSelection = treeview->get_selection();

	if (refSelection) {
		iter = refSelection->get_selected();
		if (iter) {
			nombre = ((*iter)[model.Cadena]);
			clave = ((*iter)[model.Valor]);

			txtCadena->set_text(nombre);
			txtValor->set_text(clave);

			//  Muestro el dialogo y espero hasta que elija una opcion.
			int result = dialog->run();

			//  Reviso el resultado.
			switch (result) {
			case(Gtk::RESPONSE_OK): {
				if (validarDatos(txtCadena->get_text(), txtValor->get_text())) {
					((*iter)[model.Cadena]) = txtCadena->get_text();
					((*iter)[model.Valor]) = txtValor->get_text();
					barraDeEstado->mensajeOk("Se modificaron los datos");
				} else {
					barraDeEstado->mensajeOk(
							"Los datos ingresados son invalidos");
				}
				break;
			}
			case(Gtk::RESPONSE_CANCEL): {
				break;
			}
			default: {
				break;
			}
			}
			txtCadena->set_text("");
			txtValor->set_text("");
			dialog->hide();
		} else {
			barraDeEstado->mensajeInfo("Seleccionar una fila para eliminar");
		}
	}
}

void ControladorGrilla::on_click_eliminar() {
	Glib::ustring cadena;
	Glib::RefPtr < Gtk::TreeView::Selection > refSelection;
	Glib::RefPtr < Gtk::ListStore > listUsuario;
	Gtk::TreeModel::iterator iter;
	ModelData model;

	refSelection = treeview->get_selection();

	if (refSelection) {
		iter = refSelection->get_selected();
		if (iter) {
			cadena = ((*iter)[model.Cadena]);
			lista->erase(iter);
			barraDeEstado->mensajeOk("Se elimino: " + cadena);
		} else
			barraDeEstado->mensajeInfo("Seleccionar una fila para eliminar");
	}
}

void ControladorGrilla::limpiarGrilla() {
	lista->clear();
	barraDeEstado->mensajeInfo("Se limpio la grilla");
}
