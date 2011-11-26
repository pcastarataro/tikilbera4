/*
 * ManejadorLogs.cpp
 *
 *  Created on: 12/11/2011
 *      Author: pablo
 */

#include "ManejadorLogs.h"

ManejadorLogs::Ptr ManejadorLogs::pinstance;
Mutex ManejadorLogs::mutex;

ManejadorLogs::ManejadorLogs(const ConfiguracionLogs& c) {
	logError = new Log(c.getRutaLogErrores());
	logAcceso = new Log(c.getRutaLogAccesos());
}

ManejadorLogs::~ManejadorLogs() {
	delete logError;
	delete logAcceso;
}

Log* ManejadorLogs::getLogAcceso() {
	return logAcceso;
}

Log* ManejadorLogs::getLogError() {
	return logError;
}
