#include "ProcesadorPHP.h"

/*	ejemplo de comando -> "php formulario.php --cantArchivos=5 --modo=fr" */
string ProcesadorPHP::armarComandoPHP(const string rutaPHP, 
		std::list<string> listaParams) {
	string comando("php ");

	comando.append(rutaPHP);

	for (list<string>::iterator it = listaParams.begin() ; 
			it != listaParams.end() ; it++) {
		comando.append(" --");
		comando.append(*it);
	}

	return comando;
}

bool ProcesadorPHP::extraerParametrosParaElPHP(string& rutaDelPHP , 
		const string uri , list<string>& listaParams) {
	size_t pos = uri.find(".php");
	bool retorno = true;
	
	if (pos == uri.npos) 
		retorno = false;
	else {
		retorno = true;
		rutaDelPHP = uri.substr(0, pos + 4);
		string parametros(uri.substr(pos + 5, uri.length()));
		size_t posInicial = 0;
		size_t posFinal = 0;
		
		while (posFinal = parametros.find("&", posInicial) != parametros.npos) {
			string param = parametros.substr(posInicial, posFinal-1);
			listaParams.push_back(param);
			posInicial = posFinal + 1;
		}	
		string param = parametros.substr(posInicial, parametros.length());
		listaParams.push_back(param);
	}
	
	return retorno;
}
