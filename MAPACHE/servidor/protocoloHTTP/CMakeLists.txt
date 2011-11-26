INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/sockets)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/sockets/exceptions)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/servidor/utils)
ADD_LIBRARY(protocoloHTTP HTTP_Response HTTP_Message HTTP_Request ProtocoloHTTP)
