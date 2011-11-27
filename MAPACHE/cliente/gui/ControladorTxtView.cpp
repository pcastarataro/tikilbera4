/*
 * ControladorTxtView.cpp
 *
 *  Created on: 07/11/2011
 *
 *      Author: edgardo
 */

#include "ControladorTxtView.h"
#include <fstream>

ControladorTxtView::ControladorTxtView(Gtk::Table* barraBusqueda,
		Gtk::Button *btnBuscarAnterior, Gtk::Button *btnBuscarSiguiente,
		Gtk::CheckButton* chkResaltar, Gtk::Entry *txtTextoABuscar,
		Gtk::TextView* txtTextoReporte, Gtk::Entry* txtPathLog,
		BarraDeEstado *barraEstado) {
	this->btnBuscarAnterior = btnBuscarAnterior;
	this->btnBuscarSiguiente = btnBuscarSiguiente;
	this->chkResaltar = chkResaltar;
	this->txtTextoABuscar = txtTextoABuscar;
	this->txtTextoReporte = txtTextoReporte;
	this->txtPathLog = txtPathLog;
	this->barraBusqueda = barraBusqueda;
	this->barraDeEstado = barraEstado;

	btnBuscarAnterior->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorTxtView::on_click_BuscarAnt));

	btnBuscarSiguiente->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorTxtView::on_click_BuscarSig));

	chkResaltar->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorTxtView::on_click_ResaltarTexto));

	txtTextoABuscar->signal_key_release_event().connect(
			sigc::mem_fun(*this, &ControladorTxtView::on_text_key_press_event));
}

ControladorTxtView::~ControladorTxtView() {
}

bool ControladorTxtView::on_text_key_press_event(GdkEventKey *Key) {
	std::string enter("Return");
	std::string teclaPresionada(gdk_keyval_name(Key->keyval));

	if (teclaPresionada == enter)
		on_click_BuscarSig();
	else {
		inicializarItAcceso();
		if (chkResaltar->get_active())
			ResaltaTextoEnTextbox(txtTextoABuscar->get_text(), txtTextoReporte);
	}
	return true;
}

void ControladorTxtView::cargarReporte() {
	std::ifstream archivoError;
	std::string ubicacion;
	char buffer[MAX_BUFFER];

	Glib::RefPtr < Gtk::TextBuffer > m_refTextBuffer
			= txtTextoReporte->get_buffer();
	m_refTextBuffer->set_text("");
	ubicacion = txtPathLog->get_text();
	archivoError.open(ubicacion.c_str());

	if (!archivoError.good()) {
		m_refTextBuffer->insert_at_cursor("No se encuentra el archivo ...");
	} else {
		while (archivoError.good()) {
			archivoError.getline(buffer, MAX_BUFFER, '\n');
			m_refTextBuffer->insert_at_cursor(buffer);
			m_refTextBuffer->insert_at_cursor("\n");
		}
	}
	txtTextoReporte->set_buffer(m_refTextBuffer);
	inicializarItAcceso();
}

void ControladorTxtView::irAlFinal() {
	Glib::RefPtr < Gtk::TextBuffer > buffer;
	buffer = txtTextoReporte->get_buffer();
	Gtk::TextBuffer::iterator it = buffer->end();
	txtTextoReporte->scroll_to(it);
}

void ControladorTxtView::on_click_Actualizar() {
	cargarReporte();
	barraDeEstado->mensajeInfo("Reporte actualizado");
}

void ControladorTxtView::ResaltaTextoEnTextbox(std::string texto,
		Gtk::TextView* txt) {
	Glib::RefPtr < Gtk::TextBuffer > buffer = txt->get_buffer();
	buffer->remove_all_tags(buffer->begin(), buffer->end());

	Glib::RefPtr < Gtk::TextBuffer::Tag > refTagMatch
			= Gtk::TextBuffer::Tag::create();
	refTagMatch->property_background() = "gray";

	Glib::RefPtr < Gtk::TextBuffer::TagTable > refTagTable
			= buffer->get_tag_table();
	refTagTable->add(refTagMatch);

	Gtk::TextBuffer::iterator mathStart;
	Gtk::TextBuffer::iterator mathEnd;
	Gtk::TextBuffer::iterator it = buffer->begin();

	while (it.forward_search(texto.c_str(),
			Gtk::TEXT_SEARCH_TEXT_ONLY | Gtk::TEXT_SEARCH_VISIBLE_ONLY,
			mathStart, mathEnd)) {
		buffer->apply_tag(refTagMatch, mathStart, mathEnd);
		it = mathEnd;
	}
}

