#ifndef LOG_H_
#define LOG_H_
#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/PatternLayout.hh>

/**
 * Clase encargada de abstraer el manejo de la libreria log4cpp para nuestra aplicacion
 */
class Log {
private:
	log4cpp::Category& category;
	log4cpp::Appender *appender;
	log4cpp::Layout *layout;
	log4cpp::PatternLayout *layoutPattern;

public:
	/**
	 * Constructor
	 * @param pathLogFile es la ruta del log a utilizar.
	 */
	explicit Log(const std::string& pathLogFile);

	/**
	 * Contructor
	 * @param pathLogFile es la ruta del log a utilizar
	 * @param format es el formato que se le dará al log(ver documentacion libreria).
	 */
	Log(const std::string& pathLogFile, const std::string& format);

	/**
	 * Destructor
	 */
	virtual ~Log();

	/**
	 * Loguea un warning dentro del log
	 * @menssage es el mensaje que se logueara
	 */
	void logWarning(const std::string& menssage);

	/**
	 * Loguea un error dentro del log
	 * @menssage es el mensaje que se logueara
	 */
	void logError(const std::string& menssage);

	/**
	 * Loguea una informacion dentro del log
	 * @menssage es el mensaje que se logueara
	 */
	void logInfo(const std::string& menssage);
};

#endif
