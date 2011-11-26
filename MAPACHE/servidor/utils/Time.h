#ifndef TIME_H_
#define TIME_H_
#include <time.h>
#include <iostream>

/**
 * Clase encargada de manejar el tiempo utilizado para
 * las respuestas
 */
class Time {
private:
	time_t tiempo;
	struct tm *tlocal;
public:
	/**
	 * Contructor
	 */
	Time() {}

	/**
	 * Destructor
	 */
	virtual ~Time() {}

	/**
	 * Devuelve la hora en una cadena de text
	 */
	std::string getHora() {
	char output[128];
	tiempo = time(0);
	tlocal = localtime(&tiempo);
	strftime(output, 128, "%H:%M:%S", tlocal);
	std::string hora(output);
	return hora;
}

	/**
	 * Devuelve la fecha en una cadena de text
	 */
	std::string getFecha() {
	char output[128];
	tiempo = time(0);
	tlocal = localtime(&tiempo);
	strftime(output, 128, "%d/%m/%y", tlocal);
	std::string fecha(output);
	return fecha;
}

	/**
	 * Devuelve una cadena con la fecha y hora en el formato para
	 * las respuestas
	 */
	std::string getFechaHora() {
	char output[128];
	tiempo = time(0);
	tlocal = localtime(&tiempo);
	  strftime( output, 128, "%a, %d %b %Y %H:%M:%S %Z", tlocal );
	std::string fecha(output);
	return fecha;
}
};

#endif /* TIME_H_ */
