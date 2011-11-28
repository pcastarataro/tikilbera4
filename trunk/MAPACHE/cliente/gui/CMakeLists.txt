pkg_check_modules(GTKMM gtkmm-2.4) 
# look into FindPkgConfig.cmake, 
# it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 
link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS}  )

INCLUDE_DIRECTORIES(${DIR_RAIZ}/common/configuraciones)
INCLUDE_DIRECTORIES(${DIR_RAIZ}/cliente)
ADD_LIBRARY(gui BarraDeEstado ControladorGrilla GrillaDinamicos GrillaErrores GrillaEstaticos GrillaUsuarios VentanaPrincipal ControladorTxtView vbVistaAcceso Solapas vbVistaError)
