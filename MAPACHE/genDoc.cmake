MACRO(GENERATE_DOCUMENTATION NOMBRE_PROYECTO OUTPUT_DIR)
#el archivo doxy debe estar en el mismo path que el input source
MESSAGE( STATUS "output_dir: " ${OUTPUT_DIR})
SET( OUT_DIR ${OUTPUT_DIR})
SET( PRJ_NAME ${NOMBRE_PROYECTO})
SET(NOMBRE_CONFIG Doxy${NOMBRE_PROYECTO})
SET(DIR_DESTINO_DOXY_CONFIG ${DIR_ABSOLUTA_DOXYFILE}${NOMBRE_CONFIG})



# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${DOXY_CONFIG} ${DIR_DESTINO_DOXY_CONFIG} @ONLY)
add_custom_target(doc${PRJ_NAME} ALL
${DOXYGEN_EXECUTABLE} ${NOMBRE_CONFIG}
WORKING_DIRECTORY ${DIR_ABSOLUTA_DOXYFILE}#el archivo doxy debe estar en el mismo path que el input source!!
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
ENDMACRO(GENERATE_DOCUMENTATION)

