MACRO(GENERATE_DOCUMENTATION NOMBRE_PROYECTO)
#el archivo doxy debe estar en el mismo path que el input source


SET(PRJ_NAME ${NOMBRE_PROYECTO})
SET(NOMBRE_CONFIG Doxy${NOMBRE_PROYECTO})
SET(OUT_DIR ${DOXY_CONFIG_DIR}${NOMBRE_CONFIG})
SET(DIR_DOXY_CONFIG_DEPLOY ${DIR_ABSOLUTA_DOXYFILE}Doxy${PRJ_NAME})
MESSAGE( STATUS "OUT_DIR: " ${OUT_DIR})
MESSAGE( STATUS "DIR_ABSOLUTA_DOXYFILE: " ${DIR_ABSOLUTA_DOXYFILE})
MESSAGE( STATUS "DIR_DOXY_CONFIG_DEPLOY: " ${DIR_DOXY_CONFIG_DEPLOY})


# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_DIR})

configure_file(${DOXY_CONFIG} ${DIR_DOXY_CONFIG_DEPLOY} @ONLY)
add_custom_target(doc${PRJ_NAME} ALL
${DOXYGEN_EXECUTABLE} ${NOMBRE_CONFIG}
WORKING_DIRECTORY ${DIR_ABSOLUTA_DOXYFILE}#el archivo doxy debe estar en el mismo path que el input source!!
COMMENT "Generating API documentation with Doxygen" VERBATIM
)

#SET(LISTA ${LISTA} ; ${DIR_DOXY_CONFIG_DEPLOY})
#MESSAGE( STATUS "LISTA: " ${LISTA})


endif(DOXYGEN_FOUND)
ENDMACRO(GENERATE_DOCUMENTATION)
