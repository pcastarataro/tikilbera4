/**
 * Clase que modela los datos que utiliza el objeto grafico Gtk::TreeView.
 */
class ModelData: public Gtk::TreeModel::ColumnRecord {
public:
	/**
	 * Constructor
	 */
	ModelData() {
		add(Cadena);
		add(Valor);
	}

	Gtk::TreeModelColumn<Glib::ustring> Cadena;
	Gtk::TreeModelColumn<Glib::ustring> Valor;
};
