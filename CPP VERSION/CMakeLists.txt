cmake_minimum_required(VERSION 2.6)

project(Tank_Game)

set(EXECUTABLE_OUTPUT_PATH ..)

file(
    GLOB_RECURSE
    source_files
    
    src/*.cpp
	  src/*.hpp
	)

add_executable(
  Tank_Game
  ${source_files}
  )

FIND_PACKAGE(PythonLibs 2.7 REQUIRED)
target_link_libraries(Tank_Game python2.7)

FIND_PACKAGE(Boost  ${BOOST_VERSION}  COMPONENTS python)
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIR}"   "${PYTHON_INCLUDE_DIRS}")
LINK_DIRECTORIES("${PYTHON_INCLUDE_DIRS}" "${Boost_LIBRARY_DIRS}")

if(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-std=c++17 -Wall)
        # add_definitions(-O2 -s -DNDEBUG)
        add_definitions(-g -DEBUG)
        add_definitions(${GCC_COVERAGE_LINK_FLAGS}$)
endif()

list(APPEND CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")
find_package(SFML 2.4 COMPONENTS system window graphics network audio)
target_link_libraries(Tank_Game sfml-graphics sfml-system sfml-window sfml-audio sfml-network)
