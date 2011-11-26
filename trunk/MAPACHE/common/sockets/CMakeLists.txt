ADD_SUBDIRECTORY(exceptions)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/sockets/exceptions)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/protocoloControl)
ADD_LIBRARY(sockets TCPSocket)
