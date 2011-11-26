PROJECT(Cliente)
find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-2.4) 
# look into FindPkgConfig.cmake, 
# it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
ADD_SUBDIRECTORY(gui)

INCLUDE_DIRECTORIES(${DIR_RAIZ}/cliente/gui)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/configuraciones)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/sockets)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/protocoloControl)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/sockets/exceptions)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/cliente)


SET(EXECUTABLE_OUTPUT_PATH ${DIR_RAIZ})
ADD_EXECUTABLE(ConfiguradorMapache Main ClienteControl)
TARGET_LINK_LIBRARIES(ConfiguradorMapache gui  ${GTKMM_LIBRARIES} sockets protocoloControl exceptions configuraciones tinyxml)
