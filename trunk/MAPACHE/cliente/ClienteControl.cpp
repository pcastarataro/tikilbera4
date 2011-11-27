#include "ClienteControl.h"
#include "TCPSocket.h"
#include "SocketException.h"
#include "ProtocoloControl.h"
#include "ProtocoloControlException.h"

ClienteControl::ClienteControl() {
}

ClienteControl::~ClienteControl() {
}

bool ClienteControl::detenerServidor(const std::string& ip,
		unsigned int puerto) {
	bool detenidoConExito = false;
	TCPSocket sockControl;
	try {
		sockControl.conectar(ip , puerto);
		ProtocoloControl protocolo(sockControl);
		try {
			protocolo.enviarOperacionDetenerServidor();
			detenidoConExito = protocolo.recibirRespuestaDetenido();
		} catch(const SocketException&) { }
	}catch(const SocketException&) { }
	sockControl.apagar();
	sockControl.cerrar();
	return detenidoConExito;
}