void ControladorTxtView::BuscarSigEnTextbox(std::string texto,
		Gtk::TextView* txt, bool resaltar) {
	int fila, columna;

	Glib::RefPtr < Gtk::TextBuffer > buffer;
	buffer = txt->get_buffer();

	buffer->remove_all_tags(buffer->begin(), buffer->end());

	if (resaltar)
		ResaltaTextoEnTextbox(texto, txt);

	Glib::RefPtr < Gtk::TextBuffer::Tag > refTagMatch
			= Gtk::TextBuffer::Tag::create();
	refTagMatch->property_background() = "orange";

	Glib::RefPtr < Gtk::TextBuffer::TagTable > refTagTable
			= buffer->get_tag_table();

	refTagTable->add(refTagMatch);

	Gtk::TextBuffer::iterator mathStart;
	Gtk::TextBuffer::iterator mathEnd;

	bool estado = itActualAcceso.forward_search(texto.c_str(),
			Gtk::TEXT_SEARCH_TEXT_ONLY | Gtk::TEXT_SEARCH_VISIBLE_ONLY,
			mathStart, mathEnd);

	if (estado) {
		fila = mathStart.get_line();
		columna = mathStart.get_line_offset();
		buffer->apply_tag(refTagMatch, mathStart, mathEnd);
		txt->scroll_to(mathEnd);
		itActualAcceso = mathEnd;
		gchar* msg = g_strdup_printf("Encontrado en: Col %d Ln %d",
				columna + 1, fila + 1);
		barraDeEstado->mensajeInfo(msg);
	} else
		barraDeEstado->mensajeInfo("No hay mas coincidencias con " + texto);
}

void ControladorTxtView::BuscarAntEnTextbox(std::string texto,
		Gtk::TextView* txt, bool resaltar) {
	int fila, columna;

	Glib::RefPtr < Gtk::TextBuffer > buffer;
	buffer = txt->get_buffer();

	buffer->remove_all_tags(buffer->begin(), buffer->end());

	if (resaltar)
		ResaltaTextoEnTextbox(texto, txt);
	Glib::RefPtr < Gtk::TextBuffer::Tag > refTagMatch
			= Gtk::TextBuffer::Tag::create();
	refTagMatch->property_background() = "orange";

	Glib::RefPtr < Gtk::TextBuffer::TagTable > refTagTable
			= buffer->get_tag_table();

	refTagTable->add(refTagMatch);

	Gtk::TextBuffer::iterator mathStart;
	Gtk::TextBuffer::iterator mathEnd;

	bool estado = itActualAcceso.backward_search(texto.c_str(),
			Gtk::TEXT_SEARCH_TEXT_ONLY | Gtk::TEXT_SEARCH_VISIBLE_ONLY,
			mathStart, mathEnd);

	if (estado) {
		fila = mathStart.get_line();
		columna = mathStart.get_line_offset();
		buffer->apply_tag(refTagMatch, mathStart, mathEnd);
		txt->scroll_to(mathStart);
		itActualAcceso = mathStart;
		gchar* msg = g_strdup_printf("Encontrado en: Col %d Ln %d",
				columna + 1, fila + 1);
		barraDeEstado->mensajeInfo(msg);
	} else
		barraDeEstado->mensajeInfo("No hay mas coincidencias con " + texto);
}

void ControladorTxtView::inicializarItAcceso() {
	Glib::RefPtr < Gtk::TextBuffer > buffer;
	buffer = txtTextoReporte->get_buffer();
	itActualAcceso = buffer->begin();
}

void ControladorTxtView::on_click_BuscarSig() {
	BuscarSigEnTextbox(txtTextoABuscar->get_text(), txtTextoReporte,
			chkResaltar->get_active());
}

void ControladorTxtView::on_click_BuscarAnt() {
	BuscarAntEnTextbox(txtTextoABuscar->get_text(), txtTextoReporte,
			chkResaltar->get_active());
}

void ControladorTxtView::on_click_ResaltarTexto() {
	bool activo = chkResaltar->get_active();
	Glib::RefPtr < Gtk::TextBuffer > buffer = txtTextoReporte->get_buffer();
	buffer->remove_all_tags(buffer->begin(), buffer->end());
	if ((activo) && (txtTextoABuscar->get_text() != ""))
		ResaltaTextoEnTextbox(txtTextoABuscar->get_text(), txtTextoReporte);
}

void ControladorTxtView::mostrarBarra() {
	if (barraBusqueda != NULL)
		barraBusqueda->show();
}

void ControladorTxtView::ocultarBarra() {
	if (barraBusqueda != NULL) {
		Glib::RefPtr < Gtk::TextBuffer > buffer = txtTextoReporte->get_buffer();
		buffer->remove_all_tags(buffer->begin(), buffer->end());
		barraBusqueda->hide();
	}
}
