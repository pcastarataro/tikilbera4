PROJECT(parserPHP)
SET (EXECUTABLE_OUTPUT_PATH ${DIR_RAIZ}/cgi-bin)
ADD_EXECUTABLE(parserPHP.cgi main.cpp ProcesadorPHP)
