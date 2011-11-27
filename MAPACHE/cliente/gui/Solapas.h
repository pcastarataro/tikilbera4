/*
 * Solapas.h
 *
 *  Created on: 06/11/2011
 *      Author: edgardo
 */

#ifndef SOLAPAS_H_
#define SOLAPAS_H_
#include <gtkmm-2.4/gtkmm.h>
#include "Configuracion.h"
#include "TipoEstatico.h"
#include "TipoDinamico.h"
#include "GrillaUsuarios.h"
#include "GrillaEstaticos.h"
#include "GrillaDinamicos.h"
#include "GrillaErrores.h"
#include "BarraDeEstado.h"
#include "vbViewAcceso.h"
#include "vbViewError.h"

#define SOLAPA_CONF_BASICA 0
#define SOLAPA_CONF_ESTATICO 1
#define SOLAPA_CONF_DINAMICO 2
#define SOLAPA_CONF_CODIG_ERRORES 3
#define SOLAPA_CONF_USUARIO 4
#define SOLAPA_CONF_REPORTES 5
#define SOLAPA_REPORTE_ERROR 6
#define SOLAPA_REPORTE_ACCESO 7
#define SOLAPA_AYUDA 8


class Solapas: public Gtk::Notebook {
private:
	bool solapasVisibles;

	Gtk::Window *ventanaPpal;

	GrillaUsuarios* grillaUsuarios;
	GrillaEstaticos* grillaEstaticos;
	GrillaDinamicos* grillaDinamicos;
	GrillaErrores* grillaErrores;

	/* widget barra de estado */
	BarraDeEstado* barraDeEstado;

	/**/
	vbViewAcceso *viewTextAcceso;
	vbViewError *viewTextError;

	void on_click_btnExaminar();
	void on_click_btnExaminarRaiz();
	void on_click_btnExaminarLogAccesos();
	void on_click_btnExaminarLogErrores();
	void on_click_CerrarBusquedaError();
	void on_click_CerrarBusquedaAcceso();

	void selectorGuardar(Gtk::Entry* txtPath, const std::string& nombreArchivo);

	void conectarEventos();
	void cargarWidgets();

	/* Abrir configuracion */
	void setConfiguracionBasica(const ConfiguracionBasica& confBasica);
	void setConfiguracionEstatico(std::list<TipoEstatico> configuracion);
	void setConfiguracionDinamico(std::list<TipoDinamico> configuracion);
	void setConfiguracionUsuario(std::list<Usuario> configuracion);
	void setConfiguracionErrores(std::list<TipoError> configuracion);
	void setConfiguracionReportes(ConfiguracionLogs configuracion);

	/* Guardar configuracion */
	void agregarConfiguracionBasica(Configuracion& configuracion);
	void agregarConfiguracionEstatico(Configuracion& configuracion);
	void agregarConfiguracionDinamico(Configuracion& configuracion);
	void agregarConfiguracionUsuario(Configuracion& configuracion);
	void agregarConfiguracionErrores(Configuracion& configuracion);
	void agregarConfiguracionReportes(Configuracion& configuracion);

	void cargarBarraDeHerramientasTexto();

	/* */
	void setModoTexto(bool estado);

	void on_click_IrAlFinal();
	void on_click_Buscar();
	void on_click_Actualizar();

	Glib::RefPtr<Gtk::Builder> builder;
	virtual bool on_button_press_event(GdkEventButton* event);
	void cargarReporte(int numeroReporte);

public:
	/**
	 * Constructor
	 */
			Solapas(BaseObjectType* cobject,
					const Glib::RefPtr<Gtk::Builder>& refGlade);
	/**
	 * Destructor
	 */
	virtual ~Solapas();

	/**
	 * Visualiza la solapa ingresada como argumento
	 * @param numero Numero de solapa a mostrar.
	 */
	void set_current_page(int numero);

	/**
	 * Setea la ventana sobre la cual la encuentra el menu solapas.
	 * @param ventana Ventana sobre la cual esta el menu con solapas.
	 */
	void setVentanaPpal(Gtk::Window *ventana);

	/**
	 * Muestra/Oculta las solapas del menu.
	 */
	void cambiarVisibilidadSolapas();

	/**
	 * Carga la configuracion de la aplicacion
	 * @param Configuracion configuracion valida de la aplicacion
	 */
	void cargarConfiguracion(Configuracion& config);

	/**
	 * Guarda la configuracion de la aplicacion
	 * @param rutaArchivo la ubicacion donde se quiere guardar la configuracion.
	 */
	void guardarConfiguracion(const std::string &rutaArchivo);
};

#endif /* SOLAPAS_H_ */
