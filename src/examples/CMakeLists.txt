add_executable(populating_ades
	src/populating_ades.cpp)

add_executable(populating_db
	src/populating_db.cpp)

add_executable(save_load_ades
	src/save_load_ades.cpp)

target_link_libraries(populating_ades 
	${LIBRARY_NAME})

target_link_libraries(populating_db
	${LIBRARY_NAME})

target_link_libraries(save_load_ades
       	${LIBRARY_NAME})

install(TARGETS populating_ades
  # IMPORTANT: Add the populating_ades executable to the "export-set"
  EXPORT LibADESTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)

install(TARGETS populating_db
  # IMPORTANT: Add the populating_db executable to the "export-set"
  EXPORT LibADESTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)

install(TARGETS save_load_ades
  # IMPORTANT: Add the save_load_ades executable to the "export-set"
  EXPORT LibADESTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
