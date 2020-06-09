cmake_minimum_required(VERSION 3.16)
project(numericalc)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory("numericalc")
add_subdirectory("numericalc-tests")

# Doxygen setup
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_CONFIG docs/doxygen-config.dox)
    add_custom_target(docs ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else()
    message("Doxygen not found.")
endif()