INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/configuraciones)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/threads)
ADD_LIBRARY(utils CargardorDeArchivos ErrorArchivoException Log ManejadorLogs)
