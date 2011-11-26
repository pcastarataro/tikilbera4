/**
 * Clase que modela los datos que utiliza el objeto grafico Gtk::TreeView.
 * para la configuracion de datos estaticos.
 */
class ModelEstatico: public Gtk::TreeModel::ColumnRecord {
public:

	/**
	 * Constructor
	 */
	ModelEstatico() {
		add(Extension);
		add(Contenido);
	}

	Gtk::TreeModelColumn<Glib::ustring> Extension;
	Gtk::TreeModelColumn<Glib::ustring> Contenido;
};
