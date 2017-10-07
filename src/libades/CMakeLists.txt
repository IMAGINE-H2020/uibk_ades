project(${LIBRARY_NAME} VERSION 0.1 LANGUAGES CXX)

add_library(${LIBRARY_NAME}
	src/storage/adesdb.cpp
	src/types/ades.cpp
	src/types/motion_sequence.cpp
	src/types/motion_type.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	PRIVATE src)

target_link_libraries(${LIBRARY_NAME}
	boost
	armadillo
	libgp
	mlpack)
	
install(TARGETS ${LIBRARY_NAME} EXPORT LibADESConfig
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})   # for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT LibADESConfig DESTINATION share/LibADES/cmake) 

export(TARGETS ${LIBRARY_NAME} FILE LibADESConfig.cmake)


	

