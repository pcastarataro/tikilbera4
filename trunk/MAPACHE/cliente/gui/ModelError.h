/**
 * Clase que modela los datos que utiliza el objeto grafico Gtk::TreeView.
 * para la configuracion de errores.
 */
class ModelError: public Gtk::TreeModel::ColumnRecord {
public:

	/**
	 * Constructor
	 */
	ModelError() {
		add(NroError);
		add(Path);
	}

	Gtk::TreeModelColumn<Glib::ustring> NroError;
	Gtk::TreeModelColumn<Glib::ustring> Path;
};
