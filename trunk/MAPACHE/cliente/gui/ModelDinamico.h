/**
 * Clase que modela los datos que utiliza el objeto grafico Gtk::TreeView.
 * para la configuracion de datos dinamicos.
 */
class ModelDinamico: public Gtk::TreeModel::ColumnRecord {
public:

	/**
	 * Constructor
	 */
	ModelDinamico() {
		add(Extension);
		add(Comando);
	}

	Gtk::TreeModelColumn<Glib::ustring> Extension;
	Gtk::TreeModelColumn<Glib::ustring> Comando;
};
