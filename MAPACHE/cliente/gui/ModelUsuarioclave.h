/**
 * Clase que modela los datos que utiliza el objeto grafico Gtk::TreeView.
 * para la configuracion de usuarios.
 */
class ModelUsuarioClave: public Gtk::TreeModel::ColumnRecord {
public:

	/**
	 * Constructor
	 */
	ModelUsuarioClave() {
		add(Usuario);
		add(Clave);
	}

	Gtk::TreeModelColumn<Glib::ustring> Usuario;
	Gtk::TreeModelColumn<Glib::ustring> Clave;
};
