PROJECT(Precom)


MESSAGE( STATUS "dir a incluir: " ${DIR_RAIZ} "/precompilador")
INCLUDE_DIRECTORIES(${DIR_RAIZ}/precompilador)


SET(EXECUTABLE_OUTPUT_PATH ${DIR_RAIZ}/cgi-bin)
ADD_EXECUTABLE(pr.cgi main.cpp ParserEntradaEstandar)
TARGET_LINK_LIBRARIES(pr.cgi ProcesadorTP1)
