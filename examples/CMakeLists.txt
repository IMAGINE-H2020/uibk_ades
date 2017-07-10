#cmake_minimum_required(VERSION 3.1)
#project(examples)

target_include_directories (${LIBRARY_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

list(APPEND CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

#link_directories(${CMAKE_BINARY_DIR})
find_library(LIB_FILES ${LIBRARY_NAME})
message(STATUS "Lib name : " ${LIBRARY_NAME})
message(STATUS "Lib path : " ${LIB_FILES})
message(STATUS "build path : " ${CMAKE_BINARY_DIR})
add_executable(populating_ades populating_ades.cpp)
target_link_libraries(populating_ades LINK_PUBLIC ${LIBRARY_NAME})
#target_link_libraries(populating_ades ${CMAKE_BINARY_DIR}/lib${LIBRARY_NAME})
#message(STATUS "path to so:" ${CMAKE_BINARY_DIR}/${LIBRARY_NAME})

#file(GLOB SRC_FILES *.cpp)
#add_executable(MyApp ${SRC_FILES})
#target_link_libraries(MyApp MyLib) 
